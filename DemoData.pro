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
    LinkListSharedPointer.h \
    List.h \
    MyFunc.h \
    Object.h \
    Pointer.h \
    SeqList.h \
    SharedPointer.h \
    SmartPointer.h \
    StaticArray.h \
    StaticLinkList.h \
    StaticLinkListSharedPointer.h \
    StaticList.h

SOURCES += \
        Exception.cpp \
        main.cpp \
        MyFunc.cpp \
        Object.cpp
