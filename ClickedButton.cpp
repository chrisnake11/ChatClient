#include "ClickedButton.h"
#include "global.h"
ClickedButton::ClickedButton(QWidget *parent): QPushButton(parent) {
    // set hand cursor for the button
    setCursor(Qt::PointingHandCursor);
}

ClickedButton::~ClickedButton(){

}

void ClickedButton::setState(const QString& normal, const QString& hover, const QString& pressed) {
    _normal = normal;
    _hover = hover;
    _pressed = pressed;
    setProperty("state", normal);
    repolish(this); // 重新计算样式
    update(); // 通常不需要，加上更保险
}

void ClickedButton::enterEvent(QEnterEvent *event) {
    setProperty("state", _hover);
    repolish(this); // 重新计算样式
    update();
    QPushButton::enterEvent(event); // 调用基类处理
}

void ClickedButton::leaveEvent(QEvent *event) {
    setProperty("state", _normal);
    repolish(this);
    update();
    QPushButton::leaveEvent(event); // 调用基类处理
}

void ClickedButton::mousePressEvent(QMouseEvent *event) {
    setProperty("state", _pressed);
    repolish(this);
    update();
    QPushButton::mousePressEvent(event); // 调用基类处理
}

void ClickedButton::mouseReleaseEvent(QMouseEvent *event) {
    setProperty("state", _hover);
    repolish(this);
    update();
    QPushButton::mouseReleaseEvent(event); // 调用基类处理
}