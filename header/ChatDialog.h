#pragma once

#include <QDialog>
#include <QWidget>
#include <QShowEvent>
#include <QKeyEvent>
#include <QString>
#include "SelectedLabel.h"
#include "AddFriendDialog.h"
#include "Data.h"
#include <vector>
#include <memory>
#include "TcpManager.h"
#include "UserManager.h"

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
    void setFriendUid(const int& uid) {
        _friend_uid = uid;
    }
    int getFriendUid() {
        return _friend_uid;
    }

public slots:
    // 清除侧边栏选中状态
    void clearListState();
    // 切换到联系人列表
    void switchToContact();
    // 切换到消息列表
    void switchToMessage();
    // 本地搜索联系人
    void searchContact();
    // 加载联系人个人信息
    void loadContactInfo(const int& uid);
    // 用户信息界面跳转到聊天界面
    void chatWithUser(const int& uid);
    // 打开添加联系人对话框
    void openAddContactDialog();
    
    // 向服务器请求消息
    void loadChatInfo(const int& uid, const int& friend_uid);
    // 加载聊天界面
    void loadChatFrame(const int& uid, const int& friend_uid, std::shared_ptr<std::vector<ChatMessageInfo>>);
    // 发送消息
    void onSendMessage();

    // 添加好友到联系人列表
    void addUser(std::unique_ptr<UserInfo>& user_info);
    void switchToNewFriendUI();
    // 添加到好友请求列表
    void addNewFriend(const int& uid, const QString& username, const QString& message);
    // 接收/拒绝好友请求
    void acceptNewFriend(const QString& requester);
    void rejectNewFriend(const QString& requester);

signals:
    void acceptNewFriendSuccess(const QString& requester);
    void rejectNewFriendSuccess(const QString& requester);
    // 加载和uid用户的聊天信息
    void loadChatMessageList(std::shared_ptr<std::vector<ChatMessageInfo>>);

private:
    void initChatDialog();
    Ui::ChatDialog *ui;

    // 当前选中的联系人
    SelectedLabel* _currentListLabel;
    int _friend_uid;
};

