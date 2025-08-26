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

struct AddFriendInfo {
};

struct AuthFriendInfo {
};