#pragma once
#include <string>

struct ServerInfo {
	quint16 uid;
	QString host;
	QString port;
	QString token;
};

struct BaseUserInfo {
	int uid;
	QString username;
	QString email;
	QString passwd;
};

struct UserInfo : public BaseUserInfo {
	int gender; // 性别
	int onlineStatus; // 在线状态，0-离线，1-在线
	QString nickname; // 昵称
	QString phone; // 电话
	QString address; // 地址
	QString avatar; // 头像
	QString birthday; // 生日
	QString sign; // 个性签名
	QString lastLogin; // 最后登录时间
	QString registerTime; // 注册时间
};

// 聊天消息
struct MessageItemInfo {
	MessageItemInfo() : uid(0), unreadCount(0) {}
	MessageItemInfo(int uid, const QString& nickname, const QString& avatar, const QString& message, const QString& last_message_time, int unread_count):
        uid(uid), nickname(nickname), avatar(avatar), message(message), lastMessageTime(last_message_time), unreadCount(unread_count) {}
	int uid;
	QString nickname;
	QString avatar;
	QString message;
	QString lastMessageTime;
	int unreadCount;
};

struct ContactItemInfo {
	ContactItemInfo(): uid(0), onlineStatus(0) {}
	int uid;
	int onlineStatus;
	QString username;
    QString nickname;
	QString avatar;
	QString sign;
};

struct ChatMessageInfo {
	ChatMessageInfo(): message_id(0), sender_id(0), receiver_id(0) {}
	int message_id;
	int sender_id;
	int receiver_id;
    QString message;
	QString message_time;
	QString message_type;
};

struct AddFriendInfo {
};

struct AuthFriendInfo {
};