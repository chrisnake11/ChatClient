#include "SelectedButton.h"

SelectedButton::SelectedButton(QWidget *parent) 
    : ClickedButton(parent) {
    setState(WidgetMouseState::NORMAL);
}

SelectedButton::~SelectedButton(){
    
}

void SelectedButton::setState(WidgetMouseState state) {
    if(_state == state) {
        return;
    }
    switch (state){
        case WidgetMouseState::NORMAL:
            setProperty("state", "normal");
            break;
        case WidgetMouseState::HOVERED:
            setProperty("state", "hovered");
            break;
        case WidgetMouseState::PRESSED:
            setProperty("state", "pressed");
            break;
        case WidgetMouseState::SELECTED:
            setProperty("state", "selected");
            break;
    }
}

void SelectedButton::enterEvent(QEnterEvent *event) {
    if(_state != WidgetMouseState::SELECTED){
        setState(WidgetMouseState::HOVERED);
    }
    ClickedButton::enterEvent(event);
}

void SelectedButton::leaveEvent(QEvent *event) {
    // 如果选中，离开无效
    if(_state != WidgetMouseState::SELECTED){
        // 如果是press，变为hovered
        if(_state == WidgetMouseState::PRESSED){
            setState(WidgetMouseState::HOVERED);
        }

        // 否则变成普通
        else{
            setState(WidgetMouseState::NORMAL);
        }
    }

    ClickedButton::leaveEvent(event);
}

void SelectedButton::mousePressEvent(QMouseEvent *event) {
    if(_state != WidgetMouseState::SELECTED){
            ClickedButton::mousePressEvent(event);
    }
}

void SelectedButton::mouseReleaseEvent(QMouseEvent *event) {
    // 按钮内释放，变为选中，触发事件
    if(rect().contains(event->pos())){
        setState(WidgetMouseState::SELECTED);
        emit clicked();
    }
    // 按钮外释放
    else{
        if(_state != WidgetMouseState::SELECTED){
            setState(WidgetMouseState::NORMAL);
        }
    }
    ClickedButton::mouseReleaseEvent(event);
}