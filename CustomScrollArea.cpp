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
    
    _overlayScrollBar = new QScrollBar(Qt::Vertical, this);
    _overlayScrollBar->setStyleSheet(R"(
        QScrollBar:vertical {
            background: transparent;
            width: 8px;
            border-radius: 4px;
            margin: 0px;
        }
        QScrollBar::handle:vertical {
            background: rgba(0, 0, 0, 0.3);
            border-radius: 4px;
            min-height: 20px;
        }
        QScrollBar::handle:vertical:hover {
            background: rgba(0, 0, 0, 0.5);
        }
        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            border: none;
            background: none;
            height: 0px;
            subcontrol-position: bottom;
            subcontrol-origin: margin;
        }
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: none;
        }
    )");
    
    // 初始隐藏悬浮滚动条
    _overlayScrollBar->hide();

    // 连接信号进行同步(滚动条位置，范围)
    // 直接操作自定义滚动条，同步原生滚动条
    connect(_overlayScrollBar, &QScrollBar::valueChanged,
            this, &CustomScrollArea::onOverlayScrollBarValueChanged);
    // QScrollArea原生滚动条滚动，同步自定义滚动条
    connect(verticalScrollBar(), &QScrollBar::valueChanged,
            this, &CustomScrollArea::onVerticalScrollBarValueChanged);
    // 原生滚动条范围改变，同步自定义滚动条范围。
    connect(verticalScrollBar(), &QScrollBar::rangeChanged,
            this, &CustomScrollArea::updateOverlayScrollBarRange);

    // 确保内容可以自适应大小
    setWidgetResizable(true);

    // 设置定时器
    hideTimer->setSingleShot(true);
    hideTimer->setInterval(500); // 默认500毫秒后隐藏
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
        _overlayScrollBar->show();
        _overlayScrollBar->setGeometry(width() - 8, 0, 8, height());
        // 同步滚动条范围和值
        updateOverlayScrollBarRange(verticalScrollBar()->minimum(), verticalScrollBar()->maximum());
        _overlayScrollBar->setValue(verticalScrollBar()->value());
        isScrollBarVisible = true;
    }
    hideTimer->stop();
}

void CustomScrollArea::hideScrollBars()
{
    if (_overlayScrollBar) {
        _overlayScrollBar->hide();
    }
    isScrollBarVisible = false;
}

void CustomScrollArea::onOverlayScrollBarValueChanged(int value)
{
    // 防止无限递归
    verticalScrollBar()->blockSignals(true);
    verticalScrollBar()->setValue(value);
    verticalScrollBar()->blockSignals(false);
}

void CustomScrollArea::onVerticalScrollBarValueChanged(int value)
{
    // 防止无限递归
    _overlayScrollBar->blockSignals(true);
    _overlayScrollBar->setValue(value);
    _overlayScrollBar->blockSignals(false);
}

void CustomScrollArea::updateOverlayScrollBarRange(int min, int max)
{
    _overlayScrollBar->setRange(min, max);
    _overlayScrollBar->setPageStep(verticalScrollBar()->pageStep());
    _overlayScrollBar->setSingleStep(verticalScrollBar()->singleStep());
}