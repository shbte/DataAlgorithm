TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    Array.h \
    DynamicArray.h \
    DynamicList.h \
    Exception.h \
    LinkList.h \
    List.h \
    MyFunc.h \
    Object.h \
    SeqList.h \
    SmartPointer.h \
    StaticArray.h \
    StaticList.h

SOURCES += \
        Exception.cpp \
        main.cpp \
        MyFunc.cpp \
        Object.cpp
