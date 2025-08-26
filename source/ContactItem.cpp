#include "ContactItem.h"
#include <QMouseEvent>
#include <QEnterEvent>
#include <QPixmap>
#include <QDebug>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>

ContactItem::ContactItem(QWidget *parent) : QWidget(parent),
                                            _layout(new QHBoxLayout(this)),
                                            _avatarLabel(nullptr),
                                            _nameLabel(nullptr),
                                            _personalSigLabel(nullptr),
                                            _isOnline(false),
                                            _state(WidgetMouseState::NORMAL)
{
    setupUI();
    setProperty("state", "normal");
}

ContactItem::~ContactItem()
{
    // QT 会自动删除子控件
}

void ContactItem::setupUI()
{
    // 设置固定大小 - 增加宽度以容纳所有内容
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // 创建主水平布局
    _layout->setContentsMargins(5, 5, 5, 5);  // 减少左右边距
    _layout->setSpacing(5);

    // 创建头像标签
    _avatarLabel = new QLabel(this);
    _avatarLabel->setFixedSize(40, 40);
    _avatarLabel->setScaledContents(true);
    _avatarLabel->setStyleSheet("border-radius: 20px;"); // 圆形边框

    // 创建中间的垂直布局（用于姓名和消息）
    QVBoxLayout *middleLayout = new QVBoxLayout();
    middleLayout->setContentsMargins(0, 0, 0, 0);
    middleLayout->setSpacing(2);

    // 创建姓名标签
    _nameLabel = new QLabel("contact", this);
    _nameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _nameLabel->setStyleSheet("font-weight: bold; color: #333333; font-size: 12px;");
    
    // 创建个性签名
    QHBoxLayout *sigLayout = new QHBoxLayout();
    sigLayout->setContentsMargins(0, 0, 0, 0);
    sigLayout->setSpacing(5);
    sigLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    
    // 添加在线状态指示
    QLabel* statusIndicator = new QLabel(this);
    statusIndicator->setFixedSize(8, 8);
    QLabel* onlineLabel = new QLabel(this);
    
    if(_isOnline == true){
        statusIndicator->setStyleSheet("background-color: green; border-radius: 4px;");
        onlineLabel->setText("在线");
        onlineLabel->setStyleSheet("color: #666666; font-size: 9px;");
    }
    else{
        statusIndicator->setStyleSheet("background-color: red; border-radius: 4px;");
        onlineLabel->setText("离线");
        onlineLabel->setStyleSheet("color: #666666; font-size: 9px;");
    }

    // 添加个性签名
    _personalSigLabel = new QLabel("message", this);
    _personalSigLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _personalSigLabel->setStyleSheet("color: #666666; font-size: 9px;");

    sigLayout->addWidget(statusIndicator);
    sigLayout->addWidget(onlineLabel);
    sigLayout->addWidget(_personalSigLabel);

    middleLayout->addWidget(_nameLabel);
    middleLayout->addLayout(sigLayout, 1);

    // 添加到主布局 - 调整伸缩因子
    _layout->addWidget(_avatarLabel, 0);          // 头像不伸缩
    _layout->addLayout(middleLayout, 1);          // 中间内容可伸缩
    
    // 设置默认头像
    setDefaultAvatar();

    // 设置鼠标追踪
    setMouseTracking(true);
}

void ContactItem::setInfo(const int& uid, const QString &name, const QString &avatarPath, const QString &message)
{
    _uid = uid;
    _name = name;
    _avatarPath = avatarPath;
    _message = message;
    updateDisplayContent();
}

void ContactItem::setAvatar(const QString &avatarPath)
{
    _avatarPath = avatarPath;
    
    if (!avatarPath.isEmpty() && QFileInfo::exists(avatarPath)) {
        QPixmap pixmap(avatarPath);
        if (!pixmap.isNull()) {
            // 缩放并设置圆形头像
            QPixmap scaledPixmap = pixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::FastTransformation);
            
            // 创建圆形遮罩
            QPixmap roundedPixmap(40, 40);
            roundedPixmap.fill(Qt::transparent);
            
            QPainter painter(&roundedPixmap);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setBrush(QBrush(scaledPixmap));
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(0, 0, 40, 40);
            
            _avatarLabel->setPixmap(roundedPixmap);
            _avatarLabel->setAlignment(Qt::AlignCenter);
        } else {
            setDefaultAvatar();
        }
    } else {
        setDefaultAvatar();
    }
}

void ContactItem::setDefaultAvatar()
{
    // 设置默认头像
    QPixmap defaultAvatar(":/images/wechat.png");
    if (!defaultAvatar.isNull()) {
        QPixmap scaledPixmap = defaultAvatar.scaled(40, 40, Qt::KeepAspectRatio, Qt::FastTransformation);
        _avatarLabel->setPixmap(scaledPixmap);
    } else {
        // 如果没有默认图片，创建一个简单的圆形头像
        QPixmap pixmap(40, 40);
        pixmap.fill(Qt::transparent);
        
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(QColor("#cccccc")));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(0, 0, 40, 40);
        
        _avatarLabel->setPixmap(pixmap);
    }
    _avatarLabel->setAlignment(Qt::AlignCenter);
}

void ContactItem::updateDisplayContent()
{
    _nameLabel->setText(_name);
    _personalSigLabel->setText(_message);

    // 处理消息显示，末尾省略
    QFontMetrics fontWidth(_personalSigLabel->font());
    QString elideNote = fontWidth.elidedText(_message, Qt::ElideRight, _personalSigLabel->width());
    
    _personalSigLabel->setText(elideNote);

    // 设置头像
    setAvatar(_avatarPath);
}

void ContactItem::mousePressEvent(QMouseEvent *event)
{
    // 发送选中信号，让MessageListWidget处理
    if (event->button() == Qt::LeftButton) {
        // 发送消息，由MessageListWidget传递给聊天窗口渲染。
        qDebug() << "MessageItem clicked:" << _name;
        emit contactClicked(this);
    }
    // 继续事件传播
    QWidget::mousePressEvent(event);
}

void ContactItem::resizeEvent(QResizeEvent *event)
{
    // 改变尺寸
    QWidget::resizeEvent(event);
    // 重新调整显示内容
    updateDisplayContent();
}

void ContactItem::enterEvent(QEnterEvent *event){
    qDebug() << "ContactItem Mouse entered:" << _name;
    QWidget::enterEvent(event);
    if(_state != WidgetMouseState::SELECTED){
        setState(WidgetMouseState::HOVERED);
    }
}

void ContactItem::leaveEvent(QEvent *event){
    qDebug() << "MessageItem Mouse left:" << _name;
    QWidget::leaveEvent(event);
    if(_state != WidgetMouseState::SELECTED){
        setState(WidgetMouseState::NORMAL);
    }
}

void ContactItem::setState(WidgetMouseState state){
    if (_state == state) {
        return;
    }
    _state = state;

    switch (state) {
        case WidgetMouseState::NORMAL:
            setProperty("state", "normal");
            break;
        case WidgetMouseState::HOVERED:
            setProperty("state", "hovered");
            break;
        case WidgetMouseState::SELECTED:
            setProperty("state", "selected");
            break;
        case WidgetMouseState::DISABLED:
            setProperty("state", "disabled");
            break;
    }
    
    repolish(this);
}

void ContactItem::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}