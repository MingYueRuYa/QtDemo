#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(qreal windowOpacity READ windowOpacity WRITE setWindowOpacity)

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void fadeOut();
    void fadeIn();

private:
    QPropertyAnimation *animation;
    QPushButton *fadeOutBtn;
    QPushButton *fadeInBtn;
};

#endif // MAINWINDOW_H 