#ifndef CHATITEM_H
#define CHATITEM_H

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
#include <QStyleOption>
#include <QStyle>

/*
    聊天列表的聊天项，包含头像、名称和消息气泡
*/
class ChatItem : public QWidget {
    Q_OBJECT
public:
    explicit ChatItem(bool from_this, QWidget *parent = nullptr);
    ~ChatItem();
    void setUid(const int& uid);
    void setName(const QString &name);
    void setAvatar(const QString &avatarPath);
    void setMessageBubble(QWidget* bubble);
    QString getName() const;
    int getUid() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QGridLayout *_layout;
    QWidget *_messageLabel;
    QLabel *_avatarLabel;
    QLabel *_nameLabel;
    int _uid;
};

#endif // CHATITEM_H
