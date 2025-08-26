#ifndef CLICKEDBUTTON_H
#define CLICKEDBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QEvent>
#include <QEnterEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>
#include "global.h"

class ClickedButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ClickedButton(QWidget *parent = nullptr);
    ~ClickedButton();
    // Set the style for different button states
    WidgetMouseState getState() const;
    virtual void setState(WidgetMouseState state);

protected slots:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:
    void clicked();

protected:
    WidgetMouseState _state;
};

#endif // CLICKEDBUTTON_H