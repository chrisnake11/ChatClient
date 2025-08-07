#include "ChatDialog.h"
#include "ui_ChatDialog.h"
#include "ContactListWidget.h"
#include <QScrollBar>
#include <QFile>
#include <QDebug>
#include <QTime>
#include "global.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    // 加载聊天对话框专用qss样式
    initChatDialog();

    // 初始化联系人列表
    initContactList();
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::loadChatDialogStyle()
{
    QFile styleFile(":/styles/chat_dialog.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        this->setStyleSheet(style);
        styleFile.close();
        qDebug() << "Chat dialog style loaded successfully";
    } else {
        qDebug() << "Failed to load chat_dialog.qss from resources";
    }
}


void ChatDialog::initChatDialog()
{
    // 初始化聊天对话框的UI和其他设置
    loadChatDialogStyle();
}

void ChatDialog::initContactList()
{
    // 设置contact_list的滚动条
    // ui->contact_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->contact_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < 20; ++i){
        ui->contact_list->addContact(test_users[i], ":/images/wechat.png", test_messages[i], test_times[i]);
    }

    connect(ui->contact_scroll->verticalScrollBar(), &QScrollBar::valueChanged,
        this, &ChatDialog::updateContactList);
}

void ChatDialog::updateContactList(int value)
{
    // 更新联系人列表
    
}   