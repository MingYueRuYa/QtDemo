#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置主窗口大小
    resize(800, 400);

    // 创建一个标签作为移动的对象
    movingLabel = new QLabel(this);
    movingLabel->setText("移动的标签");
    movingLabel->setStyleSheet("QLabel { background-color: #3498db; color: white; padding: 10px; border-radius: 5px; }");
    movingLabel->setAlignment(Qt::AlignCenter);
    movingLabel->adjustSize();

    // 设置初始位置（左边）
    movingLabel->move(0, height() / 2 - movingLabel->height() / 2);

    // 创建动画对象
    animation = new QPropertyAnimation(movingLabel, "geometry", this);
    animation->setDuration(2000); // 持续2秒
    animation->setStartValue(QRect(0, 
                                 height() / 2 - movingLabel->height() / 2,
                                 movingLabel->width(), 
                                 movingLabel->height()));
    animation->setEndValue(QRect(width() - movingLabel->width(),
                               height() / 2 - movingLabel->height() / 2,
                               movingLabel->width(),
                               movingLabel->height()));
    
    // 设置动画曲线
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    
    // 设置动画循环播放
    animation->setLoopCount(-1); // -1表示无限循环
    
    // 启动动画
    animation->start();
}

MainWindow::~MainWindow()
{
} 

void MainWindow::resizeEvent(QResizeEvent *event)
{
    animation->setStartValue(QRect(0,
                                 height() / 2 - movingLabel->height() / 2,
                                 movingLabel->width(),
                                 movingLabel->height()));
    animation->setEndValue(QRect(width() - movingLabel->width(),
                               height() / 2 - movingLabel->height() / 2,
                               movingLabel->width(),
                               movingLabel->height()));
}
