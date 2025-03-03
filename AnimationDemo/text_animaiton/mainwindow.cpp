#include "TextAnimationLabel.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    TextAnimationLabel *label = new TextAnimationLabel(this);
    label->setText("动画文字");
    label->setFixedSize(200, 100);
    label->setStyleSheet("background-color: white;");
    setCentralWidget(label);
    
    // 启动动画
    label->startAnimation();
} 
