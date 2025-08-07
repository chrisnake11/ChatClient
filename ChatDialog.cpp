#include "ChatDialog.h"
#include "ui_ChatDialog.h"
#include "ContactListWidget.h"
#include <QFile>
#include <QDebug>
#include <QTime>
#include "global.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    qDebug() << "contact_widget width:" << ui->contact_widget->width();
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    
    // 加载聊天对话框专用qss样式
    initChatDialog();
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
}