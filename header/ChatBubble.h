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
    explicit ChatBubble(const bool fromthis, QWidget *parent = nullptr);
    ~ChatBubble();
    void setMargin(int margin);
    void setWidget(QWidget *widget);

protected:
    void paintEvent(QPaintEvent *event) override;
    bool _fromthis; // 是否来自于自己
    QHBoxLayout *_layout;
    int _margin;
};

#endif // CHATBUBBLE_H
