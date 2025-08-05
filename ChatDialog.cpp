#include "ChatDialog.h"
#include "ui_ChatDialog.h"
ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
{
	ui->setupUi(this);

}

ChatDialog::~ChatDialog()
{
	delete ui;
}

