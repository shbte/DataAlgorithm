TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    DynamicList.h \
    Exception.h \
    List.h \
    MyFunc.h \
    Object.h \
    SeqList.h \
    SmartPointer.h \
    StaticList.h

SOURCES += \
        Exception.cpp \
        main.cpp \
        MyFunc.cpp \
        Object.cpp
