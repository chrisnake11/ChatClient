#include "TcpManager.h"
#include <QAbstractSocket>
#include <QJsonDocument>
#include "UserManager.h"
#include <memory>
#include <vector>

TcpManager::TcpManager() : _host(""), _port(0), _b_recv_pending(false), _message_id(0), _message_len(0) {
	// QTcpSocket连接成功后，发送信号
	QObject::connect(&_socket, &QTcpSocket::connected, [&] {
		qDebug() << "Success Connect to Server, emit connect_success(true)";
		emit sig_connect_success(true);
		});

		// QTcpSocket接收到数据后，处理接收的数据
		QObject::connect(&_socket, &QTcpSocket::readyRead, [&] {
			// 当所有数据接收完毕，添加到缓存中
			_buffer.append(_socket.readAll());

			QDataStream stream(&_buffer, QIODevice::ReadOnly);
			stream.setVersion(QDataStream::Qt_6_0);

			// 处理接收到的数据
			forever {
				// 没有中断，直接获取消息头
				if (!_b_recv_pending) {
					// 没有足够的数据来读取消息头，退出
					if (_buffer.size() < static_cast<int>(sizeof(quint16) * 2)) {
						return;
					}

					// 读取消息ID和消息len
					stream >> _message_id >> _message_len;

					//将buffer中的前四个字节移除
					_buffer = _buffer.mid(sizeof(quint16) * 2);

					qDebug() << "Message id: " << _message_id << ", Message len: " << _message_len;
				}

				// 没有足够的缓存读取消息体
				if (_buffer.size() < _message_len) {
					_b_recv_pending = true;
					return;
				}

				// 获取消息体
				_b_recv_pending = false;
				QByteArray message_body = _buffer.mid(0, _message_len);
				qDebug() << "recv body is: " << message_body;

				// 处理消息体
				_buffer = _buffer.mid(_message_len);
				handleMsg(RequestID(_message_id), _message_len, message_body);
			}

			});

	// socket发生错误时
	 QObject::connect(&_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), [&](QAbstractSocket::SocketError socketError) {
           Q_UNUSED(socketError)
           qDebug() << "Error:" << _socket.errorString();
		   emit sig_connect_success(false);
       });

	 // QTcpSocket断开连接时
	 QObject::connect(&_socket, &QTcpSocket::disconnected, [&]() {
		 qDebug() << "Disconnected from server.";
		 });

	 // 发送数据
	 QObject::connect(this, &TcpManager::sig_send_data, this, &TcpManager::slot_send_data);

	 initHandlers();
}

TcpManager::~TcpManager() {

}

void TcpManager::handleLogin(RequestID id, int len, QByteArray data) {
	Q_UNUSED(len);
	qDebug() << "handle id is: " << id << "data is " << data;

	// parse json data		
	QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

	if (jsonDoc.isNull()) {
		qDebug() << "Failed to create JsonDocument";
		return;
	}

	QJsonObject jsonObj = jsonDoc.object();
	if (!jsonObj.contains("error")) {
		int err = ErrorCodes::ERROR_JSON_PARSE_FAILED;
		qDebug() << "Login Failed, error is json parse error" << err;
		emit sig_login_failed(err);
		return;
	}

	// check success signals
	int err = jsonObj["error"].toInt();
	if (err != ErrorCodes::SUCCESS) {
		qDebug() << "Login failed, err is " << err;
		emit sig_login_failed(err);
		return;
	}

	// 读取用户数据
	std::shared_ptr<UserInfo> user_info = std::make_shared<UserInfo>();
	if (jsonObj.contains("user_info") && jsonObj["user_info"].isObject()) {
		QJsonObject user_obj = jsonObj["user_info"].toObject();
		user_info->uid = user_obj["uid"].toInt();
		user_info->username = user_obj["user_name"].toString();
		user_info->email = user_obj["email"].toString();
		user_info->passwd = user_obj["passwd"].toString();
		user_info->nickname = user_obj["nickname"].toString();
		user_info->phone = user_obj["phone"].toString();
		user_info->address = user_obj["address"].toString();
		user_info->avatar = user_obj["avatar"].toString();
		user_info->gender = user_obj["gender"].toInt();
		user_info->birthday = user_obj["birthday"].toString();
		user_info->sign = user_obj["sign"].toString();
		user_info->online_status = user_obj["online_status"].toInt();
		user_info->last_login = user_obj["last_login"].toString();
		user_info->register_time = user_obj["register_time"].toString();
	}
	else {
		int err = ErrorCodes::ERROR_LOAD_USERINFO_FAILED;
		qDebug() << "Login Failed, load json user info failed" << err;
		emit sig_login_failed(err);
		return;
	}

	// 保存用户信息
	UserManager::getInstance()->setUid(jsonObj["uid"].toInt());
	UserManager::getInstance()->setToken(jsonObj["token"].toString());
	UserManager::getInstance()->setUserInfo(std::move(user_info));

	// change to chat dialog
	emit loginSuccess();
}

void TcpManager::handlerGetMessageList(RequestID id, int len, QByteArray data) { 
	Q_UNUSED(len);
	qDebug() << "handle id is ID_GET_MESSAGE_LIST: " << id;
	// 解析为json
	QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
	if (jsonDoc.isNull()) {
		qDebug() << "Failed to create JsonDocument";
		return;
	}
	QJsonObject jsonObj = jsonDoc.object();
	if (!jsonObj.contains("error")) {
		int err = ErrorCodes::ERROR_JSON_PARSE_FAILED;
		qDebug() << "Get Message List Failed, error is json parse error" << err;
		return;
	}
	// check success signals
	int err = jsonObj["error"].toInt();
	if (err != ErrorCodes::SUCCESS) {
		qDebug() << "Get Message List Failed, err is " << err;
		return;
	}

	std::shared_ptr<std::vector<MessageInfoItem>> message_list = std::make_shared<std::vector<MessageInfoItem>>();

	if (jsonObj.contains("message_list") && jsonObj["message_list"].isArray()) {
		for (auto item : jsonObj["message_list"].toArray()) {
			QJsonObject message_obj = item.toObject();

			message_list->emplace_back(message_obj["uid"].toInt(), message_obj["nickname"].toString(), message_obj["avatar"].toString(), message_obj["message"].toString(), message_obj["last_message_time"].toString(), message_obj["unread_count"].toInt());
		}
	}

	emit getMessageInfoList(message_list);
}

void TcpManager::initHandlers() {
	// 响应获取用户数据的请求结果
	_handlers.insert(ID_LOGIN_CHAT, [this](RequestID id, int len, QByteArray data) {
			handleLogin(id, len, data);
		});

	_handlers.insert(ID_GET_MESSAGE_LIST, [this](RequestID id, int len, QByteArray data) {
			handlerGetMessageList(id, len, data);
		});
}

void TcpManager::handleMsg(RequestID id, int len, QByteArray data) {
	auto it = _handlers.find(id);
	if (it == _handlers.end()) {
		qDebug() << "not found id " << id << " handler function";
		return;
	}
	it.value()(id, len, data);
}

void TcpManager::slot_tcp_connect(ServerInfo server_info) {
	qDebug() << "Connecting to chat server";
	_host = server_info.host;
	_port = static_cast<uint16_t>(server_info.port.toUInt());
	qDebug() << "Target ChatServer Host: " << _host << ", Port: " << _port;
	_socket.connectToHost(_host, _port);
}

void TcpManager::slot_send_data(RequestID reqId, QString data) {
    qDebug() << "Send data to chat server, " << reqId << data;

	uint16_t id = static_cast<uint16_t>(reqId);
	QByteArray dataBytes = data.toUtf8();
	quint16 len = static_cast<quint16>(dataBytes.size());

	// create a write-only buffer to send data
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setByteOrder(QDataStream::BigEndian);
	out << id << len;
	block.append(dataBytes);

	// send data
	_socket.write(block);
	_socket.flush();
}