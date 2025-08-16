#include "UserInfo.h"

UserInfo::UserInfo()
    : uid(0), _sex(0), _username(""), _nickname(""), _personalSignature("") {}

UserInfo::UserInfo(int uid, int sex, const QString &username, const QString &nickname)
    : uid(uid), _sex(sex), _username(username), _nickname(nickname), _personalSignature("") {}
