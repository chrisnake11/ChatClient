#include "ChatListWidget.h"
#include <QScrollBar>
#include <QTimer>
#include "UserManager.h"

ChatListWidget::ChatListWidget(QWidget *parent)
    : QWidget(parent), _layout(new QVBoxLayout(this)), _scrollArea(nullptr)
{
    qDebug() << "ChatListWidget created";
    _layout->setContentsMargins(20, 20, 20, 20);
    _layout->setAlignment(Qt::AlignTop);
    setLayout(_layout);
    setMouseTracking(true);
}

ChatListWidget::~ChatListWidget()
{
}

void ChatListWidget::clear() {
    QLayoutItem* item;
    while ((item = _layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();  // 删除其中的控件
        }
        delete item;  // 删除布局项本身
    }
}

void ChatListWidget::addChatItemBack(QWidget* chat_item)
{
    _layout->insertWidget(_layout->count(), chat_item);
}

void ChatListWidget::addChatItemFront(QWidget* chat_item)
{
    _layout->insertWidget(0, chat_item);
}

void ChatListWidget::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}

void ChatListWidget::setScrollArea(CustomScrollArea* scrollArea)
{
    _scrollArea = scrollArea;
    // 设置scrollArea后，自动滚动到底部
    if(_scrollArea){
        _scrollArea->verticalScrollBar()->setValue(_scrollArea->verticalScrollBar()->maximum());
        // 如果scrollArea向上滚动到头，就在头部添加ChatBubble
        connect(_scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &ChatListWidget::onScrollBarValueChanged);
    }
}

void ChatListWidget::onScrollBarValueChanged(int value)
{
    if (value == 0) {
        // 在头部添加ChatBubble
        auto chat_item = new ChatItem(true, this);
        chat_item->setName("Me");
        chat_item->setMessageBubble(new TextBubble("New message at the top"));
        chat_item->setAvatar(":/images/wechat.png");
        addChatItemFront(chat_item);
        _scrollArea->getCustomScrollBar()->setValue(_scrollArea->getCustomScrollBar()->minimum() + 1);
    }
}

void ChatListWidget::loadChatMessageList(std::shared_ptr<std::vector<ChatMessageInfo>> message_list)
{
    // 清空之前的聊天记录，重新加载
    clear();
    // 当前用户id
    int uid = UserManager::getInstance()->getUid();
    if (message_list) {
        for (auto& message : *message_list) {
            // 发送者的id
            int sender_id = message.sender_id;
            // 生成chat_item和bubble
            ChatItem* chat_item = new ChatItem(sender_id == uid, this);
            std::shared_ptr<UserInfo> sender;
            auto text_bubble = new TextBubble(message.message);
            // 根据是否为当前用户发送，生成不同的chat_item
            if (sender_id == uid) {
                sender = UserManager::getInstance()->getUserInfo(sender_id);
            }
            else {
                sender = UserManager::getInstance()->getFriendInfo(sender_id);
            }
            chat_item->setName(sender->nickname);
            chat_item->setAvatar(sender->avatar);
            chat_item->setMessageBubble(text_bubble);
            addChatItemBack(chat_item);
        }
    }
    _scrollArea->getCustomScrollBar()->setValue(_scrollArea->getCustomScrollBar()->maximum());
}

void ChatListWidget::addSingleMessage(std::shared_ptr<ChatMessageInfo> message)
{
    qDebug() << "Message add from " << message->sender_id << " to " << message->receiver_id << " : " << message->message;
    int uid = UserManager::getInstance()->getUid();
    ChatItem* chatItem = nullptr;
    if (message->sender_id == uid) {
        chatItem = new ChatItem(true, this);
        chatItem->setName(UserManager::getInstance()->getUsername());
        chatItem->setAvatar(":/images/wechat.png");
    }
    else {
        chatItem = new ChatItem(false, this);
        chatItem->setName(UserManager::getInstance()->getFriendInfo(message->sender_id)->nickname);
        chatItem->setAvatar(":/images/wechat.png");
    }
    TextBubble* textBubble = new TextBubble(message->message, chatItem);
    chatItem->setMessageBubble(textBubble);
    addChatItemBack(chatItem);
    // 强制更新布局，会自动通知QScrollArea更新
    updateGeometry();
    // 延迟滚动到底部
    QTimer::singleShot(0, this, [this]() {
        _scrollArea->getCustomScrollBar()->setValue(_scrollArea->getCustomScrollBar()->maximum());
        });
}