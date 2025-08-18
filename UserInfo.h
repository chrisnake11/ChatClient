#pragma once

#include <QString>

class UserInfo{
public:
    UserInfo() = default;
    UserInfo(int uid, int sex, int age, const QString& avatar, const QString &username, const QString &address, const QString& personalSignature, bool isOnline)
        : uid(uid), sex(sex), age(age), avatar(avatar), username(username), address(address), personalSignature(personalSignature), isOnline(isOnline) {}
    int uid;
    int sex;
    int age;
    QString avatar;
    QString username;
    QString address;
    QString personalSignature;
    bool isOnline;
};