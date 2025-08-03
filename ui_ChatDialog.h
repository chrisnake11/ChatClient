/********************************************************************************
** Form generated from reading UI file 'ChatDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatDialogClass
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *user_frame;
    QLabel *label;
    QFrame *contact_frame;
    QScrollArea *contact_scroll;
    QWidget *scrollAreaWidgetContents;
    QFrame *chat_frame;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *chat_scroll;
    QWidget *scrollAreaWidgetContents_2;
    QTextEdit *textEdit;

    void setupUi(QDialog *ChatDialogClass)
    {
        if (ChatDialogClass->objectName().isEmpty())
            ChatDialogClass->setObjectName("ChatDialogClass");
        ChatDialogClass->resize(686, 420);
        horizontalLayoutWidget = new QWidget(ChatDialogClass);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 671, 401));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        user_frame = new QFrame(horizontalLayoutWidget);
        user_frame->setObjectName("user_frame");
        user_frame->setMinimumSize(QSize(40, 0));
        user_frame->setMaximumSize(QSize(40, 16777215));
        user_frame->setFrameShape(QFrame::Shape::StyledPanel);
        user_frame->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(user_frame);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 21, 16));

        horizontalLayout->addWidget(user_frame);

        contact_frame = new QFrame(horizontalLayoutWidget);
        contact_frame->setObjectName("contact_frame");
        contact_frame->setMinimumSize(QSize(200, 0));
        contact_frame->setMaximumSize(QSize(200, 16777215));
        contact_frame->setFrameShape(QFrame::Shape::StyledPanel);
        contact_frame->setFrameShadow(QFrame::Shadow::Raised);
        contact_scroll = new QScrollArea(contact_frame);
        contact_scroll->setObjectName("contact_scroll");
        contact_scroll->setGeometry(QRect(10, 10, 181, 381));
        contact_scroll->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 179, 379));
        contact_scroll->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(contact_frame);

        chat_frame = new QFrame(horizontalLayoutWidget);
        chat_frame->setObjectName("chat_frame");
        chat_frame->setFrameShape(QFrame::Shape::StyledPanel);
        chat_frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayoutWidget = new QWidget(chat_frame);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 401, 381));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        chat_scroll = new QScrollArea(verticalLayoutWidget);
        chat_scroll->setObjectName("chat_scroll");
        chat_scroll->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 397, 271));
        chat_scroll->setWidget(scrollAreaWidgetContents_2);

        verticalLayout->addWidget(chat_scroll);

        textEdit = new QTextEdit(verticalLayoutWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setMinimumSize(QSize(0, 100));
        textEdit->setMaximumSize(QSize(16777215, 100));

        verticalLayout->addWidget(textEdit);


        horizontalLayout->addWidget(chat_frame);


        retranslateUi(ChatDialogClass);

        QMetaObject::connectSlotsByName(ChatDialogClass);
    } // setupUi

    void retranslateUi(QDialog *ChatDialogClass)
    {
        ChatDialogClass->setWindowTitle(QCoreApplication::translate("ChatDialogClass", "ChatDialog", nullptr));
        label->setText(QCoreApplication::translate("ChatDialogClass", "Avatar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatDialogClass: public Ui_ChatDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
