#pragma once
#include <QString>

class UserInfo{

public:
    UserInfo();
    UserInfo(int uid, int sex, const QString &username, const QString &nickname);

    int uid;
    int _sex;
    QString _username;
    QString _nickname;
    QString _personalSignature;
};