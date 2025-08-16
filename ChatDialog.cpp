#include "ChatDialog.h"
#include "ui_ChatDialog.h"
#include <QScrollBar>
#include <QFile>
#include <QDebug>
#include <QTime>
#include <QApplication>
#include "global.h"
#include "MessageListWidget.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
{
    ui->setupUi(this);    
    
    // 设置联系人列表的滚动区域，绑定滚动加载事件。
    ui->message_list->setScrollArea(ui->contact_scroll);
    // 设置聊天内容区域的滚动区域，绑定滚动加载事件。
    ui->chat_content->setScrollArea(ui->chat_scroll);

    // 让QDialog降级为自定义无边框的QWidget窗口，嵌入到主窗口中。
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    
    // 加载聊天对话框专用qss样式
    initChatDialog();

    // 连接消息点击加载聊天界面
    connect(ui->message_list, &MessageListWidget::messageClicked, 
        this, &ChatDialog::loadChatMessage);

    connect(ui->send_btn, &QPushButton::clicked, this, &ChatDialog::sendMessage);
    connect(this, &ChatDialog::messageSent, ui->chat_content, &ChatListWidget::onMessageSent);
    connect(ui->search_edit, &QLineEdit::textChanged, this, &ChatDialog::searchMessage);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::initChatDialog()
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

    _currentListLabel = ui->msg_list_btn;
    ui->msg_list_btn->setState(WidgetMouseState::SELECTED);

    // 设置中间堆栈窗口为消息页面
    ui->mid_stack_widget->setCurrentWidget(ui->message_page);
}

void ChatDialog::loadChatMessage(const QString &name)
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

void ChatDialog::sendMessage(){
    QString message = ui->send_edit->toPlainText();
    if (message.isEmpty()) {
        return;
    }
    // TODO: Send the message to the current contact
    emit messageSent(_currentContact, message);
    ui->send_edit->clear();
    
}

void ChatDialog::searchMessage(){
    QString searchText = ui->search_edit->text();
    // 调用联系人列表的搜索功能
    ui->message_list->searchMessage(searchText);
}