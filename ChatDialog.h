#pragma once

#include <QDialog>
#include <QWidget>
#include <QShowEvent>
#include <QKeyEvent>
#include "SelectedLabel.h"
#include "UserInfo.h"
#include "AddFriendDialog.h"

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void loadChatMessage(const QString &name);
    void sendMessage();
    void chatWithUser(const QString& name);
    void searchContact();
    void clearListState();
    void switchToContact();
    void switchToMessage();
    void loadContactInfo(const QString &name);
    void openAddContactDialog();
    void addUser(const UserInfo& user_info);

signals:
    void messageSent(const QString &contact, const QString &message);

private:
    void initChatDialog();
    Ui::ChatDialog *ui;

    // 当前选中的联系人
    SelectedLabel* _currentListLabel;
    QString _currentContact;
    QString _currentUsername; // 当前用户的用户名，用于发送消息等操作
};

