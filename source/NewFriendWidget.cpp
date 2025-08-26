#include "NewFriendWidget.h"


NewFriendWidget::NewFriendWidget(QWidget *parent)
    : QWidget(parent),
        _layout(nullptr),   
        _scrollArea(nullptr)
{
    initUI();
    loadNewFriendList();
}

NewFriendWidget::~NewFriendWidget()
{
}

void NewFriendWidget::initUI(){
    // 内部添加布局，等待NewFriendItem加入
    _layout = new QVBoxLayout(this);
    _layout->setAlignment(Qt::AlignTop);
    _layout->setContentsMargins(10, 10, 10, 10);
    _layout->setSpacing(10);
    setLayout(_layout);
}

void NewFriendWidget::addNewFriendItem(NewFriendItem* item)
{
    // 在布局的第一个添加
    _layout->insertWidget(0, item);
    // Widget转发好友请求同意/拒绝信号
    connect(item, &NewFriendItem::addFriendAccepted, this, [this](const QString& requester){
        emit acceptNewFriend(requester);
    });
    connect(item, &NewFriendItem::addFriendRejected, this, [this](const QString& requester){
        emit rejectNewFriend(requester);
    });
}

NewFriendItem* NewFriendWidget::findNewFriendItem(const QString& name)
{
    for (int i = 0; i < _layout->count(); ++i) {
        NewFriendItem *item = qobject_cast<NewFriendItem *>(_layout->itemAt(i)->widget());
        if (item && item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}
void NewFriendWidget::setScrollArea(QScrollArea* scrollArea)
{
    _scrollArea = scrollArea;
    // 绑定动态加载事件
    connect(_scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, [this](){
        if (_scrollArea->verticalScrollBar()->value() == _scrollArea->verticalScrollBar()->maximum()) {
            loadNewFriendList();
        }
    });
}

void NewFriendWidget::loadNewFriendList()
{
    // 加载10个元素
    for(int i = 0; i < 10; i++){
        if( i % 2 == 0){
            NewFriendItem* item = new NewFriendItem(true, false, this);
            item->setInfo(1, "test_user" + QString::number(i), "", "i am test_user");
            addNewFriendItem(item);
        }
        else{
            NewFriendItem* item = new NewFriendItem(false, true, this);
            item->setInfo(1, "test_user" + QString::number(i), "", "i am test_user");
            addNewFriendItem(item);
        }
    }
}

void NewFriendWidget::onAcceptNewFriendSuccess(const QString& requester){
    NewFriendItem* item = findNewFriendItem(requester);
    if (item) {
        item->onAcceptFriendSuccess(true);
    }
}

void NewFriendWidget::onRejectNewFriendSuccess(const QString& requester){
    NewFriendItem* item = findNewFriendItem(requester);
    if (item) {
        item->onRejectFriendSuccess(true);
    }
}

void NewFriendWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}