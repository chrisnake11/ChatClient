#pragma once

#include <QObject>
#include <QTcpSocket>
#include "singleton.h"
#include "global.h"
#include <functional>
#include "Data.h"

class TcpManager  : public QObject, public Singleton<TcpManager>, public std::enable_shared_from_this<TcpManager>
{
	Q_OBJECT

public:
	~TcpManager();
private:
	friend class Singleton<TcpManager>;
	TcpManager();
	void initHandlers();
	void handleMsg(RequestID id, int len, QByteArray data);
	void handleLogin(RequestID id, int len, QByteArray data);
	// 处理响应，获取消息列表
	void handleGetMessageList(RequestID id, int len, QByteArray data);
	void handleGetContactList(RequestID id, int len, QByteArray data);
	void handleGetChatMessageList(RequestID id, int len, QByteArray data);
	void handleSentChatMessageSuccess(RequestID id, int len, QByteArray data);
	void handleReceiveChatMessage(RequestID id, int len, QByteArray data);

	// handle login response
	QMap<RequestID, std::function<void(RequestID id, int len, QByteArray data)>> _handlers;

	// client socket
	QTcpSocket _socket;
	QString _host;
	uint16_t _port;

	// 接收数据的缓冲区
	QByteArray _buffer;
	bool _b_recv_pending;
	quint16 _message_id;
	quint16 _message_len;


public:
	// 建立TCP长连接
	void slot_tcp_connect(ServerInfo);
	// 发送数据
	void slot_send_data(RequestID reqId, QString data);


signals:
	void sig_connect_success(bool success);
	void sig_send_data(RequestID reqId, QString data);
	void sig_login_failed(int); // 登录失败
	void loginSuccess(); // 登录成功
	// 获取消息列表
	void getMessageInfoList(std::shared_ptr<std::vector<MessageItemInfo>>);
	void getContactInfoList(std::shared_ptr<std::vector<ContactItemInfo>>); // 获取消息列表成功
	void getChatMessageList(const int& uid, const int& friend_uid, std::shared_ptr<std::vector<ChatMessageInfo>> message_list);
	void sentChatMessageSuccess(std::shared_ptr<ChatMessageInfo> message); // 发送消息成功
	void receiveChatMessage(std::shared_ptr<ChatMessageInfo> message);
};

