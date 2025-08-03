/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

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

class Ui_LoginDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *avatar;
    QSpacerItem *verticalSpacer;
    QLabel *login_tip;
    QHBoxLayout *horizontalLayout_name;
    QLabel *name_label;
    QLineEdit *name_text;
    QHBoxLayout *horizontalLayout_passwd;
    QLabel *passwd_label;
    QLineEdit *passwd_text;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    clickedlabel *forget_label;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_btn;
    QPushButton *login_btn;
    QSpacerItem *horizontalSpacer;
    QPushButton *register_btn;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(300, 500);
        LoginDialog->setMinimumSize(QSize(300, 500));
        LoginDialog->setMaximumSize(QSize(300, 500));
        verticalLayoutWidget = new QWidget(LoginDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 283, 471));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 10, 0, 10);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        avatar = new QLabel(verticalLayoutWidget);
        avatar->setObjectName("avatar");
        avatar->setEnabled(true);
        avatar->setMaximumSize(QSize(150, 150));
        avatar->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        avatar->setPixmap(QPixmap(QString::fromUtf8(":/resources/avatar.png")));
        avatar->setScaledContents(true);
        avatar->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(avatar, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        login_tip = new QLabel(verticalLayoutWidget);
        login_tip->setObjectName("login_tip");
        login_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(login_tip);

        horizontalLayout_name = new QHBoxLayout();
        horizontalLayout_name->setObjectName("horizontalLayout_name");
        horizontalLayout_name->setContentsMargins(10, -1, 10, -1);
        name_label = new QLabel(verticalLayoutWidget);
        name_label->setObjectName("name_label");
        name_label->setMaximumSize(QSize(60, 30));

        horizontalLayout_name->addWidget(name_label);

        name_text = new QLineEdit(verticalLayoutWidget);
        name_text->setObjectName("name_text");
        name_text->setMaximumSize(QSize(200, 20));

        horizontalLayout_name->addWidget(name_text);


        verticalLayout->addLayout(horizontalLayout_name);

        horizontalLayout_passwd = new QHBoxLayout();
        horizontalLayout_passwd->setObjectName("horizontalLayout_passwd");
        horizontalLayout_passwd->setContentsMargins(10, -1, 10, -1);
        passwd_label = new QLabel(verticalLayoutWidget);
        passwd_label->setObjectName("passwd_label");
        passwd_label->setMaximumSize(QSize(60, 30));

        horizontalLayout_passwd->addWidget(passwd_label);

        passwd_text = new QLineEdit(verticalLayoutWidget);
        passwd_text->setObjectName("passwd_text");
        passwd_text->setMaximumSize(QSize(200, 20));
        passwd_text->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_passwd->addWidget(passwd_text);


        verticalLayout->addLayout(horizontalLayout_passwd);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, -1, 10, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        forget_label = new clickedlabel(verticalLayoutWidget);
        forget_label->setObjectName("forget_label");
        QFont font;
        font.setUnderline(true);
        forget_label->setFont(font);

        horizontalLayout->addWidget(forget_label);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_btn = new QHBoxLayout();
        horizontalLayout_btn->setObjectName("horizontalLayout_btn");
        horizontalLayout_btn->setContentsMargins(10, -1, 10, 0);
        login_btn = new QPushButton(verticalLayoutWidget);
        login_btn->setObjectName("login_btn");
        login_btn->setMinimumSize(QSize(60, 20));
        login_btn->setMaximumSize(QSize(60, 20));

        horizontalLayout_btn->addWidget(login_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_btn->addItem(horizontalSpacer);

        register_btn = new QPushButton(verticalLayoutWidget);
        register_btn->setObjectName("register_btn");
        register_btn->setMinimumSize(QSize(60, 25));
        register_btn->setMaximumSize(QSize(60, 25));

        horizontalLayout_btn->addWidget(register_btn);


        verticalLayout->addLayout(horizontalLayout_btn);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        avatar->setText(QString());
        login_tip->setText(QCoreApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215\345\222\214\345\257\206\347\240\201", nullptr));
        name_label->setText(QCoreApplication::translate("LoginDialog", "name ", nullptr));
        passwd_label->setText(QCoreApplication::translate("LoginDialog", "passwd", nullptr));
        forget_label->setText(QCoreApplication::translate("LoginDialog", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
        login_btn->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        register_btn->setText(QCoreApplication::translate("LoginDialog", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
