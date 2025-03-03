#ifndef TEXTANIMATIONLABEL_H
#define TEXTANIMATIONLABEL_H

#include <QLabel>
#include <QPropertyAnimation>

class TextAnimationLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(qreal yPosition READ yPosition WRITE setYPosition)

public:
    explicit TextAnimationLabel(QWidget *parent = nullptr);
    void startAnimation();
    
    qreal yPosition() const { return m_yPosition; }
    void setYPosition(qreal y);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPropertyAnimation *m_animation;
    qreal m_yPosition;
};

#endif // TEXTANIMATIONLABEL_H 