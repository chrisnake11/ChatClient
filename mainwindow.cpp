#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), _register_dialog(nullptr), _login_dialog(nullptr), _reset_dialog(nullptr), _chat_dialog(nullptr)
{
    // // 初始化UI界面
    ui->setupUi(this);


    // 初始化登录界面
    // _login_dialog = new LoginDialog(this);
    // setCentralWidget(_login_dialog);

    _chat_dialog = new ChatDialog(this);
    // 设置主窗口的大小
    this->setMinimumSize(QSize(900, 600));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    // 设置聊天界面为主窗口的中心部件
    setCentralWidget(_chat_dialog);


    // // 切换到注册界面
    // connect(_login_dialog, &LoginDialog::switch_to_register, this, &MainWindow::createRegisterDialog);

    // // 切换到重置密码界面
    // connect(_login_dialog, &LoginDialog::switch_to_reset, this, &MainWindow::createResetDialog);

    // // 切换到聊天界面
    // connect(_login_dialog, &LoginDialog::switch_to_chat, this, &MainWindow::createChatDialog);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createResetDialog()
{
    // 创建重置密码界面
    if (_reset_dialog == nullptr) {
        _reset_dialog = new ResetDialog(this);

        // 重置密码界面返回登录界面
        connect(_reset_dialog, &ResetDialog::switch_to_login, this, [this] {
                setCentralWidget(_login_dialog);
            });

        // 重置密码成功，显示提示信息并删除重置密码界面
        connect(_reset_dialog, &ResetDialog::reset_success, this, [this] {
            qDebug() << "重置密码成功";
            _login_dialog->showTip("重置密码成功，请登录", true);
            delete _reset_dialog;
            _reset_dialog = nullptr;
            });

    }
    setCentralWidget(_reset_dialog);
}

void MainWindow::createRegisterDialog()
{
    // 如果为空，新建注册界面
    if (_register_dialog == nullptr) {
        _register_dialog = new RegisterDialog(this);
        // 注册界面返回登录界面
        connect(_register_dialog, &RegisterDialog::switch_to_login, this, [this] {
                setCentralWidget(_login_dialog);
            });

        // 注册成功，显示提示信息并删除注册界面
        connect(_register_dialog, &RegisterDialog::register_success, this, [this] {
            qDebug() << "注册成功";
            _login_dialog->showTip("注册成功，请登录", true);
            // 先切换到登录界面，再删除注册界面
            setCentralWidget(_login_dialog);
            delete _register_dialog;
            _register_dialog = nullptr;
            });
    }

    // 直接切换到注册界面
    setCentralWidget(_register_dialog);
}


void MainWindow::createChatDialog()
{
	qDebug() << "createChatDialog called";
	// 如果为空，新建聊天界面
    if (_chat_dialog == nullptr) {
        _chat_dialog = new ChatDialog(this);
        // 注册聊天界面切换到其他界面的信号事件
	}

    // 设置主窗口的大小
    this->setMinimumSize(QSize(900, 600));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    // 切换到聊天界面
    setCentralWidget(_chat_dialog);
}