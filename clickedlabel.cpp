#include "clickedlabel.h"

ClickedLabel::ClickedLabel(QWidget *parent)
	: QLabel(parent), _state(WidgetMouseState::NORMAL)
{
    setState(WidgetMouseState::NORMAL);
}

ClickedLabel::~ClickedLabel()
{}


void ClickedLabel::enterEvent(QEnterEvent * event)
{
	// 进入为悬浮
	setState(WidgetMouseState::HOVERED);
    QLabel::enterEvent(event);
}

void ClickedLabel::leaveEvent(QEvent* event)
{
	// 离开恢复正常
	setState(WidgetMouseState::NORMAL);
	QLabel::leaveEvent(event);
}

void ClickedLabel::mouseReleaseEvent(QMouseEvent *event)
{
	// 释放触发事件
	
	QLabel::mouseReleaseEvent(event);
}

void ClickedLabel::setState(WidgetMouseState state)
{
	if(_state == state){
		return;
	}
	_state = state;
	switch (state) {
		case WidgetMouseState::NORMAL:
			setProperty("state", "normal");
			break;
		case WidgetMouseState::HOVERED:
			setProperty("state", "hovered");
			break;
		case WidgetMouseState::SELECTED:
			setProperty("state", "selected");
			break;
		case WidgetMouseState::DISABLED:
			setProperty("state", "disabled");
			break;
		}
	repolish(this);
	update();
}

WidgetMouseState ClickedLabel::getState()
{
	return _state;
}

void ClickedLabel::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    QLabel::paintEvent(event);
}