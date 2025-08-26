#include "MessageItem.h"
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

MessageItem::MessageItem(QWidget *parent) : QWidget(parent),
                                            _avatarLabel(nullptr),
                                            _nameLabel(nullptr),
                                            _msgLabel(nullptr),
                                            _timeLabel(nullptr),
                                            _state(WidgetMouseState::NORMAL)
{
    setupUI();
    setProperty("state", "normal");
}

MessageItem::~MessageItem()
{
    // QT 会自动删除子控件
}

void MessageItem::setupUI()
{
    // 设置固定大小 - 增加宽度以容纳所有内容
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // 创建主水平布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);  // 减少左右边距
    mainLayout->setSpacing(5);

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
    _nameLabel = new QLabel("联系人", this);
    _nameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _nameLabel->setStyleSheet("font-weight: bold; color: #333333; font-size: 12px;");
    // 创建消息标签
    _msgLabel = new QLabel("message", this);
    _msgLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _msgLabel->setStyleSheet("color: #666666; font-size: 9px;");

    middleLayout->addWidget(_nameLabel);
    middleLayout->addWidget(_msgLabel);
    
    // 创建时间标签 - 增加固定宽度
    _timeLabel = new QLabel("12:00", this);
    _timeLabel->setFixedSize(40, 40); // 固定大小
    _timeLabel->setAlignment(Qt::AlignCenter);
    _timeLabel->setStyleSheet("color: #999999; font-size: 9px;");
    
    // 添加到主布局 - 调整伸缩因子
    mainLayout->addWidget(_avatarLabel, 0);          // 头像不伸缩
    mainLayout->addLayout(middleLayout, 1);          // 中间内容可伸缩
    mainLayout->addWidget(_timeLabel, 0);            // 时间标签不伸缩
    
    // 设置默认头像
    setDefaultAvatar();

    // 设置鼠标追踪
    setMouseTracking(true);
}

void MessageItem::setInfo(const int& uid, const QString &name, const QString &avatarPath, const QString &message, const QString &time)
{
    _uid = uid;
    _name = name;
    _avatarPath = avatarPath;
    _time = time;
    _message = message;
    updateDisplayContent();
}

void MessageItem::setAvatar(const QString &avatarPath)
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

void MessageItem::setDefaultAvatar()
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

void MessageItem::updateDisplayContent()
{
    _nameLabel->setText(_name);
    _msgLabel->setText(_message);

    // 处理消息显示，末尾省略
    QFontMetrics fontWidth(_msgLabel->font());
    QString elideNote = fontWidth.elidedText(_message, Qt::ElideRight, _msgLabel->width());
    
    _msgLabel->setText(elideNote);

    _timeLabel->setText(_time);
    // 设置头像
    setAvatar(_avatarPath);
}

void MessageItem::mousePressEvent(QMouseEvent *event)
{
    // 发送选中信号，让MessageListWidget处理
    if (event->button() == Qt::LeftButton) {
        // 发送消息，由MessageListWidget传递给聊天窗口渲染。
        qDebug() << "MessageItem clicked:" << _name;
        emit messageClicked(this);
    }
    // 继续事件传播
    QWidget::mousePressEvent(event);
}

void MessageItem::resizeEvent(QResizeEvent *event)
{
    // 改变尺寸
    QWidget::resizeEvent(event);
    // 重新调整显示内容
    updateDisplayContent();
}

void MessageItem::enterEvent(QEnterEvent *event){
    qDebug() << "ContactItem Mouse entered:" << _name;
    QWidget::enterEvent(event);
    if(_state != WidgetMouseState::SELECTED){
        setState(WidgetMouseState::HOVERED);
    }
}

void MessageItem::leaveEvent(QEvent *event){
    qDebug() << "MessageItem Mouse left:" << _name;
    QWidget::leaveEvent(event);
    if(_state != WidgetMouseState::SELECTED){
        setState(WidgetMouseState::NORMAL);
    }
}

void MessageItem::setState(WidgetMouseState state){
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

void MessageItem::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}