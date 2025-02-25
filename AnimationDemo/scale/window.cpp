#include "window.h"
#include <QVBoxLayout>
#include <QPushButton>

AnimatedWindow::AnimatedWindow(QWidget *parent)
    : QWidget(parent)
{
    // 设置初始窗口大小
    resize(200, 200);
    
    // 创建动画对象
    animation = new QPropertyAnimation(this, "windowSize", this);
    animation->setDuration(1000); // 动画持续1秒
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    
    // 创建一个按钮来触发动画
    QPushButton *button = new QPushButton("开始动画", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(button);
    
    connect(button, &QPushButton::clicked, this, &AnimatedWindow::startAnimation);
}

void AnimatedWindow::startAnimation()
{
    // 设置动画的起始值和结束值
    if (width() == 200) {
        animation->setStartValue(QSize(200, 200));
        animation->setEndValue(QSize(400, 400));
    } else {
        animation->setStartValue(QSize(400, 400));
        animation->setEndValue(QSize(200, 200));
    }
    
    // 开始动画
    animation->start();
} 