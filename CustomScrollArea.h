#ifndef CUSTOMSCROLLAREA_H
#define CUSTOMSCROLLAREA_H

#include <QScrollArea>
#include <QMouseEvent>
#include <QTimer>


/*
    自动隐藏滚动条的ScrollArea类
    当鼠标进入时显示滚动条，离开时隐藏滚动条。
*/
class CustomScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit CustomScrollArea(QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

protected slots:
    // 延迟隐藏滚动条
    void hideScrollBars();

protected:
    QTimer *hideTimer;
    bool isScrollBarVisible;
    void showScrollBars();
};

#endif // CUSTOMSCROLLAREA_H