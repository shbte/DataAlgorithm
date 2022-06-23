TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    Exception.h \
    MyFunc.h \
    Object.h

SOURCES += \
        Exception.cpp \
        main.cpp \
        MyFunc.cpp \
        Object.cpp
