#include "ControlDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlDemo w;
    w.show();
    return a.exec();
}
