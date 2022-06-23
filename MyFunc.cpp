#include "MyFunc.h"

#include <iostream>

#include "Object.h"
#include "Exception.h"
#include "SmartPointer.h"

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
