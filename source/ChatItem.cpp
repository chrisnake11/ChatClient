#include "ChatItem.h"

ChatItem::ChatItem(bool fromthis, QWidget *parent)
    : QWidget(parent), _fromthis(fromthis)
{
    _layout = new QGridLayout(this);
    _layout->setVerticalSpacing(3);
    _layout->setHorizontalSpacing(3);
    _layout->setContentsMargins(3, 3, 3, 3);

    _nameLabel = new QLabel(this);
    _nameLabel->setObjectName("chat_user_name");
    QFont font("Microsoft YaHei", 10);
    _nameLabel->setFont(font);
    _nameLabel->setFixedHeight(20);
    
    _avatarLabel = new QLabel(this);
    _avatarLabel->setFixedSize(40, 40);
    _avatarLabel->setScaledContents(true);
    
    _messageLabel = new QWidget(this);
    
    QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    // 来自于自己的消息
    if(fromthis == true){
        // 设置布局，头像在右
        // _    name    avatar
        // _    bubble  _

        _layout->setContentsMargins(0, 0, 8, 0);
        _layout->setAlignment(Qt::AlignRight);
        _nameLabel->setAlignment(Qt::AlignRight);
        _nameLabel->setContentsMargins(0, 0, 10, 0);

        // 添加组件(row, col, rowSpan, colSpan)
        _layout->addWidget(_nameLabel, 0, 1, 1, 1);
        _layout->addWidget(_avatarLabel, 0, 2, 2, 1, Qt::AlignTop);
        _layout->addItem(spacer, 1, 0, 2, 1); // 添加在左边，将组件挤到右侧
        _layout->addWidget(_messageLabel, 1, 1, 1, 1);

        // 设置第1列和第2列的拉伸因子
        _layout->setColumnStretch(0, 2);
        _layout->setColumnStretch(1, 3);
    }
    else{
        // 设置布局，头像在左
        // avatar   name    _
        // _        bubble  _

        _layout->setContentsMargins(0, 8, 0, 0);
        _layout->setAlignment(Qt::AlignLeft);
        _nameLabel->setAlignment(Qt::AlignLeft);
        _nameLabel->setContentsMargins(10, 0, 0, 0);

        // 添加组件(fromrow, fromcol, 跨行数量, 跨列数量)
        _layout->addWidget(_nameLabel, 0, 1, 1, 1);
        _layout->addWidget(_avatarLabel, 0, 0, 2, 1, Qt::AlignTop);
        _layout->addItem(spacer, 1, 2, 1, 1); // 添加在右边，将组件挤到左侧
        _layout->addWidget(_messageLabel, 1, 1, 1, 1);

        // 设置第2列和第3列的拉伸因子
        _layout->setColumnStretch(1, 3);
        _layout->setColumnStretch(2, 2);
    }

    this->setLayout(_layout);
}

ChatItem::~ChatItem()
{
}

void ChatItem::setName(const QString &name){
    _nameLabel->setText(name);
}

void ChatItem::setMessageBubble(QWidget* bubble)
{
    // 替换消息气泡
    _layout->replaceWidget(_messageLabel, bubble);
    delete _messageLabel;
    _messageLabel = bubble;
}

void ChatItem::setAvatar(const QString &avatarPath)
{
    QPixmap avatarPixmap(avatarPath);
    _avatarLabel->setPixmap(avatarPixmap.scaled(40, 40, Qt::KeepAspectRatio));
}

QString ChatItem::getName() const
{
    return _nameLabel->text();
}


void ChatItem::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QWidget::paintEvent(event);
}
