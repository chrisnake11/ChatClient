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
class ContactItem : public QWidget
{
    Q_OBJECT
public:
    explicit ContactItem(QWidget *parent = nullptr);
    ~ContactItem();
    void setInfo(const QString &name, const QString &avatarPath, const QString &message, const QString &time);
    void setAvatar(const QString &avatarPath);
    QString getAvatarPath() const { return _avatarPath; }
    QString getName() const { return _name; }
    // 设置内容
    void updateDisplayContent();
    void setSelected(bool selected);
    void setHovered(bool hovered);

public slots:
    // 鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void contactClicked(const QString &name);

private:
    void setupUI();
    void setDefaultAvatar();
    QString _avatarPath;
    QString _name;
    QString _message;
    QString _time;
    QLabel *_avatarLabel;
    QLabel *_nameLabel;
    QLabel *_msgLabel;
    QLabel *_timeLabel;
    bool _isSelected;
};

#endif // CONTACTITEM_H