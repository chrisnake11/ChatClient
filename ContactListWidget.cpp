#include "ContactListWidget.h"
#include "global.h"
#include <QScrollBar>
#include <QStyleOption>
#include <QPainter>

ContactListWidget::ContactListWidget(QWidget *parent)
    : QWidget(parent),
      _contentLayout(nullptr), _scrollArea(nullptr), _currentSelectedContact(nullptr)
{
    setupUI();
    initContactList();

}

ContactListWidget::~ContactListWidget()
{
    clearContacts();
}

void ContactListWidget::setupUI()
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

void ContactListWidget::addContact(const QString &name, const QString &avatarPath, 
                                 const QString &message, const QString &time)
{
    // 检查是否已存在该联系人
    if (findContactItem(name) != nullptr) {
        qDebug() << "Contact already exists:" << name;
        return;
    }
    
    // 创建新的联系人项目
    ContactItem *contactItem = new ContactItem(this);
    // 连接点击信号
    connect(contactItem, &ContactItem::contactClicked, this, &ContactListWidget::setCurrentContact);
    contactItem->setInfo(name, avatarPath, message, time);
    // 添加到布局
    _contentLayout->insertWidget(_contentLayout->count(), contactItem);

    _contactItems.append(contactItem);    
    qDebug() << "Added contact:" << name;
}

void ContactListWidget::updateContact(ContactItem *item, const QString &name, const QString &message, const QString &time, int unreadCount)
{
    if (item) {
        item->setInfo(name, item->getAvatarPath(), message, time);
        qDebug() << "Updated contact:" << name;
    } else {
        qDebug() << "Contact not found for update:" << name;
    }
}

void ContactListWidget::clearContacts()
{
    for (ContactItem *item : _contactItems) {
        _contentLayout->removeWidget(item);
        item->deleteLater();
    }
    _contactItems.clear();
    _currentSelectedContact = nullptr;
}


void ContactListWidget::setCurrentContact(ContactItem *item)
{
    // 如果点击的是当前选中项，则不处理
    if (item == _currentSelectedContact) {
        return;
    }
    // 清除之前的选中状态
    if (_currentSelectedContact) {
        _currentSelectedContact->setState(WidgetMouseState::NORMAL);
    }

    // 记录当前选中联系人
    if (item) {
        item->setState(WidgetMouseState::SELECTED);
        _currentSelectedContact = item;
        // 发送信号，通知ChatWidget
        qDebug() << "ContactListWidget send contactClicked signal for:" << item->getName();
        emit contactClicked(item->getName());
    }
}


void ContactListWidget::initContactList(){
    // 加载联系人数据
    for(int i = 0; i < 20; ++i){
        addContact(test_users[i], ":/images/wechat.png", test_messages[i], test_times[i]);
    }
}

void ContactListWidget::setScrollArea(QScrollArea *scrollArea)
{
    _scrollArea = scrollArea;
    // 绑定动态加载事件
    connect(_scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &ContactListWidget::loadContactList);
}

void ContactListWidget::loadContactList()
{
    // 获取当前滚动条的值
    int scrollValue = _scrollArea->verticalScrollBar()->value();
    int maxScrollValue = _scrollArea->verticalScrollBar()->maximum();

    // 如果滚动条已经到达底部，加载更多联系人
    if (scrollValue == maxScrollValue) {
        int n = _contactItems.size();
        // 从内存中加载20条数据。
        // 假设_contactItems与test_user长度一致。
        for (int i = n; i < n + 20 && i < test_users.size(); ++i) {
            addContact(test_users[i], ":/images/wechat.png", test_messages[i], test_times[i]);
        }
    }
}

ContactItem* ContactListWidget::findContactItem(const QString &name)
{
    for (ContactItem *item : _contactItems) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

void ContactListWidget::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}

void ContactListWidget::searchContact(const QString &text){
    for (ContactItem *item : _contactItems) {
        if (item->getName().contains(text, Qt::CaseInsensitive)) {
            item->show();
        } else {
            item->hide();
        }
    }
    updateGeometry();
}