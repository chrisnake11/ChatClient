#ifndef CLICKEDBUTTON_H
#define CLICKEDBUTTON_H

#include <QPushButton>

class ClickedButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ClickedButton(QWidget *parent = nullptr);
    ~ClickedButton();
    // Set the style for different button states
    void setState(const QString &normal, const QString &hover, const QString &pressed);

protected:
    virtual void enterEvent(QEnterEvent *event) override; // extend from QWidget
    virtual void leaveEvent(QEvent *event) override; // extend from QWidget
    virtual void mousePressEvent(QMouseEvent *event) override; // extend from AbstractButton
    virtual void mouseReleaseEvent(QMouseEvent *event) override; // extend from AbstractButton

private:
    QString _normal;   // Normal state style
    QString _hover;   // Hover state style
    QString _pressed; // Pressed state style
};

#endif // CLICKEDBUTTON_H