#ifndef CONTACT_LIST_WIDGET_H
#define CONTACT_LIST_WIDGET_H
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
#include <QResizeEvent>
#include "ContactItem.h"

class ContactListWidget : public QWidget{
    Q_OBJECT
public:
    explicit ContactListWidget(QWidget *parent = nullptr);
    ~ContactListWidget();

    // contact management functions
    void addContact(ContactItem* item);
    void clearContacts();
    void updateContact(ContactItem *item, const int& uid, const QString &name, const QString &message);
    ContactItem* findContactItem(const QString &name);
    
    void setScrollArea(QScrollArea *scrollArea);

    void paintEvent(QPaintEvent *event) override;
    
public slots:
    void setCurrentContact(ContactItem *item);
    void loadContactList();
    void searchContact(const QString &text);

signals:
    void contactClicked(const int& uid);

private:
    // 初始化联系人列表
    void initContactList();
    void setupUI();
    QVBoxLayout * _contentLayout;
    QList<ContactItem*> _contactItems;

    ContactItem* _currentSelectedContact;
    QScrollArea* _scrollArea;
};
#endif // CONTACT_LIST_WIDGET_H