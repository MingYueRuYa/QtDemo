QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = TextAnimation
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    TextAnimationLabel.cpp

HEADERS += \
    mainwindow.h \
    TextAnimationLabel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target 