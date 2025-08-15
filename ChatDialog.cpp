#include "ChatDialog.h"
#include "ui_ChatDialog.h"
#include "ContactListWidget.h"
#include <QScrollBar>
#include <QFile>
#include <QDebug>
#include <QTime>
#include "global.h"
#include <QApplication>

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
{
    ui->setupUi(this);    
    
    // 设置联系人列表的滚动区域，绑定滚动加载事件。
    ui->contact_list->setScrollArea(ui->contact_scroll);
    // 设置聊天内容区域的滚动区域，绑定滚动加载事件。
    ui->chat_content->setScrollArea(ui->chat_scroll);

    // 让QDialog降级为自定义无边框的QWidget窗口，嵌入到主窗口中。
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    
    // 加载聊天对话框专用qss样式
    initChatDialog();

    // 连接联系人点击加载聊天界面
    connect(ui->contact_list, &ContactListWidget::contactClicked, 
        this, &ChatDialog::loadChatContact);
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

void ChatDialog::loadChatContact(const QString &name)
{
    qDebug() << "Loading chat for contact:" << name;
    _currentContact = name;
    ui->chat_title->setText(name);
    // 读取状态
    ui->chat_status->setText("在线");
    ui->chat_status->setStyleSheet("color: green;");
    // TODO: Load chat history for the selected contact

}

void ChatDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        event->ignore();
        return;
    }
    QDialog::keyPressEvent(event);
}