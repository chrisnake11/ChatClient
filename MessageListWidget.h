#ifndef MESSAGE_LIST_WIDGET_H
#define MESSAGE_LIST_WIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QFileInfo>
#include <QScrollArea>
#include <QPaintEvent>
#include "MessageItem.h"
#include <QResizeEvent>

class MessageListWidget : public QWidget{
    Q_OBJECT
public:
    explicit MessageListWidget(QWidget *parent = nullptr);
    ~MessageListWidget();

    // message management functions
    void addMessage(MessageItem *item);
    void clearMessages();
    void updateMessage(MessageItem *item, const QString &name, const QString &message, const QString &time, int unreadCount);
    MessageItem* findMessageItem(const QString &name);


    void setScrollArea(QScrollArea *scrollArea);

    void paintEvent(QPaintEvent *event) override;
    
public slots:
    void setCurrentMessage(MessageItem *item);
    void loadMessageList();
    void searchMessage(const QString &text);

signals:
    void messageClicked(const QString& name);

private:
    // 初始化消息列表
    void initMessageList();
    void setupUI();
    QVBoxLayout * _contentLayout;
    QList<MessageItem*> _messageItems;

    MessageItem* _currentSelectedMessage;
    QScrollArea* _scrollArea;
};
#endif // MESSAGE_LIST_WIDGET_H