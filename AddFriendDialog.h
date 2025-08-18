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
    void addUser(const UserInfo& userInfo);

private:
    Ui::AddFriendDialog *ui;
};