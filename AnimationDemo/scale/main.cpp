#include <QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    AnimatedWindow w;
    w.show();
    
    return a.exec();
} 