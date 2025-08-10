#ifndef SELECTEDBUTTON_H
#define SELECTEDBUTTON_H

#include "ClickedButton.h"

class SelectedButton : public ClickedButton{
    Q_OBJECT
public:
    SelectedButton(QWidget *parent = nullptr);
    ~SelectedButton();
    void setState(WidgetMouseState state) override;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // SELECTEDBUTTON_H