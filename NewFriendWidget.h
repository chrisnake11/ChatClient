#pragma once

#include <QWidget>
#include <QScrollBar>
#include <QScrollArea>
#include "NewFriendItem.h"
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>
/*
    NewFriendWidget负责管理好友请求的显示，不交互。
*/
class NewFriendWidget: public QWidget{
    Q_OBJECT

public:
    explicit NewFriendWidget(QWidget *parent = nullptr);
    ~NewFriendWidget();

    void addNewFriendItem(NewFriendItem* item);
    NewFriendItem* findNewFriendItem(const QString& name);
    void setScrollArea(QScrollArea* scrollArea);
    void paintEvent(QPaintEvent *event) override;

public slots:
    void onAcceptNewFriendSuccess(const QString& requester);
    void onRejectNewFriendSuccess(const QString& requester);
signals:
    // 转发NewFriendItem中的请求信号给ChatDialog
    void acceptNewFriend(const QString& requester);
    void rejectNewFriend(const QString& requester);

private:
    void initUI();
    void loadNewFriendList();
    QVBoxLayout* _layout;
    QScrollArea* _scrollArea;
};