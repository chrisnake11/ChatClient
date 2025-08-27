#pragma once
#include <string>

struct ServerInfo {
	quint16 uid;
	QString host;
	QString port;
	QString token;
};

struct BaseUserInfo {
	BaseUserInfo() : uid(0), username(""), email(""), passwd("") {}
	int uid;
	QString username;
	QString email;
	QString passwd;
};

struct UserInfo : public BaseUserInfo {
public:
	UserInfo() : BaseUserInfo(),avatar(""), sign(""), nickname(""), gender(0), birthday(""), phone(""), address(""), online_status(0), last_login(""), register_time("") {}
	QString nickname; // 昵称
	QString phone; // 电话
	QString address; // 地址
	QString avatar; // 头像
	int gender; // 性别
	QString birthday; // 生日
	QString sign; // 个性签名
	int online_status; // 在线状态，0-离线，1-在线
	QString last_login; // 最后登录时间
	QString register_time; // 注册时间
};

// 聊天消息
struct MessageInfoItem {
	MessageInfoItem() : uid(0), unread_count(0) {}
	MessageInfoItem(int uid, const QString& nickname, const QString& avatar, const QString& message, const QString& last_message_time, int unread_count)
		: uid(uid), nickname(nickname), avatar(avatar), message(message), last_message_time(last_message_time), unread_count(unread_count) {
	}
	int uid;
	QString nickname;
	QString avatar;
	QString message;
	QString last_message_time;
	int unread_count;
};

struct AddFriendInfo {
};

struct AuthFriendInfo {
};