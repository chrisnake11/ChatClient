#ifndef CONTACTITEM_H
#define CONTACTITEM_H
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


class ContactItem : public QWidget
{
    Q_OBJECT
public:
    explicit ContactItem(QWidget *parent = nullptr);
    ~ContactItem();

    // 更新信息
    void setInfo(const int& uid, const QString &name, const QString &avatarPath, const QString &message);
    void setAvatar(const QString &avatarPath);
    QString getAvatarPath() const { return _avatarPath; }
    QString getName() const { return _name; }
    int getUid() const { return _uid; }
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
    // 联系人被点击
    void contactClicked(ContactItem *item);


private:
    void setupUI();
    void setDefaultAvatar();

    // 信息
    int _uid;
    QString _avatarPath;
    QString _name;
    QString _message; // 个性签名

    // ui组件
    QHBoxLayout *_layout;
    QLabel *_avatarLabel; // 头像
    QLabel *_nameLabel; // 名称
    QLabel *_personalSigLabel; // 个性签名标签

    // 在线状态
    bool _isOnline;

    WidgetMouseState _state;
};

#endif // CONTACTITEM_H