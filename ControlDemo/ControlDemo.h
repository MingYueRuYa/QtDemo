#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ControlDemo.h"

class ControlDemo : public QMainWindow
{
    Q_OBJECT

public:
    ControlDemo(QWidget *parent = Q_NULLPTR);

protected slots:
    void on_test_state_btn_clicked();

private:
    void _init_btn();

 private:
    Ui::ControlDemoClass ui;
};
