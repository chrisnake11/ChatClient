#ifndef CUSTOMSCROLLAREA_H
#define CUSTOMSCROLLAREA_H

#include <QScrollArea>
#include <QMouseEvent>
#include <QTimer>

class CustomScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    explicit CustomScrollArea(QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void hideScrollBars();

private:
    QTimer *hideTimer;
    bool isScrollBarVisible;
    void showScrollBars();
};

#endif // CUSTOMSCROLLAREA_H