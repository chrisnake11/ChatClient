#ifndef CONTACTLISTWIDGET_H
#define CONTACTLISTWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>
#include <QMouseEvent>
#include <QEnterEvent>
#include <QPainter>
#include <QPixmap>
#include <QFileInfo>
#include "ContactItem.h"


class ContactListWidget : public QWidget{
    Q_OBJECT
public:
    explicit ContactListWidget(QWidget *parent = nullptr);
    ~ContactListWidget();
    void addContact(const QString &name, const QString &avatarPath,
                    const QString &message, const QString &time);
    void removeContact(const QString &name);
    void clearContacts();
    void setCurrentContact(const QString &name);
    ContactItem* getContactItem(const QString &name);
    void updateContact(const QString &name, const QString &time,
                       const QString &message, int unreadCount);

private:
    void setupUI();
    ContactItem* findContactItem(const QString &name);
    QVBoxLayout * _contentLayout;
    QList<ContactItem*> _contactItems;
    QString _currentSelectedContact;

};
#endif // CONTACTLISTWIDGET_H