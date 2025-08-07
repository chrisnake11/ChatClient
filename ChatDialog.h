#pragma once

#include <QDialog>
#include <QWidget>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();
public slots:
    void updateContactList(int value);

private:
    void loadChatDialogStyle();
    void initChatDialog();
    void initContactList();
    
    Ui::ChatDialog *ui;

    // 当前选中的联系人
    QString _currentContact;

    QString _currentUsername; // 当前用户的用户名，用于发送消息等操作

};

