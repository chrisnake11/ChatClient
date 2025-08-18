#include "ChatDialog.h"
#include "ui_ChatDialog.h"
#include <QScrollBar>
#include <QFile>
#include <QDebug>
#include <QTime>
#include <QApplication>
#include "global.h"
#include "MessageListWidget.h"
#include "UserInfoWidget.h"
#include "AddFriendDialog.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
{
    ui->setupUi(this);    
    
    // 设置联系人列表的滚动区域，绑定滚动加载事件。
    ui->message_list->setScrollArea(ui->message_scroll);
    // 设置聊天内容区域的滚动区域，绑定滚动加载事件。
    ui->chat_content->setScrollArea(ui->chat_scroll);
    ui->contact_list->setScrollArea(ui->contact_scroll);

    // 让QDialog降级为自定义无边框的QWidget窗口，嵌入到主窗口中。
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    
    // 加载聊天对话框专用qss样式
    initChatDialog();

    // 界面切换事件
    connect(ui->msg_list_btn, &ClickedLabel::clicked, this, &ChatDialog::switchToMessage);
    connect(ui->contact_list_btn, &ClickedLabel::clicked, this, &ChatDialog::switchToContact);

    // 聊天消息加载事件
    connect(ui->message_list, &MessageListWidget::messageClicked, 
        this, &ChatDialog::loadChatMessage);
    // 联系人信息加载事件
    connect(ui->contact_list, &ContactListWidget::contactClicked, this, &ChatDialog::loadContactInfo);

    // 消息发送事件
    connect(ui->send_btn, &QPushButton::clicked, this, &ChatDialog::sendMessage);
    connect(this, &ChatDialog::messageSent, ui->chat_content, &ChatListWidget::onMessageSent);
    
    // 搜索框事件
    connect(ui->search_edit, &QLineEdit::textChanged, this, &ChatDialog::searchContact);

    connect(ui->add_contact_btn, &QPushButton::clicked, this, &ChatDialog::openAddContactDialog);

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
    ui->right_widget->setCurrentWidget(ui->chat_page);

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

void ChatDialog::searchContact(){
    QString searchText = ui->search_edit->text();
    // 调用联系人列表的搜索功能
    ui->contact_list->searchContact(searchText);
    switchToContact();
}

void ChatDialog::clearListState(){
    // 清空联系人列表的选中状态
    _currentListLabel->setState(WidgetMouseState::NORMAL);
}

void ChatDialog::switchToContact(){
    clearListState();
    _currentListLabel = ui->contact_list_btn;
    _currentListLabel->setState(WidgetMouseState::SELECTED);
    ui->mid_stack_widget->setCurrentWidget(ui->contact_page);
    ui->right_widget->setCurrentWidget(ui->userinfo_page);
}

void ChatDialog::switchToMessage(){
    clearListState();
    _currentListLabel = ui->msg_list_btn;
    _currentListLabel->setState(WidgetMouseState::SELECTED);
    ui->mid_stack_widget->setCurrentWidget(ui->message_page);
    ui->right_widget->setCurrentWidget(ui->chat_page);
}

    void ChatDialog::loadContactInfo(const QString &name)
    {
        qDebug() << "Loading contact info for:" << name;
        // TODO: Load contact information for the selected contact
        UserInfo userInfo(1001, 1, 18, "", name, "beijing", "hello,world!", true);
        UserInfoWidget* userInfoWidget = new UserInfoWidget(userInfo, ui->userinfo_page);
        userInfoWidget->setFixedSize(400, 500);
        // 删除旧的用户信息控件
        if(ui->userinfo_layout->count() != 0){
            QWidget* oldWidget = ui->userinfo_layout->itemAt(0)->widget();
            if(oldWidget){
                oldWidget->deleteLater();
            }
        }

        // 添加新的用户信息控件
        ui->userinfo_layout->addWidget(userInfoWidget, 1, Qt::AlignHCenter);
        connect(userInfoWidget, &UserInfoWidget::chatWithUser, this, &ChatDialog::chatWithUser);
        ui->right_widget->setCurrentWidget(ui->userinfo_page);
}

void ChatDialog::chatWithUser(const QString& name){
    MessageItem * item = ui->message_list->findMessageItem(name);
    // 创建新的message item
    if(item == nullptr){
        // 获取当前时间
        QString time_str = QDateTime::currentDateTime().toString("hh:mm");
        // 父元素绑定message_list
        item = new MessageItem(ui->message_list);
        item->setInfo(name, ":/images/wechat.png", "", time_str);
        ui->message_list->addMessage(item);
    }
    // 设置选中的message item
    ui->message_list->setCurrentMessage(item);

    // 根据当前message item加载聊天内容
    loadChatMessage(name);

    // 显示聊天界面
    switchToMessage();
}


void ChatDialog::openAddContactDialog(){
    AddFriendDialog *dialog = new AddFriendDialog(this);
    connect(dialog, &AddFriendDialog::addUser, this, &ChatDialog::addUser);
    dialog->exec();
}

// 新加用户到联系人列表
void ChatDialog::addUser(const UserInfo& user_info){
    ContactItem *item = new ContactItem(this);
    item->setInfo(user_info.username, "", "");
    // 添加用户到联系人列表
    ui->contact_list->addContact(item);
}
