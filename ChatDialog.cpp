#include "ChatDialog.h"
#include "ui_ChatDialog.h"
#include <QFile>
#include <QDebug>

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    
    // 加载聊天对话框专用样式
    loadChatDialogStyle();
    
    // 初始化界面
    initUI();
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

void ChatDialog::initUI()
{
    // 设置窗口属性
    setWindowTitle("聊天室");
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    
    // 这里可以添加其他初始化代码
}

