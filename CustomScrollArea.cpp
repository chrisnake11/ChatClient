#include "CustomScrollArea.h"
#include <QScrollBar>

CustomScrollArea::CustomScrollArea(QWidget *parent)
    : QScrollArea(parent)
    , hideTimer(new QTimer(this))
    , isScrollBarVisible(false)
{
    // 初始隐藏滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    // 设置定时器
    hideTimer->setSingleShot(true);
    hideTimer->setInterval(2000); // 默认2秒后隐藏
    // 定时器超时，隐藏滚动条
    connect(hideTimer, &QTimer::timeout, this, &CustomScrollArea::hideScrollBars);
    
    // 启用鼠标跟踪
    setMouseTracking(true);
}

void CustomScrollArea::enterEvent(QEnterEvent *event)
{
    showScrollBars();
    QScrollArea::enterEvent(event);
}

void CustomScrollArea::leaveEvent(QEvent *event)
{
    // 延迟隐藏滚动条
    hideTimer->start();
    QScrollArea::leaveEvent(event);
}

void CustomScrollArea::showScrollBars()
{
    if (!isScrollBarVisible) {
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        isScrollBarVisible = true;
    }
    hideTimer->stop();
}

void CustomScrollArea::hideScrollBars()
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    isScrollBarVisible = false;
}