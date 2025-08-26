#pragma once

#include <QObject>
#include "singleton.h"
#include <QString>
#include "Data.h"

// 用户管理类，单例模式，用于存储和管理当前登录用户的信息。
class UserManager : public QObject, public Singleton<UserManager>, public std::enable_shared_from_this<UserManager>
{
	Q_OBJECT
public:
    friend class Singleton<UserManager>;
    ~UserManager();
    void setUid(int uid);
    void setToken(QString token);
    int getUid();
    QString getToken();
    void setUserInfo(std::shared_ptr<UserInfo> user_info);
    std::shared_ptr<UserInfo> getUserInfo(int uid);
    QString getUsername();
    QString getUsername(const int& uid);
    void clear();
private:
    UserManager();
    int _uid;
    QString _token;
	std::unordered_map<int, std::shared_ptr<UserInfo>> _uid_name_map; // 用户ID和用户个人信息的映射
    std::unordered_map<int, std::shared_ptr<UserInfo>> _uid_friend_map; // id和朋友信息
};

