#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ControlDemo.h"

class ControlDemo : public QMainWindow
{
    Q_OBJECT

public:
    ControlDemo(QWidget *parent = Q_NULLPTR);

private:
    Ui::ControlDemoClass ui;
};
