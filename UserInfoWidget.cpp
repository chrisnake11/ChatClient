#include "UserInfoWidget.h"
#include "ui_userinfowidget.h"
#include <QPainter>
#include <QPixmap>
UserInfoWidget::UserInfoWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::UserInfoWidget())
	, _user_info()
{
    ui->setupUi(this);
}

UserInfoWidget::UserInfoWidget(const UserInfo& user_info, QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::UserInfoWidget())
	, _user_info(user_info)
{
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    initUI();
}

UserInfoWidget::~UserInfoWidget()
{
    delete ui;
}

void UserInfoWidget::initUI()
{
    qDebug() << "initUI called, username:" << _user_info.username;
    // 设置头像
    setDefaultAvatar();
    // 设置名称
    ui->name_label->setText(_user_info.username);
    // 设置个性签名
    ui->personal_sign_label->setText(_user_info.personalSignature);
    QString user_info = QString("sex: %1, age: %2, address: %3")
            .arg(_user_info.sex == 1 ? "Male" : "Female")
            .arg(_user_info.age)
            .arg(_user_info.address);
    // 设置信息
    ui->userinfo_label->setText(user_info);

    connect(ui->user_send_btn, &QPushButton::clicked, this, &UserInfoWidget::onChatButtonClicked);

    update();
}

void UserInfoWidget::setDefaultAvatar(){
    ui->avatar_label->setText("");
    if(!_user_info.avatar.isNull()){
        QPixmap scaledPixmap = QPixmap(":/images/wechat.png").scaled(80, 80, Qt::KeepAspectRatio, Qt::FastTransformation);
        ui->avatar_label->setPixmap(scaledPixmap);
    }
    else{
        // 如果没有默认图片，创建一个简单的圆形头像
        QPixmap pixmap(80, 80);
        pixmap.fill(Qt::transparent);
        
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(QColor("#cccccc")));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(0, 0, 80, 80);

        ui->avatar_label->setPixmap(pixmap);
    }
    ui->avatar_label->setAlignment(Qt::AlignCenter);
}

void UserInfoWidget::onChatButtonClicked(){
    emit chatWithUser(ui->name_label->text());
}