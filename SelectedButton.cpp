#include "SelectedButton.h"

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
        case WidgetMouseState::SELECTED_PRESSED:
            setProperty("state", "selected_pressed");
            break;
    }
}

void SelectedButton::enterEvent(QEnterEvent *event) {
    /*
        普通悬浮
    */
    if(_state != WidgetMouseState::SELECTED || _state != WidgetMouseState::SELECTED_PRESSED){
        setState(WidgetMouseState::HOVERED);
    }
    ClickedButton::enterEvent(event);
}

void SelectedButton::leaveEvent(QEvent *event) {
    // 如果选中，离开无效
    if(_state != WidgetMouseState::SELECTED || _state != WidgetMouseState::SELECTED_PRESSED){
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
    /*
        选中按下和普通按下
    */
   if(_state == WidgetMouseState::SELECTED){
       setState(WidgetMouseState::SELECTED_PRESSED);
   }
   else{
       setState(WidgetMouseState::PRESSED);
   }
    ClickedButton::mousePressEvent(event);
}

void SelectedButton::mouseReleaseEvent(QMouseEvent *event) {
    /*
        选中释放和按钮外释放
    */
    // 按钮内释放，变为选中，触发事件
    if(rect().contains(event->pos())){
        setState(WidgetMouseState::SELECTED);
        emit clicked();
    }
    // 按钮外释放
    else{
        // 选中按下后释放
        if(_state == WidgetMouseState::SELECTED_PRESSED){
            setState(WidgetMouseState::SELECTED);
        }
        // 非选中按下后释放，从hovered变为normal
        else{
            setState(WidgetMouseState::NORMAL);
        }
    }
    ClickedButton::mouseReleaseEvent(event);
}