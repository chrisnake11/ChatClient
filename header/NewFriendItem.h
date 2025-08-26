#ifndef NEWFRIENDITEM_H
#define NEWFRIENDITEM_H
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
#include <QPushButton>
#include "global.h"


class NewFriendItem : public QWidget
{
    Q_OBJECT
public:
    explicit NewFriendItem(bool isRequest, bool isAccepted, QWidget *parent = nullptr);
    ~NewFriendItem();

    // 更新信息
    void setInfo(const int& uid, const QString &name, const QString &avatarPath, const QString &message);
    void setAvatar(const QString &avatarPath);
    QString& getName();
    // 重写paintEvent, 绘制qss样式
    // QT StyleSheet 示例：https://doc.qt.io/qt-6/stylesheet-examples.html
    void paintEvent(QPaintEvent *event) override;


public slots:
    // 根据服务器返回结果，更新UI
    void onAcceptFriendSuccess(bool success);
    void onRejectFriendSuccess(bool success);

signals:
    // 发送信号，接收/拒绝requester的请求
    void addFriendAccepted(const QString& requester);
    void addFriendRejected(const QString& requester);

private:
    void setupUI();
    void setDefaultAvatar();

    // 信息
    int _uid;
    QString _avatarPath;
    QString _name;
    QString _message;

    // ui组件
    QHBoxLayout *_layout;
    QLabel *_avatarLabel; // 头像
    QLabel *_nameLabel; // 名称
    QLabel *_messageLabel; // 留言

    QPushButton* _acceptButton; // 接收按钮
    QPushButton* _rejectButton; // 拒绝按钮
    QLabel* _infoLabel; // 已添加/正在等待

    // 请求还是响应
    bool _isRequest;
    // 是否处理了
    bool _isAccepted;
};

#endif // CONTACTITEM_H