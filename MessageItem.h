#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H
#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>
#include <QMouseEvent>
#include <QEnterEvent>
#include <QPainter>
#include <QPixmap>
#include <QFileInfo>
#include <QResizeEvent>
#include <QPaintEvent>
#include "global.h"


class MessageItem : public QWidget
{
    Q_OBJECT
public:
    explicit MessageItem(QWidget *parent = nullptr);
    ~MessageItem();

    // 更新信息
    void setInfo(const QString &name, const QString &avatarPath, const QString &message, const QString &time);
    void setAvatar(const QString &avatarPath);
    QString getAvatarPath() const { return _avatarPath; }
    QString getName() const { return _name; }
    // 绘制ui的内容
    void updateDisplayContent();
    // 状态
    void setState(WidgetMouseState state);

    // 重写paintEvent, 绘制qss样式
    // QT StyleSheet 示例：https://doc.qt.io/qt-6/stylesheet-examples.html
    void paintEvent(QPaintEvent *event) override;
public slots:
    // 鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override;
    // 尺寸改变事件
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

signals:
    // 消息被点击
    void messageClicked(MessageItem *item);


private:
    void setupUI();
    void setDefaultAvatar();

    // 信息
    QString _avatarPath;
    QString _name;
    QString _message;
    QString _time;

    // ui组件
    QLabel *_avatarLabel;
    QLabel *_nameLabel;
    QLabel *_msgLabel;
    QLabel *_timeLabel;

    WidgetMouseState _state;
};

#endif // CONTACTITEM_H