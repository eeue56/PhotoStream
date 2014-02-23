TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += `pkg-config --cflags opencv`
LIBS += `pkg-config --libs opencv`

SOURCES += main.cpp \
    roiselector.cpp

HEADERS += \
    roiselector.h

