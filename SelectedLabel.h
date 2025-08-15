#pragma once

#include <QLabel>
#include "global.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>
#include "ClickedLabel.h"
class SelectedLabel  : public ClickedLabel
{
	Q_OBJECT

public:
	SelectedLabel(QWidget *parent);
	~SelectedLabel();

public slots:
	// 重写事件
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
};

