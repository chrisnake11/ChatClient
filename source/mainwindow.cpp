#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include "TcpManager.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), _register_dialog(nullptr), _login_dialog(nullptr), _reset_dialog(nullptr), _chat_dialog(nullptr)
{
    // // 初始化UI界面
    ui->setupUi(this);

    // 初始化登录界面
    createLoginDialog();

    // 绑定TCP登录成功信号
    connect(TcpManager::getInstance().get(), &TcpManager::loginSuccess, this, &MainWindow::createChatDialog);
    
    // 初始化聊天界面
    // createChatDialog();
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destructor called";
    delete ui;
}

void MainWindow::createLoginDialog() {
    _login_dialog = new LoginDialog(this);
    // 切换到注册界面
    connect(_login_dialog, &LoginDialog::switch_to_register, this, &MainWindow::createRegisterDialog);

    // 切换到重置密码界面
    connect(_login_dialog, &LoginDialog::switch_to_reset, this, &MainWindow::createResetDialog);

    // 切换到聊天界面
    connect(_login_dialog, &LoginDialog::switch_to_chat, this, &MainWindow::createChatDialog);
    
    setCentralWidget(_login_dialog);
}

void MainWindow::createResetDialog()
{
    _reset_dialog = new ResetDialog(this);

    // 重置密码界面返回登录界面
    connect(_reset_dialog, &ResetDialog::switch_to_login, this, &MainWindow::createLoginDialog);

    // 重置密码成功，显示提示信息并切换到登录界面删除重置密码界面
    connect(_reset_dialog, &ResetDialog::reset_success, this, [this] {
        qDebug() << "重置密码成功";
        // 切换到登录界面
        createLoginDialog();
        _login_dialog->showTip("重置密码成功，请登录", true);
        });

    
    setCentralWidget(_reset_dialog);
}

void MainWindow::createRegisterDialog()
{
    _register_dialog = new RegisterDialog(this);
    // 注册界面返回登录界面
    connect(_register_dialog, &RegisterDialog::switch_to_login, this, &MainWindow::createLoginDialog);

    // 注册成功，显示提示信息并删除注册界面
    connect(_register_dialog, &RegisterDialog::register_success, this, [this] {
        qDebug() << "注册成功";
        createLoginDialog();
        _login_dialog->showTip("注册成功，请登录", true);
        // 先切换到登录界面，再删除注册界面
        });
 

    // 直接切换到注册界面
    setCentralWidget(_register_dialog);
}


void MainWindow::createChatDialog()
{
	qDebug() << "createChatDialog called";
	// 新建聊天界面
    _chat_dialog = new ChatDialog(this);
    // 注册聊天界面切换到其他界面的信号事件
        
    // 设置主窗口的大小
    this->setMinimumSize(_chat_dialog->minimumSize());
    this->setMaximumSize(_chat_dialog->maximumSize());
    // 切换到聊天界面
    setCentralWidget(_chat_dialog);
}