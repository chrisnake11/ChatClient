#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>
#include "global.h"
#include <QMap>
#include "Data.h"


namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    void showTip(QString str, bool success);

public slots:
    void on_login_btn_clicked();
    void on_forget_label_clicked();
    // Http登录请求成功
    void slot_login_mod_finish(RequestID id, QString res, ErrorCodes err);
    void slot_login_failed(int error);
    // Tcp连接登录成功，开始获取聊天信息
    void slot_tcp_connect_finish(bool success);

signals:
    void switch_to_register();
    void switch_to_reset();
    void switch_to_chat();
    // 发送Tcp连接信号
    void sig_connect_tcp(ServerInfo server_info);

private:
    Ui::LoginDialog *ui;

    // HTTP请求的回调函数
    QMap<RequestID, std::function<void(const QJsonObject&)>> _handlers;
    // 初始化Handler的回调函数
    void initHttpHandlers();
    quint16 _uid;
    QString _token;

    bool checkNameValid();
    bool checkPasswdValid();

    QMap<TipErr, QString> _tip_errs;
    void addTipErr(TipErr err, QString tips);
    void delTipErr(TipErr err);
};

#endif // LOGINDIALOG_H
