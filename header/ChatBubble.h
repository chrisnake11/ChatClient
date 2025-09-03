#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPaintEvent>

/*
    聊天气泡基类，包含消息内容
*/
class ChatBubble : public QWidget {
    Q_OBJECT
public:
    explicit ChatBubble(QWidget *parent = nullptr);
    ~ChatBubble();
    void setMargin(int margin);
    void setWidget(QWidget *widget);

protected:
    void paintEvent(QPaintEvent *event) override;
    QHBoxLayout *_layout;
    int _margin;
};

#endif // CHATBUBBLE_H
