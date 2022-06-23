#include "MyFunc.h"

#include <iostream>

#include "Object.h"
#include "Exception.h"
#include "SmartPointer.h"
#include "DynamicList.h"
#include "StaticList.h"

using namespace std;
using namespace DemoData;

// Object
class Test : public Object // Object::operator new(size_t size) throw()::size = 16
{
public:
    int i;
    int j;
};
class Child : public Object // Object::operator new(size_t size) throw()::size = 16
{
public:
    int k;
};
void func1()
{
    Object* obj1 = new Test();
    Object* obj2 = new Child();

    // ... ....
    cout << "obj1 = " << obj1 << endl;  // obj1 = 0x19c490f6b50
    cout << "obj2 = " << obj2 << endl;  // obj2 = 0x19c490f6b70

    delete obj1;
    delete obj2;
}

// 异常类
void func2()
{
    try
    {
        THROW_EXCEPTION(ArithmeticException, "testArithmeticException");
    }
    catch(const Exception& e)
    {
        cout << "catch(const Exception& e)" << endl;
        cout << "message : " << e.message() << endl;    // message : testArithmeticException
        cout << "location : " << e.location() << endl;  // location : ..\DemoData\MyFunc.cpp:41
    }
}

// 智能指针
class Base
{
public:
    Base()
    {
        cout << "Base::Base()" << endl;
    }

    ~Base()
    {
        cout << "Base::~Base()" << endl;
    }
};
void func3()
{
    SmartPointer<Base> spb = new Base();
    SmartPointer<Base> nspb;

    cout << "spb = " << spb.get()  << endl;     // spb = 0x19c490f6b50
    cout << "nspb = " << nspb.get()  << endl;   // nspb = 0

    nspb = spb;

    cout << "spb.isNULL = " << spb.isNULL() << ", this = " << spb.get() << endl;    // spb.isNULL = 1, this = 0
    cout << "nspb.isNULL = " << nspb.isNULL() << ", this = " << nspb.get() << endl; // nspb.isNULL = 0, this = 0x19c490f6b50
}

// 线性表
void func4()
{
    StaticList<int, 5> sl;

    for(int i = 0; i < sl.capacity(); i++)
    {
        sl.insert(i, i);
    }
    for(int i = 0; i < sl.length(); i++)
    {
        cout << "sl[" << i << "] = " << sl[i] << "    ";    // sl[0] = 0    sl[1] = 1    sl[2] = 2    sl[3] = 3    sl[4] = 4
    }
    cout << endl;

    sl[0] = sl[0] + 5;
    for(int i = 0; i < sl.length(); i++)
    {
        cout << "sl[" << i << "] = " << sl[i] << "    ";    // sl[0] = 5    sl[1] = 1    sl[2] = 2    sl[3] = 3    sl[4] = 4
    }
    cout << endl;

    try
    {
        sl[5] = 6;
    }
    catch(const Exception& e)
    {
        cout << "const Exception: " << endl;
        cout << e.message() << endl;    // Array index out of bounds.
        cout << e.location() << endl;   // ..\DemoData\SeqList.h:148
    }
    cout << endl;

    DynamicList<int> dl(5);

    for(int i = 0; i < dl.capacity(); i++)
    {
        dl.insert(i, i);
    }
    for(int i = 0; i < dl.length(); i++)
    {
        cout << "dl[" << i << "] = " << dl[i] << "    ";    // dl[0] = 0    dl[1] = 1    dl[2] = 2    dl[3] = 3    dl[4] = 4
    }
    cout << endl;

    dl[0] = dl[0] + 5;
    for(int i = 0; i < dl.length(); i++)
    {
        cout << "dl[" << i << "] = " << dl[i] << "    ";    // dl[0] = 5    dl[1] = 1    dl[2] = 2    dl[3] = 3    dl[4] = 4
    }
    cout << endl;

    try
    {
        dl[5] = 6;
    }
    catch(const Exception& e)
    {
        cout << "const Exception: " << endl;
        cout << e.message() << endl;    // Array index out of bounds.
        cout << e.location() << endl;   // ..\DemoData\SeqList.h:148
    }

    dl.resize(4);
    for(int i = 0; i < dl.length(); i++)
    {
        cout << "dl[" << i << "] = " << dl[i] << "    ";    // dl[0] = 5    dl[1] = 1    dl[2] = 2    dl[3] = 3
    }
    cout << endl;
    dl.resize(9);
    for(int i = 0; i < dl.length(); i++)
    {
        cout << "dl[" << i << "] = " << dl[i] << "    ";    // dl[0] = 5    dl[1] = 1    dl[2] = 2    dl[3] = 3
    }
    cout << endl;
    dl.insert(3, 9);
    dl.insert(9);
    for(int i = 0; i < dl.length(); i++)
    {
        cout << "dl[" << i << "] = " << dl[i] << "    ";    // dl[0] = 5    dl[1] = 1    dl[2] = 2    dl[3] = 9    dl[4] = 3    dl[5] = 9
    }
    cout << endl;
}
