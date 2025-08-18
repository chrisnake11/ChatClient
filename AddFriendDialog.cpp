#include "AddFriendDialog.h"
#include "ui_addfrienddialog.h"
#include "ChatDialog.h"
#include "UserInfo.h"
#include <QMessageBox>

AddFriendDialog::AddFriendDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddFriendDialog)
{
    ui->setupUi(this);
    connect(ui->add_user_btn, &QPushButton::clicked, this, &AddFriendDialog::onAddUserButtonClicked);
}

AddFriendDialog::~AddFriendDialog(){
    delete ui;
}

void AddFriendDialog::onAddUserButtonClicked(){
    QString name = ui->user_name_edit->text();
    
    // 向服务器发送添加好友请求。
    
    // 假设发送添加请求成功，返回用户数据
    UserInfo user_info(1, 1, 18, "", "new_user", "jiangsu", "hello new world", false);

    // 提示添加用户成功
    QMessageBox::information(this, "Success",  user_info.username + " added successfully!");

    // 更新客户端
    emit addUser(user_info);
}
