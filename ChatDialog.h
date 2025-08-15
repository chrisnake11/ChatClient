#pragma once

#include <QDialog>
#include <QWidget>
#include <QShowEvent>
#include <QKeyEvent>
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
    void loadChatContact(const QString &name);
    void sendMessage();

signals:
    void messageSent(const QString &contact, const QString &message);

private:
    void loadChatDialogStyle();
    void initChatDialog();
    
    Ui::ChatDialog *ui;

    // 当前选中的联系人
    QString _currentContact;

    QString _currentUsername; // 当前用户的用户名，用于发送消息等操作

};

