#include "resetdialog.h"
#include "httpmanager.h"
#include "timerbtn.h"
ResetDialog::ResetDialog(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::ResetDialogClass())
{
	ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

	ui->err_tip->clear();

	// 将 get_code_btn 替换为一个新的 timerbtn
	{
		// 获取原来的 QPushButton 位置
		QPushButton* old_btn = ui->get_code_btn;

		// 创建一个新的 timerbtn
		timerbtn* new_btn = new timerbtn(this);
		new_btn->setObjectName("get_code_btn");
		new_btn->setText(old_btn->text());

		// 将新的 timerbtn 替换到原来的位置
		QLayout* layout = old_btn->parentWidget()->layout();
		if (layout) {
			layout->replaceWidget(old_btn, new_btn);
			old_btn->hide();
		}
		old_btn->hide();
		old_btn->deleteLater();

		// 强制更新 UI 指针
		ui->get_code_btn = new_btn;
	}
	qDebug() << "get_code_btn is of type:" << ui->get_code_btn->metaObject()->className();

	connect(ui->return_btn, &QPushButton::clicked, this, &ResetDialog::switch_to_login);

	connect(HttpManager::getInstance().get(), &HttpManager::sig_reset_mod_finish, this, &ResetDialog::on_reset_mod_finish);

	// on_xxx_do 需要重新实现QT的信号槽机制
	connect(ui->get_code_btn, &QPushButton::clicked, this, &ResetDialog::on_get_code_btn_clicked);

	connect(ui->reset_btn, &QPushButton::clicked, this, &ResetDialog::on_reset_btn_clicked);

	showTip(tr("enter email and passwd to reset"), true);

	initHttpHandlers();

	// 连接输入框的编辑完成信号
	connect(ui->email_text, &QLineEdit::editingFinished, this, [this]() {
		checkEmailValid();
		});

	connect(ui->passwd_text, &QLineEdit::editingFinished, this, [this]() {
		checkPasswdValid();
		});

	connect(ui->confirm_text, &QLineEdit::editingFinished, this, [this]() {
		checkConfirmValid();
		});

	connect(ui->code_text, &QLineEdit::editingFinished, this, [this]() {
		checkCodeValid();
		});

	// 连接可见性切换标签的点击事件
	ui->passwd_visible->setCursor(Qt::PointingHandCursor);
	ui->confirm_visible->setCursor(Qt::PointingHandCursor);

	// 初始化标签的状态
	ui->passwd_visible->setState("unvisible", "unvisible_hover", "", "visible",
		"visible_hover", "");
	ui->confirm_visible->setState("unvisible", "unvisible_hover", "", "visible",
		"visible_hover", "");

	// 连接密码可见性切换标签的点击事件
	connect(ui->passwd_visible, &clickedlabel::clicked, [this]() {
		auto state = ui->passwd_visible->getCurrentState();
		if (state == ClickLabelState::NORMAL) {
			ui->passwd_text->setEchoMode(QLineEdit::Password);
		}
		else {
			ui->passwd_text->setEchoMode(QLineEdit::Normal);
		}
		qDebug() << "passwd visible label was clicked, state: " << state;
		});

	connect(ui->confirm_visible, &clickedlabel::clicked, [this]() {
		auto state = ui->confirm_visible->getCurrentState();
		if (state == ClickLabelState::NORMAL) {
			ui->confirm_text->setEchoMode(QLineEdit::Password);
		}
		else {
			ui->confirm_text->setEchoMode(QLineEdit::Normal);
		}
		qDebug() << "confirm visible label was clicked, state: " << state;
		});

}

ResetDialog::~ResetDialog()
{
	delete ui;
}

void ResetDialog::on_get_code_btn_clicked() {
	auto email = ui->email_text->text();
	// ��ʽ���
	QRegularExpression email_regex(R"(^\w+(-+.\w+)*@\w+(-.\w+)*.\w+(-.\w+)*$)");
	if (!email_regex.match(email).hasMatch()) {
        showTip(tr("email format error"), false);
		qDebug() << "email format error";
		return;
	}
    showTip(tr("getting varify code..."), true);
	QJsonObject request;
	request["email"] = email;
	request["error"] = 0;
	HttpManager::getInstance()->postHttpRequest(QUrl(gate_url_prefix + "/" + "get_varify_code"), request, RequestID::ID_GET_VARIFY_CODE, Modules::RESET_MODEL);
}

void ResetDialog::on_reset_mod_finish(RequestID id, QString res, ErrorCodes err) {
	if (err != ErrorCodes::SUCCESS) {
		showTip(tr("Get code failed, Http reuqest error"), false);
		qDebug() << "Get code failed, Http reuqest error";
		return;
	}

	QJsonDocument doc = QJsonDocument::fromJson(res.toUtf8());

	if (doc.isNull() || !doc.isObject()) {
		showTip(tr("Get code failed, Json parse error"), false);
		qDebug() << "Get code failed, Json parse error";
		return;
	}

	_request_handlers[id](doc.object());
}

void ResetDialog::on_reset_btn_clicked() {
	auto email = ui->email_text->text();
	auto passwd = ui->passwd_text->text();
	auto confirm = ui->confirm_text->text();
	auto code = ui->code_text->text();
	// check text format
	if (email == "") {
		showTip("email can't be empty", false);
		return;
	}
	if (passwd == "") {
		showTip("password can't be empty", false);
		return;
	}
	if (confirm != passwd) {
		showTip("confirm not match password", false);
		return;
	}
	if (code == "") {
		showTip("code can't be empty", false);
		return;
	}

	QJsonObject json_obj;
	json_obj["email"] = email;
	json_obj["passwd"] = md5Encrypt(passwd);
	json_obj["confirm"] = md5Encrypt(confirm);
	json_obj["code"] = code;

	// send register http request
	HttpManager::getInstance()->postHttpRequest(QUrl(gate_url_prefix + "/user_reset"),
		json_obj, RequestID::ID_RESET_USER, Modules::RESET_MODEL);
}

void ResetDialog::initHttpHandlers() {
	_request_handlers.insert(RequestID::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj) {
		int error = jsonObj["error"].toInt();
		if (error != ErrorCodes::SUCCESS) {
			showTip(tr("param error"), false);
			return;
		}
		showTip(tr("varified code has been sent to email"), true);
		});

	_request_handlers.insert(RequestID::ID_RESET_USER, [this](const QJsonObject& jsonObj) {
		int error = jsonObj["error"].toInt();
		switch (error) {
		case ErrorCodes::SUCCESS:
			showTip(tr("reset success"), true);
			qDebug("reset success, emit signals");
			emit this->reset_success();
			return;
		case ErrorCodes::ERROR_EMAIL_NOT_MATCH:
			showTip(tr("email is not exists!"), false);
			return;
		case ErrorCodes::ERROR_VARIFY_EXPIRED:
			showTip(tr("ERROR_VARIFY_EXPIRED!"), false);
			return;
		case ErrorCodes::ERROR_VARIFY_WRONG:
			showTip(tr("ERROR_VARIFY_WRONG!"), false);
			return;
		case ErrorCodes::ERROR_PASSWORD_INVALID:
			showTip(tr("ERROR_PASSWORD_INVALID!"), false);
			return;
		default:
			showTip(tr("unknow error"), false);
			qDebug("Unknown error: ");
			return;
		}
		});
}


bool ResetDialog::checkEmailValid()
{
	//��֤����ĵ�ַ�������ʽ
	auto email = ui->email_text->text();
	// �����ַ���������ʽ
	QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
	bool match = regex.match(email).hasMatch(); // ִ���������ʽƥ��
	if (!match) {
		//��ʾ���䲻��ȷ
		addTipErr(TipErr::TIP_EMAIL_ERR, tr("email address is incorrect"));
		return false;
	}
	delTipErr(TipErr::TIP_EMAIL_ERR);
	return true;
}

bool ResetDialog::checkPasswdValid()
{
	auto pass = ui->passwd_text->text();
	if (pass.length() < 6 || pass.length() > 15) {
		//��ʾ���Ȳ�׼ȷ
		addTipErr(TipErr::TIP_PWD_ERR, tr("���볤��ӦΪ6~15"));
		return false;
	}
	// ����һ���������ʽ���󣬰�����������Ҫ��
	// ����������ʽ���ͣ�
	// ^[a-zA-Z0-9!@#$%^&*]{6,15}$ ���볤������6����������ĸ�����ֺ��ض��������ַ�
	QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
	bool match = regExp.match(pass).hasMatch();
	if (!match) {
		//��ʾ�ַ��Ƿ�
		addTipErr(TipErr::TIP_PWD_ERR, tr("���ܰ����Ƿ��ַ�"));
		return false;;
	}
	delTipErr(TipErr::TIP_PWD_ERR);
	return true;
}

bool ResetDialog::checkConfirmValid()
{
	auto pass = ui->passwd_text->text();
	auto confirm = ui->confirm_text->text();
	if (pass != confirm) {
		addTipErr(TipErr::TIP_CONFIRM_ERR, tr("���벻һ��"));
		return false;
	}
	delTipErr(TipErr::TIP_CONFIRM_ERR);
	return true;
}

bool ResetDialog::checkCodeValid()
{
	auto pass = ui->code_text->text();
	if (pass.isEmpty()) {
		addTipErr(TipErr::TIP_VARIFY_ERR, tr("code can not be empty"));
		return false;
	}
	delTipErr(TipErr::TIP_VARIFY_ERR);
	return true;
}

void ResetDialog::showTip(QString str, bool success)
{
	if (success) {
		ui->err_tip->setProperty("state", "normal");
	}
	else {
		ui->err_tip->setProperty("state", "error");
	}
	repolish(ui->err_tip);
	ui->err_tip->setText(str);
}
void ResetDialog::addTipErr(TipErr err, QString tips)
{
	_tip_errs[err] = tips;
	showTip(tips, false);
}

void ResetDialog::delTipErr(TipErr err)
{
	_tip_errs.remove(err);
	if (_tip_errs.size() == 0) {
		ui->err_tip->clear();
		return;
	}

	showTip(_tip_errs.first(), false);
}
