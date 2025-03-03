#include "TextAnimationLabel.h"
#include <QPainter>

TextAnimationLabel::TextAnimationLabel(QWidget *parent)
    : QLabel(parent)
    , m_yPosition(0)
{
    m_animation = new QPropertyAnimation(this, "yPosition", this);
    m_animation->setDuration(1000); // 动画持续2秒
    m_animation->setEasingCurve(QEasingCurve::OutInQuad);
}

void TextAnimationLabel::startAnimation()
{
    m_animation->setStartValue(-height());
    m_animation->setEndValue(0);  // 改为0，表示停在中间位置
    m_animation->start();
//    m_animation->setLoopCount(-1);
}

void TextAnimationLabel::setYPosition(qreal y)
{
    m_yPosition = y;
    update(); // 触发重绘
}

void TextAnimationLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 设置文字
    QFont font = painter.font();
    font.setPointSize(14);
    painter.setFont(font);
    
    // 计算文字位置
    QString text = this->text();
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(text);
    
    // 在当前y位置绘制文字，修改计算方式使文字在中间时居中显示
    painter.drawText(width()/2 - textWidth/2, height()/2 + m_yPosition, text);
} 
