#include "TextBubble.h"
#include <QTextBlock>
#include <QTextDocument>
#include <QFontMetricsF>

TextBubble::TextBubble(const bool fromthis, const QString& text, QWidget *parent)
    : ChatBubble(fromthis, parent), _text(text)
{
    _textEdit = new QTextEdit(this);
    _textEdit->setReadOnly(true);
    _textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _textEdit->installEventFilter(this);
    _textEdit->setText(text);
    _textEdit->setStyleSheet("background: transparent; border: none;");
    _textEdit->setWordWrapMode(QTextOption::WrapAnywhere); // 英文单词中间也能断行
    // 设置字体颜色
    QPalette palette = _textEdit->palette();
    palette.setColor(QPalette::Text, QColor(255,255,255)); // 可根据需要调整颜色
    _textEdit->setPalette(palette);
    QFont font("Microsoft YaHei", 10);
    _textEdit->setFont(font);
    setPlainText(_text);
    setWidget(_textEdit);
}

TextBubble::~TextBubble()
{
}

void TextBubble::setPlainText(const QString& text)
{
    _textEdit->setPlainText(text);
    QTextDocument * doc = _textEdit->document();
    qreal margin = doc->documentMargin();
    int margin_left = this->layout()->contentsMargins().left();
    int margin_right = this->layout()->contentsMargins().right();

    QFontMetricsF font_metric(_textEdit->font());
    int max_width = 0;
    for(QTextBlock it = doc->begin(); it!=doc->end(); it=it.next()){
        int width = int(font_metric.horizontalAdvance(it.text()));
        max_width = max_width < width ? width : max_width;
    }

    setMaximumWidth(max_width + margin * 2 + (margin_left + margin_right));
}

bool TextBubble::eventFilter(QObject* watched, QEvent* event){
    if (watched == _textEdit && event->type() == QEvent::Paint) {
        adjustTextHeight();
    }
    return ChatBubble::eventFilter(watched, event);
}

void TextBubble::adjustTextHeight() {
    // 获取文本编辑器的边距
    qreal margin = _textEdit->document()->documentMargin();
    QTextDocument* doc = _textEdit->document();
    qreal text_height = 0;

    // 计算每一行的高度
    for(QTextBlock it = doc->begin(); it != doc->end(); it = it.next()) {
        QTextLayout * layout = it.layout();
        QRectF boundingRect = layout->boundingRect();
        text_height += boundingRect.height();
    }

    // 获取布局的上下边距
    int vertical_margin = this->layout()->contentsMargins().top();
    setFixedHeight(text_height + margin * 2 + vertical_margin * 2);
}