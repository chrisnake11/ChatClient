#pragma once

#include <QDialog>
#include <QWidget>
namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
	Q_OBJECT

public:
	ChatDialog(QWidget *parent = nullptr);
	~ChatDialog();

private:
	Ui::ChatDialog *ui;
};

