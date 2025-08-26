#ifndef GLOBAL_H
#define GLOBAL_H

#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QWidget>
#include <functional>
#include "QStyle"
#include <QByteArray>
#include <QNetworkReply>
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QString>
#include <QCryptographicHash>

// repolish widget style
extern std::function<void(QWidget*)> repolish;

extern std::function<QString(QString)> md5Encrypt;

enum RequestID {
    ID_GET_VARIFY_CODE = 1001,
    ID_REG_USER = 1002,
    ID_RESET_USER = 1003,
    ID_LOGIN_USER = 1004,
    ID_LOGIN_CHAT = 1005,
    ID_LOGIN_CHAT_RSP = 1006,
};

enum Modules{
    REG_MODEL = 0,
    RESET_MODEL = 1,
    LOGIN_MODEL = 2
};

enum ErrorCodes{
    SUCCESS = 0,
    ERR_NETWORK = 2, // 网络或者服务异常
    ERROR_JSON_PARSE_FAILED = 1001, //Json 解析失败
    ERROR_RPC_FAILED = 1002, // rpc调用失败
    ERROR_VARIFY_EXPIRED = 1003, // 验证码过期
    ERROR_VARIFY_WRONG = 1004, // 验证码错误
    ERROR_USER_EXIST = 1005, // 用户已存在
    ERROR_PASSWORD_WRONG = 1006, // 密码错误
    ERROR_EMAIL_NOT_MATCH = 1007, // 邮箱不匹配
    ERROR_PASSWORD_UPDATE_FAILED = 1008, // 密码更新失败
    ERROR_PASSWORD_INVALID = 1009, // 密码无效
    ERROR_UID_INVALID = 1010, // 用户ID无效
    ERROR_TOKEN_INVALID = 1011, // token无效
    ERROR_LOAD_USERINFO_FAILED = 1012, // 读取用户信息失败
};

enum TipErr {
    TIP_SUCCESS = 0,
    TIP_EMAIL_ERR = 1,
    TIP_PWD_ERR = 2,
    TIP_CONFIRM_ERR = 3,
    TIP_PWD_CONFIRM = 4,
    TIP_VARIFY_ERR = 5,
    TIP_USER_ERR = 6
};

enum ClickLabelState{
    NORMAL = 0,
    SELECTED = 1,
};

extern QString gate_url_prefix;

extern std::vector<int> test_uids;

extern std::vector<QString> test_users;

extern std::vector<QString> test_messages;

extern std::vector<QString> test_times;

enum class WidgetMouseState{
    NORMAL = 0,
    HOVERED = 1,
    PRESSED = 2,
    SELECTED = 3,
    DISABLED = 4
};


#endif // GLOBAL_H
