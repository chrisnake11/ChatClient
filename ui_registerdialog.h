/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

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

class Ui_RegisterDialog
{
public:
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout_6;
    QLabel *name_label_reg;
    QLineEdit *name_text_reg;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *email_label_reg;
    QLineEdit *email_text_reg;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *passwd_label_reg;
    QLineEdit *passwd_text_reg;
    clickedlabel *passwd_visible;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_9;
    QLabel *confirm_label_reg;
    QLineEdit *confirm_text_reg;
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
    QPushButton *register_submit_btn;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(300, 500);
        RegisterDialog->setMinimumSize(QSize(300, 500));
        RegisterDialog->setMaximumSize(QSize(300, 500));
        verticalLayoutWidget_3 = new QWidget(RegisterDialog);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(10, 10, 281, 481));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(10, 10, 10, 10);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        err_tip = new QLabel(verticalLayoutWidget_3);
        err_tip->setObjectName("err_tip");
        err_tip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(err_tip);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(10, -1, 10, -1);
        name_label_reg = new QLabel(verticalLayoutWidget_3);
        name_label_reg->setObjectName("name_label_reg");

        horizontalLayout_6->addWidget(name_label_reg);

        name_text_reg = new QLineEdit(verticalLayoutWidget_3);
        name_text_reg->setObjectName("name_text_reg");

        horizontalLayout_6->addWidget(name_text_reg);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(10, -1, 10, -1);
        email_label_reg = new QLabel(verticalLayoutWidget_3);
        email_label_reg->setObjectName("email_label_reg");

        horizontalLayout_7->addWidget(email_label_reg);

        email_text_reg = new QLineEdit(verticalLayoutWidget_3);
        email_text_reg->setObjectName("email_text_reg");

        horizontalLayout_7->addWidget(email_text_reg);


        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(10, -1, 10, -1);
        passwd_label_reg = new QLabel(verticalLayoutWidget_3);
        passwd_label_reg->setObjectName("passwd_label_reg");

        horizontalLayout_8->addWidget(passwd_label_reg);

        passwd_text_reg = new QLineEdit(verticalLayoutWidget_3);
        passwd_text_reg->setObjectName("passwd_text_reg");
        passwd_text_reg->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_8->addWidget(passwd_text_reg);

        passwd_visible = new clickedlabel(verticalLayoutWidget_3);
        passwd_visible->setObjectName("passwd_visible");
        passwd_visible->setMinimumSize(QSize(20, 20));
        passwd_visible->setMaximumSize(QSize(20, 20));

        horizontalLayout_8->addWidget(passwd_visible);


        verticalLayout_3->addLayout(horizontalLayout_8);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(10, -1, 10, -1);
        confirm_label_reg = new QLabel(verticalLayoutWidget_3);
        confirm_label_reg->setObjectName("confirm_label_reg");

        horizontalLayout_9->addWidget(confirm_label_reg);

        confirm_text_reg = new QLineEdit(verticalLayoutWidget_3);
        confirm_text_reg->setObjectName("confirm_text_reg");
        confirm_text_reg->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_9->addWidget(confirm_text_reg);

        confirm_visible = new clickedlabel(verticalLayoutWidget_3);
        confirm_visible->setObjectName("confirm_visible");
        confirm_visible->setMinimumSize(QSize(20, 20));
        confirm_visible->setMaximumSize(QSize(20, 20));

        horizontalLayout_9->addWidget(confirm_visible);


        verticalLayout_3->addLayout(horizontalLayout_9);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);

        horizontalLayout = new QHBoxLayout();
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
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(10, -1, 10, -1);
        return_btn = new QPushButton(verticalLayoutWidget_3);
        return_btn->setObjectName("return_btn");

        horizontalLayout_10->addWidget(return_btn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);

        register_submit_btn = new QPushButton(verticalLayoutWidget_3);
        register_submit_btn->setObjectName("register_submit_btn");

        horizontalLayout_10->addWidget(register_submit_btn);


        verticalLayout_3->addLayout(horizontalLayout_10);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "Register", nullptr));
        err_tip->setText(QString());
        name_label_reg->setText(QCoreApplication::translate("RegisterDialog", "name", nullptr));
        email_label_reg->setText(QCoreApplication::translate("RegisterDialog", "email", nullptr));
        passwd_label_reg->setText(QCoreApplication::translate("RegisterDialog", "passwd", nullptr));
        passwd_visible->setText(QString());
        confirm_label_reg->setText(QCoreApplication::translate("RegisterDialog", "confirm", nullptr));
        confirm_visible->setText(QString());
        code_label->setText(QCoreApplication::translate("RegisterDialog", "code", nullptr));
        get_code_btn->setText(QCoreApplication::translate("RegisterDialog", "\350\216\267\345\217\226\351\252\214\350\257\201\347\240\201", nullptr));
        return_btn->setText(QCoreApplication::translate("RegisterDialog", "return", nullptr));
        register_submit_btn->setText(QCoreApplication::translate("RegisterDialog", "register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
