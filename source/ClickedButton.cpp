#include "ClickedButton.h"
#include "global.h"

ClickedButton::ClickedButton(QWidget *parent): QPushButton(parent) {
    // set hand cursor for the button
    setState(WidgetMouseState::NORMAL);
}

ClickedButton::~ClickedButton(){

}

void ClickedButton::enterEvent(QEnterEvent *event) {
    setState(WidgetMouseState::HOVERED);
    QPushButton::enterEvent(event);
}

void ClickedButton::leaveEvent(QEvent *event) {
    setState(WidgetMouseState::NORMAL);
    QPushButton::leaveEvent(event);
}

void ClickedButton::mousePressEvent(QMouseEvent *event) {
    setState(WidgetMouseState::PRESSED);
    QPushButton::mousePressEvent(event);
}

void ClickedButton::mouseReleaseEvent(QMouseEvent *event) {
    // 如果释放时在按钮区域内，且状态为PRESSED
    // 变为Hover状态，发出clicked信号
    if(rect().contains(event->pos())){
        if(_state == WidgetMouseState::PRESSED){
            setState(WidgetMouseState::HOVERED);
            emit clicked();
        }

    }
    // 没在区域内，不触发信号，恢复到NORMAL状态
    else{
        setState(WidgetMouseState::NORMAL);
    }
    QPushButton::mouseReleaseEvent(event);
}

WidgetMouseState ClickedButton::getState() const {
    return _state;
}

void ClickedButton::setState(WidgetMouseState state) {
    if(_state == state){
        return;
    }
    _state = state;
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
    }
    repolish(this);
    update();
}

void ClickedButton::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this); // 从当前组件获取QStyle和QSS样式
    QPainter painter(this); // 初始化一个QPainter对象
    // 按照opt样式，使用painter绘制QWidget组件
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    // 继续绘制子组件
    QPushButton::paintEvent(event);
}
