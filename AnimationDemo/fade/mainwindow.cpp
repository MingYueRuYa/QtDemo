#include "mainwindow.h"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("test fade window");
    resize(400, 300);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    fadeOutBtn = new QPushButton("fade out", this);
    fadeInBtn = new QPushButton("fade in", this);
    
    layout->addWidget(fadeOutBtn);
    layout->addWidget(fadeInBtn);

    animation = new QPropertyAnimation(this, "windowOpacity", this);
    animation->setDuration(1000); 


    connect(fadeOutBtn, &QPushButton::clicked, this, &MainWindow::fadeOut);
    connect(fadeInBtn, &QPushButton::clicked, this, &MainWindow::fadeIn);
}

MainWindow::~MainWindow()
{
}

void MainWindow::fadeOut()
{
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->start();
}

void MainWindow::fadeIn()
{
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start();
} 
