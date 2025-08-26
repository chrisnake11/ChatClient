#include "ChatBubble.h"
#include <QPainter>

const int triangleSize = 10;

ChatBubble::ChatBubble(const bool fromthis, QWidget *parent)
    : QWidget(parent), _fromthis(fromthis), _margin(10)
{
    _layout = new QHBoxLayout(this);
    if(_fromthis){
        // _layout->setContentsMargins(_margin, _margin, _margin + triangleSize, _margin);
        _layout->setContentsMargins(_margin, _margin, _margin, _margin);
    }
    else{
        // _layout->setContentsMargins(_margin + triangleSize, _margin, _margin, _margin);
        _layout->setContentsMargins(_margin, _margin, _margin, _margin);
    }
    
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
    if(_fromthis){
        // 设置画笔颜色
        painter.setBrush(QColor("#0099ff"));
        // margin内部画圆角矩形
        painter.drawRoundedRect(_margin, _margin, width() - _margin * 2, height() - _margin * 2, _margin, _margin);
        // // 画三角形
        // QPointF points[3] = {
        //     QPointF(width() - _margin, _margin * 2),
        //     QPointF(width() - _margin, _margin * 2 + triangleSize),
        //     QPointF(width() - _margin + triangleSize * cos(M_PI / 12), _margin * 2 + (triangleSize / 2))
        // };
        // painter.drawPolygon(points, 3);
    }
    // 画一个气泡，背景为#0099ff，左边有个三角形
    else{
        painter.setBrush(QColor("#0099ff"));
        painter.drawRoundedRect(_margin, _margin, width() - _margin * 2, height() - _margin * 2, 10, 10);
    }

    QWidget::paintEvent(event);
}