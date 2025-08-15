#include "SelectedLabel.h"

SelectedLabel::SelectedLabel(QWidget *parent)
	: ClickedLabel(parent)
{
    setState(WidgetMouseState::NORMAL);
}

SelectedLabel::~SelectedLabel()
{}


void SelectedLabel::enterEvent(QEnterEvent * event)
{
	// 进入为悬浮
	if (getState() == WidgetMouseState::NORMAL)
	{
		setState(WidgetMouseState::HOVERED);
	}
	qDebug() << "SelectedLabel enter" << ", state" << int(getState());
    QLabel::enterEvent(event);
}

void SelectedLabel::leaveEvent(QEvent* event)
{
	// 只有悬浮状态，离开恢复正常
	if (getState() == WidgetMouseState::HOVERED){
		setState(WidgetMouseState::NORMAL);
	}
	qDebug() << "SelectedLabel leave" << ", state" << int(getState());
	// 触发QLabel，不要使用ClickedLabel！
	QLabel::leaveEvent(event);
}

void SelectedLabel::mousePressEvent(QMouseEvent *event)
{
	// 只有悬浮状态，才会变为按下状态
	if (getState() == WidgetMouseState::HOVERED){
		setState(WidgetMouseState::PRESSED);
	}
	qDebug() << "SelectedLabel press" << ", state" << int(getState());
	QLabel::mousePressEvent(event);
}

void SelectedLabel::mouseReleaseEvent(QMouseEvent *event)
{
	// 获取坐标
	QPoint pos = event->pos();
	// 判断坐标是否在Label内部
	if(rect().contains(pos)){
		setState(WidgetMouseState::SELECTED);
		// 触发事件
	}
	else{
		setState(WidgetMouseState::NORMAL);
	}
	qDebug() << "SelectedLabel release" << ", state" << int(getState());
	// 鼠标释放，触发事件
	QLabel::mouseReleaseEvent(event);
}