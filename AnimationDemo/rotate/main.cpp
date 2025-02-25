#include <QApplication>
#include "rotatingimage.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    RotatingImage *rotatingImage = new RotatingImage();
    rotatingImage->resize(400, 400);
    rotatingImage->show();
    
    return app.exec();
} 