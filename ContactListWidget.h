#ifndef CONTACTLISTWIDGET_H
#define CONTACTLISTWIDGET_H
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
#include "ContactItem.h"
#include <QResizeEvent>

class ContactListWidget : public QWidget{
    Q_OBJECT
public:
    explicit ContactListWidget(QWidget *parent = nullptr);
    ~ContactListWidget();

    // contact management functions
    void addContact(const QString &name, const QString &avatarPath,
                    const QString &message, const QString &time);
    void clearContacts();
    void updateContact(ContactItem *item, const QString &name, const QString &message, const QString &time, int unreadCount);
    ContactItem* findContactItem(const QString &name);
    
    
    void setScrollArea(QScrollArea *scrollArea);

    void paintEvent(QPaintEvent *event) override;
    
public slots:
    void setCurrentContact(ContactItem *item);
    void loadContactList();
    void searchContact(const QString &text);

signals:
    void contactClicked(const QString& name);

private:
    // 初始化联系人列表
    void initContactList();
    void setupUI();
    QVBoxLayout * _contentLayout;
    QList<ContactItem*> _contactItems;

    ContactItem* _currentSelectedContact;
    QScrollArea* _scrollArea;
};
#endif // CONTACTLISTWIDGET_H