#ifndef CUSTOMSCROLLAREA_H
#define CUSTOMSCROLLAREA_H

#include <QScrollArea>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QStyleOption>
#include <QResizeEvent>
/*
    自动隐藏滚动条的ScrollArea类
    当鼠标进入时显示滚动条，离开时隐藏滚动条。
*/
class CustomScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit CustomScrollArea(QWidget *parent = nullptr);
    QScrollBar* getCustomScrollBar() const;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

protected slots:
    // 延迟隐藏滚动条
    void hideScrollBars();
    // 悬浮滚动条同步方法
    void onOverlayScrollBarValueChanged(int value);
    void onVerticalScrollBarValueChanged(int value);
    void updateOverlayScrollBarRange(int min, int max);

protected:
    QTimer *hideTimer;
    bool isScrollBarVisible;
    void showScrollBars();
    QScrollBar* _overlayScrollBar;
};

#endif // CUSTOMSCROLLAREA_H