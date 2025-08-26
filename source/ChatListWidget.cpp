#include "ChatListWidget.h"
#include <QScrollBar>
#include <QTimer>
ChatListWidget::ChatListWidget(QWidget *parent)
    : QWidget(parent), _layout(new QVBoxLayout(this)), _scrollArea(nullptr)
{
    qDebug() << "ChatListWidget created";
    _layout->setContentsMargins(20, 20, 20, 20);
    _layout->setAlignment(Qt::AlignTop);
    setLayout(_layout);
    loadChatHistory();
    setMouseTracking(true);
}

ChatListWidget::~ChatListWidget()
{
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
        connect(this, &ChatListWidget::messageSent, this, [this]() {
            if (_scrollArea) {
                qDebug() << "_scrollbar max" <<  _scrollArea->verticalScrollBar()->maximum();
            }
        });
    }
}

void ChatListWidget::onScrollBarValueChanged(int value)
{
    if (value == 0) {
        // 在头部添加ChatBubble
        auto chat_item = new ChatItem(true, this);
        chat_item->setName("Me");
        chat_item->setMessageBubble(new TextBubble(true,"New message at the top"));
        chat_item->setAvatar(":/images/wechat.png");
        addChatItemFront(chat_item);
        _scrollArea->getCustomScrollBar()->setValue(_scrollArea->getCustomScrollBar()->minimum() + 1);
    }
}

void ChatListWidget::loadChatHistory()
{
    for(int i = 0; i < 20; i = i + 2){
        auto chat_item1 = new ChatItem(true, this);
        auto text_bubble1 = new TextBubble(true, test_messages[i] + " from this");
        auto chat_item2 = new ChatItem(false, this);
        auto text_bubble2 = new TextBubble(false, test_messages[i + 1] + " from other");
        chat_item1->setName("Me");
        chat_item1->setAvatar(":/images/wechat.png");
        chat_item1->setMessageBubble(text_bubble1);
        addChatItemBack(chat_item1);

        chat_item2->setName("Other");
        chat_item2->setAvatar(":/images/wechat.png");
        chat_item2->setMessageBubble(text_bubble2);
        addChatItemBack(chat_item2);
    }
}

void ChatListWidget::onMessageSent(const QString &contact, const QString &message)
{
    qDebug() << "Message sent to" << contact << ":" << message;
    // TODO: Add the message to the chat history
    auto chat_item = new ChatItem(true, this);
    chat_item->setName("Me");
    chat_item->setMessageBubble(new TextBubble(true, message));
    chat_item->setAvatar(":/images/wechat.png");
    addChatItemBack(chat_item);
    // 强制更新布局，会自动通知QScrollArea更新
    updateGeometry();
    // 滚动到底部
    QTimer::singleShot(0, this, [this]() {
        if (_scrollArea) {
            _scrollArea->getCustomScrollBar()->setValue(_scrollArea->getCustomScrollBar()->maximum());
        }
    });
}