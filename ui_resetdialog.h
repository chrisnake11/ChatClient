/********************************************************************************
** Form generated from reading UI file 'resetdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETDIALOG_H
#define UI_RESETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedlabel.h"

QT_BEGIN_NAMESPACE

class Ui_ResetDialogClass
{
public:
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout_7;
    QLabel *email_label;
    QLineEdit *email_text;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *passwd_label;
    QLineEdit *passwd_text;
    clickedlabel *passwd_visible;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_9;
    QLabel *confirm_label;
    QLineEdit *confirm_text;
    clickedlabel *confirm_visible;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout;
    QLabel *code_label;
    QLineEdit *code_text;
    QPushButton *get_code_btn;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *return_btn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *reset_btn;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *ResetDialogClass)
    {
        if (ResetDialogClass->objectName().isEmpty())
            ResetDialogClass->setObjectName("ResetDialogClass");
        ResetDialogClass->resize(301, 384);
        verticalLayoutWidget_3 = new QWidget(ResetDialogClass);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(10, 10, 281, 361));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(10, 10, 10, 10);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        err_tip = new QLabel(verticalLayoutWidget_3);
        err_tip->setObjectName("err_tip");
        err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(err_tip);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(10, -1, 10, -1);
        email_label = new QLabel(verticalLayoutWidget_3);
        email_label->setObjectName("email_label");

        horizontalLayout_7->addWidget(email_label);

        email_text = new QLineEdit(verticalLayoutWidget_3);
        email_text->setObjectName("email_text");

        horizontalLayout_7->addWidget(email_text);


        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(10, -1, 10, -1);
        passwd_label = new QLabel(verticalLayoutWidget_3);
        passwd_label->setObjectName("passwd_label");

        horizontalLayout_8->addWidget(passwd_label);

        passwd_text = new QLineEdit(verticalLayoutWidget_3);
        passwd_text->setObjectName("passwd_text");
        passwd_text->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_8->addWidget(passwd_text);

        passwd_visible = new clickedlabel(verticalLayoutWidget_3);
        passwd_visible->setObjectName("passwd_visible");
        passwd_visible->setMinimumSize(QSize(20, 20));
        passwd_visible->setMaximumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(passwd_visible);


        verticalLayout_3->addLayout(horizontalLayout_8);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(10, -1, 10, -1);
        confirm_label = new QLabel(verticalLayoutWidget_3);
        confirm_label->setObjectName("confirm_label");

        horizontalLayout_9->addWidget(confirm_label);

        confirm_text = new QLineEdit(verticalLayoutWidget_3);
        confirm_text->setObjectName("confirm_text");
        confirm_text->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_9->addWidget(confirm_text);

        confirm_visible = new clickedlabel(verticalLayoutWidget_3);
        confirm_visible->setObjectName("confirm_visible");
        confirm_visible->setMinimumSize(QSize(20, 20));
        confirm_visible->setMaximumSize(QSize(20, 20));

        horizontalLayout_9->addWidget(confirm_visible);


        verticalLayout_3->addLayout(horizontalLayout_9);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, -1, 10, -1);
        code_label = new QLabel(verticalLayoutWidget_3);
        code_label->setObjectName("code_label");

        horizontalLayout->addWidget(code_label);

        code_text = new QLineEdit(verticalLayoutWidget_3);
        code_text->setObjectName("code_text");
        code_text->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(code_text);

        get_code_btn = new QPushButton(verticalLayoutWidget_3);
        get_code_btn->setObjectName("get_code_btn");

        horizontalLayout->addWidget(get_code_btn);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(10, -1, 10, -1);
        return_btn = new QPushButton(verticalLayoutWidget_3);
        return_btn->setObjectName("return_btn");

        horizontalLayout_10->addWidget(return_btn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);

        reset_btn = new QPushButton(verticalLayoutWidget_3);
        reset_btn->setObjectName("reset_btn");

        horizontalLayout_10->addWidget(reset_btn);


        verticalLayout_3->addLayout(horizontalLayout_10);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);


        retranslateUi(ResetDialogClass);

        QMetaObject::connectSlotsByName(ResetDialogClass);
    } // setupUi

    void retranslateUi(QDialog *ResetDialogClass)
    {
        ResetDialogClass->setWindowTitle(QCoreApplication::translate("ResetDialogClass", "ResetDialog", nullptr));
        err_tip->setText(QString());
        email_label->setText(QCoreApplication::translate("ResetDialogClass", "email", nullptr));
        passwd_label->setText(QCoreApplication::translate("ResetDialogClass", "passwd", nullptr));
        passwd_visible->setText(QString());
        confirm_label->setText(QCoreApplication::translate("ResetDialogClass", "confirm", nullptr));
        confirm_visible->setText(QString());
        code_label->setText(QCoreApplication::translate("ResetDialogClass", "code", nullptr));
        get_code_btn->setText(QCoreApplication::translate("ResetDialogClass", "\350\216\267\345\217\226\351\252\214\350\257\201\347\240\201", nullptr));
        return_btn->setText(QCoreApplication::translate("ResetDialogClass", "return", nullptr));
        reset_btn->setText(QCoreApplication::translate("ResetDialogClass", "reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResetDialogClass: public Ui_ResetDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETDIALOG_H
