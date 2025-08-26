#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "httpmanager.h"
#include "TcpManager.h"
LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog), _uid(0), _token("")
{
    ui->setupUi(this);

    // 设置对话框为无边框和自定义窗口，使其能够嵌入在主窗口中
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    _tip_errs.clear();

    ui->login_tip->setProperty("state", "normal");

    //connect(ui->login_btn, &QPushButton::clicked, this, &LoginDialog::on_login_btn_clicked);
    connect(ui->register_btn, &QPushButton::clicked, this, &LoginDialog::switch_to_register);

    ui->forget_label->setCursor(Qt::PointingHandCursor);


    // 设置按钮初始状态
    ui->forget_label->setState(WidgetMouseState::NORMAL);
    connect(ui->forget_label, &ClickedLabel::clicked, this, &LoginDialog::on_forget_label_clicked);

    // 初始化http handler
    initHttpHandlers();
    connect(HttpManager::getInstance().get(), &HttpManager::sig_login_mod_finish, this, &LoginDialog::slot_login_mod_finish);

    // tcp connection signal and slot
    connect(this, &LoginDialog::sig_connect_tcp, TcpManager::getInstance().get(),
        &TcpManager::slot_tcp_connect);

    // tcp connect success
    connect(TcpManager::getInstance().get(), &TcpManager::sig_connect_success, this, 
        &LoginDialog::slot_tcp_connect_finish);
    // tcp connect failed
    connect(TcpManager::getInstance().get(), &TcpManager::sig_login_failed, this, 
        &LoginDialog::slot_login_failed);

    // 用户名回车后，焦点移动到密码输入框
    connect(ui->name_text, &QLineEdit::returnPressed, this, [this]() {
        ui->passwd_text->setFocus();
    });
    // 密码输入框回车触发登录
    connect(ui->passwd_text, &QLineEdit::returnPressed, this, &LoginDialog::on_login_btn_clicked);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::showTip(QString str, bool success)
{
    if(success){
        ui->login_tip->setProperty("state", "normal");
    }
    else{
        ui->login_tip->setProperty("state", "error");
    }
    repolish(ui->login_tip);
    ui->login_tip->setText(str);

}

void LoginDialog::on_forget_label_clicked()
{
    qDebug() << "forget clicked";
    emit switch_to_reset();
}


bool LoginDialog::checkNameValid()
{
    if (ui->name_text->text() == "") {
        addTipErr(TipErr::TIP_USER_ERR, tr("name can't be empty"));
        return false;
    }
    delTipErr(TipErr::TIP_USER_ERR);
    return true;;
}
bool LoginDialog::checkPasswdValid()
{
    auto pass = ui->passwd_text->text();
    if (pass.length() < 6 || pass.length() > 15) {
        //提示长度不准确
        addTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }
    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if (!match) {
        //提示字符非法
        addTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }
    delTipErr(TipErr::TIP_PWD_ERR);
    return true;
}

void LoginDialog::addTipErr(TipErr err, QString tips)
{
    _tip_errs[err] = tips;
    showTip(tips, false);
}

void LoginDialog::delTipErr(TipErr err)
{
    _tip_errs.remove(err);
    if (_tip_errs.size() == 0) {
        ui->login_tip->clear();
        return;
    }

    showTip(_tip_errs.first(), false);
}


void LoginDialog::on_login_btn_clicked()
{
    qDebug() << "login clicked";
    if (checkNameValid() == false) {
        return;
    }

    if (checkPasswdValid() == false) {
        return;
    }

    // 按钮点击后的逻辑，例如弹出消息框
    QString name = ui->name_text->text();
    QString passwd = ui->passwd_text->text();

    QJsonObject obj;
    obj["name"] = name;
    obj["passwd"] = passwd;

    // 发送Http请求
    HttpManager::getInstance()->postHttpRequest(QUrl(gate_url_prefix + "/user_login"), 
        obj, RequestID::ID_LOGIN_USER, Modules::LOGIN_MODEL);
}


void LoginDialog::initHttpHandlers() {
	// 请求建立TCP连接，读取服务器返回的用户信息
    _handlers.insert(RequestID::ID_LOGIN_USER, [this](QJsonObject jsonObj) {
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            showTip(tr("参数错误"), false);
            return;
        }
        auto user = jsonObj["name"].toString();

        ServerInfo server_info;
        server_info.uid = jsonObj["uid"].toInt();
        server_info.host = jsonObj["host"].toString();
        server_info.port = jsonObj["port"].toString();
        server_info.token = jsonObj["token"].toString();

        _uid = server_info.uid;
        _token = server_info.token;

        qDebug() << "http response: user is " << user << ", uid is: " << _uid << ", chat_server  host is: " << server_info.host
            << ", chat_server port is: " << server_info.port << ", token is: " << server_info.token;

        emit sig_connect_tcp(server_info);
        showTip(tr("聊天服务器地址请求成功"), true);
        });
}

void LoginDialog::slot_login_mod_finish(RequestID id, QString res, ErrorCodes err)
{
    if (err != ErrorCodes::SUCCESS) {
        showTip(tr("网络请求错误"), false);
        return;
    }
    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());

    //json解析错误
    if (jsonDoc.isNull()) {
        showTip(tr("json解析为空"), false);
        return;
    }

    //json解析错误
    if (!jsonDoc.isObject()) {
        showTip(tr("json解析不是json对象"), false);
        return;
    }

    //调用对应的逻辑,根据id回调。
    _handlers[id](jsonDoc.object());
    return;
}


void LoginDialog::slot_login_failed(int error)
{
	QString result = QString("Login failed, error code: %1").arg(error);
    showTip(result, false);
    ui->login_btn->setEnabled(true);
}

void LoginDialog::slot_tcp_connect_finish(bool success)
{
    // 连接建立成功，开始请求用户信息。
    if (success) {
        showTip(tr("聊天服务连接成功，正在登录..."), true);
        QJsonObject jsonObj;
        jsonObj["uid"] = _uid;
        jsonObj["token"] = _token;
        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);

        // 发送TCP发送id和token，请求用户数据，在TcpManager中处理，存储到UserManager中。
		qDebug() << "tcp connect success request for user data";
        qDebug() << "uid: " << _uid << " token: " << _token;
        emit TcpManager::getInstance()->sig_send_data(RequestID::ID_LOGIN_CHAT, jsonString);

    }
    else {
        qDebug() << "tcp connect failed";
        showTip(tr("连接到聊天服务器失败，网络异常"), false);
    }
}
