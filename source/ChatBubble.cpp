#include "ChatBubble.h"
#include <QPainter>

const int triangleSize = 10;

ChatBubble::ChatBubble(QWidget *parent)
    : QWidget(parent), _margin(10)
{
    _layout = new QHBoxLayout(this);
    
    _layout->setContentsMargins(_margin, _margin, _margin, _margin);

    
    this->setLayout(_layout);
}

ChatBubble::~ChatBubble()
{
}

void ChatBubble::setMargin(int margin)
{
    _margin = margin;
    update();
}

void ChatBubble::setWidget(QWidget *widget)
{
    if(_layout->count() == 0){
        _layout->addWidget(widget);
    }
}

void ChatBubble::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    // 画一个气泡，背景为#0099ff，右边有个三角形
    painter.setBrush(QColor("#0099ff"));
    painter.drawRoundedRect(_margin, _margin, width() - _margin * 2, height() - _margin * 2, 10, 10);

    QWidget::paintEvent(event);
}