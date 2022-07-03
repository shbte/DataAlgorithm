TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    Array.h \
    CircleLinkList.h \
    DDString.h \
    DDStringFunc.h \
    DualCircleLinkList.h \
    DualLinkList.h \
    DynamicArray.h \
    DynamicList.h \
    Exception.h \
    LinkList.h \
    LinkListSharedPointer.h \
    LinkQueue.h \
    LinkStack.h \
    LinuxList.h \
    List.h \
    MyFunc.h \
    Object.h \
    Pointer.h \
    Queue.h \
    QueueToStack.h \
    Recursion.h \
    SeqList.h \
    SharedPointer.h \
    SmartPointer.h \
    Stack.h \
    StackToQueue.h \
    StaticArray.h \
    StaticLinkList.h \
    StaticLinkListSharedPointer.h \
    StaticList.h \
    StaticQueue.h \
    StaticStack.h

SOURCES += \
        DDString.cpp \
        DDStringFunc.cpp \
        Exception.cpp \
        Recursion.cpp \
        SymbolMath.cpp \
        main.cpp \
        MyFunc.cpp \
        Object.cpp
