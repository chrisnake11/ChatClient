#include "MessageListWidget.h"
#include "global.h"
#include <QScrollBar>
#include <QStyleOption>
#include <QPainter>

MessageListWidget::MessageListWidget(QWidget *parent)
    : QWidget(parent),
      _contentLayout(nullptr), _scrollArea(nullptr), _currentSelectedMessage(nullptr)
{
    setupUI();
    initMessageList();

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

void MessageListWidget::addMessage(const QString &name, const QString &avatarPath,
                    const QString &message, const QString &time){
    // 检查是否已存在该消息
    if (findMessageItem(name) != nullptr) {
        qDebug() << "Message already exists for sender:" << name;
        return;
    }

    // 创建新的消息项目
    MessageItem *messageItem = new MessageItem(this);
    // 连接点击信号
    connect(messageItem, &MessageItem::messageClicked, this, &MessageListWidget::setCurrentMessage);
    messageItem->setInfo(name, avatarPath, message, time);
    // 添加到布局
    _contentLayout->insertWidget(_contentLayout->count(), messageItem);

    _messageItems.append(messageItem);
    qDebug() << "Added message:" << name;
}

void MessageListWidget::updateMessage(MessageItem *item, const QString &name, const QString &message, const QString &time, int unreadCount)
{
    if (item) {
        item->setInfo(name, item->getAvatarPath(), message, time);
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
        emit messageClicked(item->getName());
    }
}


void MessageListWidget::initMessageList(){
    // 加载消息数据
    for(int i = 0; i < 20; ++i){
        addMessage(test_users[i], ":/images/wechat.png", test_messages[i], test_times[i]);
    }
}

void MessageListWidget::setScrollArea(QScrollArea *scrollArea)
{
    _scrollArea = scrollArea;
    // 绑定动态加载事件
    connect(_scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &MessageListWidget::loadMessageList);
}

void MessageListWidget::loadMessageList()
{
    // 获取当前滚动条的值
    int scrollValue = _scrollArea->verticalScrollBar()->value();
    int maxScrollValue = _scrollArea->verticalScrollBar()->maximum();

    // 如果滚动条已经到达底部，加载更多消息
    if (scrollValue == maxScrollValue) {
        int n = _messageItems.size();
        // 从内存中加载20条数据。
        // 假设_messageItems与test_user长度一致。
        for (int i = n; i < n + 20 && i < test_users.size(); ++i) {
            addMessage(test_users[i], ":/images/wechat.png", test_messages[i], test_times[i]);
        }
    }
}

MessageItem* MessageListWidget::findMessageItem(const QString &name)
{
    for (MessageItem *item : _messageItems) {
        if (item->getName() == name) {
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