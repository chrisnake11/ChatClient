#pragma once

#include <QLabel>
#include "global.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>
class ClickedLabel  : public QLabel
{
	Q_OBJECT

public:
	ClickedLabel(QWidget *parent);
	~ClickedLabel();
	
	// 强制刷新状态
	void setState(WidgetMouseState state);
	WidgetMouseState getState();

protected slots:
	virtual void enterEvent(QEnterEvent* event) override;
	virtual void leaveEvent(QEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent *event) override;
signals:
	void clicked();

protected:
	// 状态
	WidgetMouseState _state;

};

