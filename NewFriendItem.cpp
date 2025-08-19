#include "NewFriendItem.h"
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>

NewFriendItem::NewFriendItem(bool isRequest, bool isAccepted, QWidget *parent)
    : QWidget(parent),
      _layout(new QHBoxLayout(this)),
      _avatarLabel(new QLabel(this)),
      _nameLabel(new QLabel(this)),
      _messageLabel(new QLabel(this)),
      _acceptButton(new QPushButton(this)),
      _rejectButton(new QPushButton(this)),
      _infoLabel(new QLabel(this)),
      _isRequest(isRequest),
      _isAccepted(isAccepted)
{
    _acceptButton->hide();
    _rejectButton->hide();
    _infoLabel->hide();
    setupUI();
}

NewFriendItem::~NewFriendItem()
{
    delete _layout;
    delete _avatarLabel;
    delete _nameLabel;
    delete _messageLabel;
}

QString& NewFriendItem::getName(){
    return _name;
}

void NewFriendItem::setInfo(const QString &name, const QString &avatarPath, const QString &message)
{
    _name = name;
    _avatarPath = avatarPath;
    _message = message;

    _nameLabel->setText(_name);
    _messageLabel->setText("留言: " + _message);
    setAvatar(_avatarPath);
}

void NewFriendItem::setupUI(){
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _layout->setSpacing(10);

    // 头像
    _layout->addWidget(_avatarLabel);

    // 中间布局
    QVBoxLayout *middleLayout = new QVBoxLayout();
    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addWidget(_nameLabel);
    nameLayout->setSpacing(5);
    // 添加用户名和时间
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    if(_isRequest){
        QLabel *timeLabel = new QLabel("来自好友的请求:" + time, this);
        nameLayout->addWidget(timeLabel);
    }
    else{
        QLabel *timeLabel = new QLabel("发送给好友的请求:" + time, this);
        nameLayout->addWidget(timeLabel);
    }
    _messageLabel->setStyleSheet("color: #666666;");
    middleLayout->addLayout(nameLayout);
    
    // 添加留言信息
    middleLayout->addWidget(_messageLabel);
    _layout->addLayout(middleLayout);
    _layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // 右边布局
    // 如果是好友请求，并且没处理
    if (!_isRequest && !_isAccepted ) {
        _acceptButton->setText("accept");
        _acceptButton->setStyleSheet("background-color: #eee; border: 1px solid #aaa; border-radius: 2px;");
        _rejectButton->setText("reject");
        _rejectButton->setStyleSheet("background-color: #eee; border: 1px solid #aaa; border-radius: 2px;");
        connect(_acceptButton, &QPushButton::clicked, this, [this]{
            // 向上级发送信号
            emit addFriendAccepted(_name);
        });
        connect(_rejectButton, &QPushButton::clicked, this, [this] {
            // 向上级发送信号
            emit addFriendRejected(_name);
        });
        _acceptButton->show();
        _rejectButton->show();
    }
    // 如果是主动发出的请求，并且没处理
    else if (_isRequest && !_isAccepted) {
        // 设置接收状态文字，显示label
        _infoLabel->setText("wait accept");
        _infoLabel->show();
    }
    // 处理过的请求
    else{
        _infoLabel->setText("accepted");
        _infoLabel->show();
    }
    _layout->addWidget(_acceptButton);
    _layout->addWidget(_rejectButton);
    _layout->addWidget(_infoLabel);
    setLayout(_layout);
    setStyleSheet("background-color: white; border-radius: 5px;");

}

void NewFriendItem::setAvatar(const QString &avatarPath)
{
    if (QFileInfo::exists(avatarPath)) {
        QPixmap pixmap(avatarPath);
        _avatarLabel->setPixmap(pixmap.scaled(40, 40, Qt::KeepAspectRatio));
    } else {
        setDefaultAvatar();
    }
}


void NewFriendItem::setDefaultAvatar()
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

void NewFriendItem::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}

void NewFriendItem::onAcceptFriendSuccess(bool success){
    qDebug() << "accept new friend success";
    _acceptButton->hide();
    _rejectButton->hide();
    _infoLabel->setText("accepted");
    _infoLabel->show();
}
void NewFriendItem::onRejectFriendSuccess(bool success){
    qDebug() << "reject new friend success";
    _acceptButton->hide();
    _rejectButton->hide();
    _infoLabel->setText("rejected");
    _infoLabel->show();
}