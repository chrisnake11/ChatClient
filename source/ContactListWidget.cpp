#include "ContactListWidget.h"
#include "global.h"
#include <QScrollBar>
#include <QStyleOption>
#include <QPainter>
#include "UserManager.h"
#include "TcpManager.h"
#include <QJsonDocument>

ContactListWidget::ContactListWidget(QWidget *parent)
    : QWidget(parent),
      _contentLayout(nullptr), _scrollArea(nullptr), _currentSelectedContact(nullptr)
{
    setupUI();
    initContactList();
    connect(TcpManager::getInstance().get(), &TcpManager::getContactInfoList, this, &ContactListWidget::loadContactList);

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

void ContactListWidget::addContact(ContactItem* item){
    // 检查是否已存在该消息
    if (findContactItem(item->getName()) != nullptr) {
        qDebug() << "Contact already exists for sender:" << item->getName();
        return;
    }
    // 连接点击信号
    connect(item, &ContactItem::contactClicked, this, &ContactListWidget::setCurrentContact);
    // 添加到布局
    _contentLayout->insertWidget(_contentLayout->count(), item);

    _contactItems.append(item);
    qDebug() << "Added contact:" << item->getName();
}

void ContactListWidget::updateContact(ContactItem *item, const int& uid, const QString &name, const QString &message)
{
    if (item) {
        item->setInfo(uid, name, item->getAvatarPath(), message);
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

    // 记录当前选中消息
    if (item) {
        item->setState(WidgetMouseState::SELECTED);
        _currentSelectedContact = item;
        // 发送信号，通知ChatWidget
        qDebug() << "ContactListWidget send contactClicked signal for:" << item->getName();
        emit contactClicked(item->getUid());
    }
}


void ContactListWidget::initContactList(){
    // 加载消息数据
    int uid = UserManager::getInstance()->getUid();
    QString token = UserManager::getInstance()->getToken();
    QJsonObject root;
    root["uid"] = uid;
    root["token"] = token;
    QJsonDocument doc(root);
    QString json_str = doc.toJson();
    // 发送联系人列表请求
    TcpManager::getInstance()->sig_send_data(RequestID::ID_GET_CONTACT_LIST, json_str);
}

void ContactListWidget::loadContactList(std::shared_ptr<std::vector<ContactItemInfo>> contact_list) {
    qDebug() << "load ContactList, size: " << (*contact_list).size();
    for (auto& item : *contact_list) {
        ContactItem* contact_item = new ContactItem(this);
        contact_item->setInfo(item.uid, item.nickname, item.avatar, item.sign);
        addContact(contact_item);
    }
}

void ContactListWidget::setScrollArea(QScrollArea *scrollArea)
{
    _scrollArea = scrollArea;
    // 绑定动态加载事件
    /*connect(_scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, &ContactListWidget::loadContactList);*/
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
