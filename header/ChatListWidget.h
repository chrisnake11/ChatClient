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
#include "CustomScrollArea.h"
#include "UserManager.h"

class ChatListWidget : public QWidget {
    Q_OBJECT
public:
    explicit ChatListWidget(QWidget *parent = nullptr);
    ~ChatListWidget();
    void addChatItemBack(QWidget* chat_item);
    void addChatItemFront(QWidget* chat_item);
    void setScrollArea(CustomScrollArea* scrollArea);
    void loadChatMessageList(std::shared_ptr<std::vector<ChatMessageInfo>>);
    void clear();
public slots:
    void addSingleMessage(std::shared_ptr<ChatMessageInfo> message);

private:
    void paintEvent(QPaintEvent* event) override;
    void onScrollBarValueChanged(int value);
    QVBoxLayout * _layout;
    CustomScrollArea* _scrollArea;
};

#endif // CHATLISTWIDGET_H