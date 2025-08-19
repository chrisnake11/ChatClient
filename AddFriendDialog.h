#pragma once

#include <QDialog>
#include <QString>
#include "UserInfo.h"

namespace Ui {
class AddFriendDialog;
}

class AddFriendDialog: public QDialog{
    Q_OBJECT
public:
    explicit AddFriendDialog(QWidget *parent = nullptr);
    ~AddFriendDialog();

public slots:
    void onAddUserButtonClicked();

signals:
    // 给ChatDialog发送好友请求信号
    void addUser(const QString& username, const QString& message);

private:
    Ui::AddFriendDialog *ui;
};