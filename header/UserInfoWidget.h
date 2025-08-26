#pragma once
#include <QWidget>
#include <QString>
#include "Data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserInfoWidget; };
QT_END_NAMESPACE

class UserInfoWidget: public QWidget{
    Q_OBJECT
public:
    explicit UserInfoWidget(QWidget *parent = nullptr);
    explicit UserInfoWidget(const UserInfo& user_info, QWidget *parent = nullptr);
    ~UserInfoWidget();

    UserInfo getUserInfo() const { return _user_info; }
    void setUserInfo(const UserInfo& user_info) { _user_info = user_info; }
    void initUI();

public slots:
    void onChatButtonClicked();

signals:
    void chatWithUser(const int& uid);
private:
	Ui::UserInfoWidget *ui;
    void setDefaultAvatar();
    UserInfo _user_info;
};