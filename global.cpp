#include "global.h"

std::function<void(QWidget*)> repolish = [](QWidget* w){
    w->style()->unpolish(w);
    w->style()->polish(w);
};

std::function<QString(QString)> md5Encrypt = [](const QString& input){
    QByteArray byteArray = input.toUtf8();
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Md5);
    return hash.toHex();
};

QString gate_url_prefix = "";

std::vector<QString> test_users = {
    "user1",
    "user2",
    "user3",
    "user4",
    "user5",
    "user6",
    "user7",
    "user8",
    "user9",
    "user10",
    "user11",
    "user21",
    "user31",
    "user41",
    "user51",
    "user61",
    "user71",
    "user81",
    "user91",
    "user101"
};


std::vector<QString> test_messages = {
    "Hello, how are you?",
    "Did you receive my last message?",
    "Let's meet tomorrow at 10 AM.",
    "Can you send me the report?",
    "Don't forget the meeting next week.",
    "I will be out of office on Friday.",
    "Can you review the document I sent?",
    "What do you think about the new project?",
    "I have attached the files you requested.",
    "Please confirm your attendance for the event.",
    "Hello, how are you?",
    "Did you receive my last message?",
    "Let's meet tomorrow at 10 AM.",
    "Can you send me the report?",
    "Don't forget the meeting next week.",
    "I will be out of office on Friday.",
    "Can you review the document I sent?",
    "What do you think about the new project?",
    "I have attached the files you requested.",
    "Please confirm your attendance for the event.",
};

std::vector<QString> test_times = {
    "10:00",
    "10:05",
    "10:10",
    "10:15",
    "10:20",
    "10:25",
    "10:30",
    "10:35",
    "10:40",
    "10:45",
    "10:00",
    "10:05",
    "10:10",
    "10:15",
    "10:20",
    "10:25",
    "10:30",
    "10:35",
    "10:40",
    "10:45"
};