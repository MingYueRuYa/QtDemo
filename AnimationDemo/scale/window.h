#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPropertyAnimation>

class AnimatedWindow : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSize windowSize READ size WRITE resize)

public:
    explicit AnimatedWindow(QWidget *parent = nullptr);

public slots:
    void startAnimation();

private:
    QPropertyAnimation *animation;
};

#endif // WINDOW_H 