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

    std::shared_ptr<UserInfo> getFriendInfo(int uid);

    // 获取联系人时，更新联系人信息
    void updateFriendInfoByContactList(std::shared_ptr<std::vector<ContactItemInfo>> contact_list);

    QString getUsername();
    QString getUsername(const int& uid);
    void clear();
private:
    UserManager();
    int _uid;
    QString _token;
	std::unordered_map<int, std::shared_ptr<UserInfo>> _uid_name_map; // 用户ID和用户个人信息的映射
    std::unordered_map<int, std::shared_ptr<UserInfo>> _uid_friend_map; // 联系人id和联系人的信息
};

