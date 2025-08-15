#ifndef CHATLISTWIDGET_H
#define CHATLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QScrollArea>
#include <QList>
#include <QEvent>
#include <QPaintEvent>
#include <QStyleOption>
#include <QStyle>
#include <QPainter>
#include <QResizeEvent>
#include "ChatBubble.h"
#include "ChatItem.h"
#include "global.h"
#include "TextBubble.h"

class ChatListWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChatListWidget(QWidget *parent = nullptr);
    ~ChatListWidget();
    void addChatItemBack(QWidget* chat_item);
    void addChatItemFront(QWidget* chat_item);
    void setScrollArea(QScrollArea* scrollArea);
    void loadChatHistory();
protected:
    void paintEvent(QPaintEvent* event) override;
    void onScrollBarValueChanged(int value);
private:
    QVBoxLayout * _layout;
    QScrollArea* _scrollArea;
};

#endif // CHATLISTWIDGET_H