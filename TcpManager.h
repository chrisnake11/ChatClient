#pragma once

#include <QObject>
#include <QTcpSocket>
#include "singleton.h"
#include "global.h"
#include <functional>

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
	void slot_tcp_connect(ServerInfo);
	void slot_send_data(RequestID reqId, QString data);
signals:
	void sig_connect_success(bool success);
	void sig_send_data(RequestID reqId, QString data);
	void sig_switch_chat_dialog();
	void sig_login_failed(int);
};

