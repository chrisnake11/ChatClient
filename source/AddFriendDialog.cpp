#include "AddFriendDialog.h"
#include "ui_addfrienddialog.h"
#include "ChatDialog.h"
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

    // 提示添加用户成功

    // 发送添加用户信号
    emit addUser(1, "zheyvc", "hello new world");
}
