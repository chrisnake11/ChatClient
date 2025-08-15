#ifndef TEXTBUBBLE_H
#define TEXTBUBBLE_H

#include <QWidget>
#include <QString>
#include <QTextEdit>
#include "ChatBubble.h"

class TextBubble : public ChatBubble
{
    Q_OBJECT

public:
    explicit TextBubble(const bool fromthis, const QString& text, QWidget *parent = nullptr);
    ~TextBubble();
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    void setPlainText(const QString& text);
    void adjustTextHeight();
private:
    QString _text;
    QTextEdit* _textEdit;
};

#endif // TEXTBUBBLE_H