#include "ChatDialog.h"
#include "ui_ChatDialog.h"
#include <QFile>
#include <QDebug>

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    
    // 加载聊天对话框专用样式
    loadChatDialogStyle();

}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::loadChatDialogStyle()
{
    QFile styleFile(":/styles/chat_dialog.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        this->setStyleSheet(style);
        styleFile.close();
        qDebug() << "Chat dialog style loaded successfully";
    } else {
        qDebug() << "Failed to load chat_dialog.qss from resources";
    }
}
