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
#include "NewFriendItem.h"
#include "NewFriendWidget.h"

ChatDialog::ChatDialog(QWidget* parent)
	: QDialog(parent), _currentListLabel(nullptr)
    , ui(new Ui::ChatDialog)
{
    ui->setupUi(this);  
    
    // 设置联系人列表的滚动区域，绑定滚动加载事件。
    ui->message_list->setScrollArea(ui->message_scroll);
    // 设置聊天内容区域的滚动区域，绑定滚动加载事件。
    ui->chat_content->setScrollArea(ui->chat_scroll);
    ui->contact_list->setScrollArea(ui->contact_scroll);
    ui->new_friend_list->setScrollArea(ui->new_friend_scroll);

    // 让QDialog降级为自定义无边框的QWidget窗口，嵌入到主窗口中。
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    
    // 加载聊天对话框样式
    initChatDialog();

    // 界面切换事件
    connect(ui->msg_list_btn, &ClickedLabel::clicked, this, &ChatDialog::switchToMessage);
    connect(ui->contact_list_btn, &ClickedLabel::clicked, this, &ChatDialog::switchToContact);

    // 请求聊天记录
    connect(ui->message_list, &MessageListWidget::messageClicked, 
        this, &ChatDialog::loadChatInfo);
    connect(TcpManager::getInstance().get(), &TcpManager::getChatMessageList,
        this, &ChatDialog::loadChatFrame); 
    connect(this, &ChatDialog::loadChatMessageList, ui->chat_content, &ChatListWidget::loadChatMessageList);
    // 点击联系人
    connect(ui->contact_list, &ContactListWidget::contactClicked, this, &ChatDialog::loadContactInfo);


    
    // 搜索框事件
    connect(ui->search_edit, &QLineEdit::textChanged, this, &ChatDialog::searchContact);

    connect(ui->add_contact_btn, &QPushButton::clicked, this, &ChatDialog::openAddContactDialog);

    // 好友请求界面
    connect(ui->contact_notification_label, &ClickedLabel::clicked, this, &ChatDialog::switchToNewFriendUI);
    
    // 好友请求
    connect(ui->new_friend_list, &NewFriendWidget::acceptNewFriend, this, &ChatDialog::acceptNewFriend);
    connect(ui->new_friend_list, &NewFriendWidget::rejectNewFriend, this, &ChatDialog::rejectNewFriend);
    connect(this, &ChatDialog::acceptNewFriendSuccess, ui->new_friend_list, &NewFriendWidget::onAcceptNewFriendSuccess);
    connect(this, &ChatDialog::rejectNewFriendSuccess, ui->new_friend_list, &NewFriendWidget::onRejectNewFriendSuccess);

    // 消息发送事件
    connect(ui->send_btn, &QPushButton::clicked, this, &ChatDialog::onSendMessage);
    connect(TcpManager::getInstance().get(), &TcpManager::sentChatMessageSuccess, ui->chat_content, &ChatListWidget::addSingleMessage);
    connect(TcpManager::getInstance().get(), &TcpManager::receiveChatMessage, ui->chat_content, &ChatListWidget::addSingleMessage);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::initChatDialog()
{
    // 读取style文件
    QFile styleFile(":/styles/chat_dialog.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        this->setStyleSheet(style);
        styleFile.close();
        qDebug() << "Chat dialog style loaded successfully";
    }
    else {
        qDebug() << "Failed to load chat_dialog.qss from resources";
    }

    // 设置侧边栏
    _currentListLabel = ui->msg_list_btn;
    ui->msg_list_btn->setState(WidgetMouseState::SELECTED);
    // 设置中间堆栈窗口为消息页面
    ui->mid_stack_widget->setCurrentWidget(ui->message_page);
    // 隐藏右边界面
    ui->right_widget->setCurrentWidget(ui->chat_page);
    ui->chat_header->hide();
    ui->chat_content->hide();
    ui->input_widget->hide();

    QString username = UserManager::getInstance()->getUsername();
    ui->user_avatar->setText(username);
}

void ChatDialog::loadChatInfo(const int& uid, const int& friend_uid)
{
    QJsonObject obj;
    obj["uid"] = uid;
    obj["friend_uid"] = friend_uid;
    QString token = UserManager::getInstance()->getToken();
    obj["token"] = token;
    QJsonDocument doc(obj);
    // 发送ChatMessage列表请求
    TcpManager::getInstance()->slot_send_data(ID_GET_CHAT_MESSAGE, doc.toJson());
}

// 聊天界面，读取聊天对象的用户名
void ChatDialog::loadChatFrame(const int& uid, const int& friend_uid, std::shared_ptr<std::vector<ChatMessageInfo>> message_list)
{
    ui->chat_header->show();
    ui->chat_content->show();
    ui->input_widget->show();

    setFriendUid(friend_uid);

    // 获取uid对应的好友信息
    std::shared_ptr<UserInfo> user_info = UserManager::getInstance()->getFriendInfo(friend_uid);
    if (user_info == nullptr) {
        std::cout << "UserManager friend " << uid << " not found" << std::endl;
        return;
    }
    // 获取用户数据
    QString name = user_info->nickname;
    int online_status = user_info->onlineStatus;
    qDebug() << "Loading chat for contact: " << uid << ", " << name;

    ui->chat_title->setText(name);
    // 设置用户在线状态
    if (online_status) {
        ui->chat_status->setText("在线");
        ui->chat_status->setStyleSheet("color: green;");
    }
    else {
        ui->chat_status->setText("离线");
        ui->chat_status->setStyleSheet("color: red;");
    }
    // 加载消息列表
    emit loadChatMessageList(message_list);
    // 加载聊天界面的同时，切换到消息列表
    switchToMessage();
}

void ChatDialog::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        event->ignore();
        return;
    }
    QDialog::keyPressEvent(event);
}

void ChatDialog::onSendMessage() {
    QString message = ui->send_edit->toPlainText();
    if (message.isEmpty()) {
        return;
    }
    // 发送消息，清除发送框。
    int uid = UserManager::getInstance()->getUid();
    int friend_uid = getFriendUid();
    ui->send_edit->clear();
    QJsonObject obj;
    obj["token"] = UserManager::getInstance()->getToken();
    obj["uid"] = uid;
    obj["friend_uid"] = friend_uid;
    obj["message"] = message;
    obj["message_time"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    obj["message_type"] = "text";
    QJsonDocument doc(obj);
    TcpManager::getInstance()->slot_send_data(ID_SEND_CHAT_MESSAGE, doc.toJson());
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
    // 重新选择列表按钮
    clearListState();
    _currentListLabel = ui->msg_list_btn;
    _currentListLabel->setState(WidgetMouseState::SELECTED);
    // 显示对应界面
    ui->mid_stack_widget->setCurrentWidget(ui->message_page);
    ui->right_widget->setCurrentWidget(ui->chat_page);
}

void ChatDialog::loadContactInfo(const int &uid)
{
    qDebug() << "Loading contact info for uid: " << uid;
    // TODO: Load contact information for the selected contact
    std::shared_ptr<UserInfo> userinfo = UserManager::getInstance()->getUserInfo(uid);
    UserInfoWidget* userInfoWidget = new UserInfoWidget(*userinfo, ui->userinfo_page);
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

// 用户界面，点击聊天按钮
void ChatDialog::chatWithUser(const int& uid)
{
    // 设置当前聊天对象为点击的uid用户。
    ui->message_list->setCurrentMessage(ui->message_list->findMessageItem(uid));
    // 切换到Message列表
    switchToMessage();
}

void ChatDialog::openAddContactDialog(){
    AddFriendDialog *dialog = new AddFriendDialog(this);
    // 
    connect(dialog, &AddFriendDialog::addUser, this, &ChatDialog::addNewFriend);
    dialog->exec();
}

void ChatDialog::addNewFriend(const int& uid, const QString& username, const QString& message){
    // 发送添加好友请求
    qDebug() << "Sending add friend request for:" << username;
    // 假设成功，添加到new_friend列表
    NewFriendItem *item = new NewFriendItem(true, false, ui->new_friend_list);
    item->setInfo(uid, username, "", message);
    ui->new_friend_list->addNewFriendItem(item);
    // 添加到联系人列表。
    std::unique_ptr<UserInfo> user_info = std::make_unique<UserInfo>();
    user_info->uid = uid;
    user_info->username = username;
    addUser(user_info);
}

// 新加用户到联系人列表
void ChatDialog::addUser(std::unique_ptr<UserInfo>& user_info){
    ContactItem *item = new ContactItem(ui->contact_list);
    // 测试代码
    item->setInfo(user_info->uid, user_info->username, "", "", 0);
    // 添加用户到联系人列表
    ui->contact_list->addContact(item);
}

void ChatDialog::switchToNewFriendUI(){
    qDebug() << "Switching to new friend UI";
    // right_widget切换到新好友页面
    ui->right_widget->setCurrentWidget(ui->new_friend_page);
}

void ChatDialog::acceptNewFriend(const QString& requester){
    // 发送信号
    qDebug() << UserManager::getInstance()->getUsername() << " accept " << requester << " request";
    emit acceptNewFriendSuccess(requester);
}

void ChatDialog::rejectNewFriend(const QString& requester){
    qDebug() << UserManager::getInstance()->getUsername() << " reject " << requester << " request";
    emit rejectNewFriendSuccess(requester);
}