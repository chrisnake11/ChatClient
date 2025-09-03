#include "MessageListWidget.h"
#include "global.h"
#include <QScrollBar>
#include <QStyleOption>
#include <QPainter>
#include <QJSonDocument>
#include "UserManager.h"
#include "TcpManager.h"

MessageListWidget::MessageListWidget(QWidget *parent)
    : QWidget(parent),
      _contentLayout(nullptr), _scrollArea(nullptr), _currentSelectedMessage(nullptr)
{
    setupUI();
    initMessageList();
    connect(TcpManager::getInstance().get(), &TcpManager::getMessageInfoList, this, &MessageListWidget::loadMessageList);
}

MessageListWidget::~MessageListWidget()
{
    clearMessages();
}

void MessageListWidget::setupUI()
{
    // 创建主布局
    _contentLayout = new QVBoxLayout(this);
    _contentLayout->setContentsMargins(0, 0, 0, 0);
    _contentLayout->setSpacing(0);
    // 设置布局对齐
    _contentLayout->setAlignment(Qt::AlignTop);

    setLayout(_contentLayout);

    setMouseTracking(true);
}

void MessageListWidget::addMessage(MessageItem *item){
    // 检查是否已存在该消息
    int uid = item->getUid();
    if (findMessageItem(uid) != nullptr) {
        qDebug() << "Message already exists. uid:" << uid;
        return;
    }

    // 连接点击信号
    connect(item, &MessageItem::messageClicked, this, &MessageListWidget::setCurrentMessage);
    // 添加到布局
    _contentLayout->insertWidget(_contentLayout->count(), item);

    _messageItems.append(item);
    qDebug() << "Added message:" << item->getName();
}

void MessageListWidget::updateMessage(MessageItem *item, const int& uid, const QString &name, const QString &message, const QString &time, int unreadCount)
{
    if (item) {
        item->setInfo(uid, name, item->getAvatarPath(), message, time);
        qDebug() << "Updated message:" << name;
    } else {
        qDebug() << "Message not found for update:" << name;
    }
}

void MessageListWidget::clearMessages()
{
    for (MessageItem *item : _messageItems) {
        _contentLayout->removeWidget(item);
        item->deleteLater();
    }
    _messageItems.clear();
    _currentSelectedMessage = nullptr;
}


void MessageListWidget::setCurrentMessage(MessageItem *item)
{
    // 如果点击的是当前选中项，则不处理
    if (item == _currentSelectedMessage) {
        return;
    }
    // 清除之前的选中状态
    if (_currentSelectedMessage) {
        _currentSelectedMessage->setState(WidgetMouseState::NORMAL);
    }

    // 记录当前选中消息
    if (item) {
        item->setState(WidgetMouseState::SELECTED);
        _currentSelectedMessage = item;
        // 发送信号，通知ChatWidget
        qDebug() << "MessageListWidget send messageClicked signal for:" << item->getName();
        int uid = UserManager::getInstance()->getUid();
        int friend_uid = item->getUid();
        // 发送消息点击信号，触发TcpManager发送消息
        emit messageClicked(uid, friend_uid);
    }
}


void MessageListWidget::initMessageList(){
    // 加载消息数据，向服务器请求数据
    auto uid = UserManager::getInstance()->getUid();
    auto token = UserManager::getInstance()->getToken();
    QJsonObject root;
    root["uid"] = uid;
    root["token"] = token;
    QJsonDocument doc(root);
    QString doc_str = doc.toJson(QJsonDocument::Indented);
    TcpManager::getInstance()->sig_send_data(RequestID::ID_GET_MESSAGE_LIST, doc_str);
}

void MessageListWidget::loadMessageList(std::shared_ptr<std::vector<MessageItemInfo>> message_list)
{
    qDebug() << "MessageListWidget receive messageList:" << (*message_list).size();

    for (auto& item : *message_list) {
        MessageItem* messageItem = new MessageItem(this);
        messageItem->setInfo(item.uid, item.nickname, item.avatar, item.message, item.lastMessageTime);
        addMessage(messageItem);
    }
}

void MessageListWidget::setScrollArea(QScrollArea *scrollArea)
{
    _scrollArea = scrollArea;
    // 绑定动态加载事件
    //connect(_scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &MessageListWidget::loadMessageList);
}

MessageItem* MessageListWidget::findMessageItem(const int &uid)
{
    for (MessageItem *item : _messageItems) {
        if (item->getUid() == uid) {
            return item;
        }
    }
    return nullptr;
}

void MessageListWidget::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}

void MessageListWidget::searchMessage(const QString &text){
    for (MessageItem *item : _messageItems) {
        if (item->getName().contains(text, Qt::CaseInsensitive)) {
            item->show();
        } else {
            item->hide();
        }
    }
    updateGeometry();
}