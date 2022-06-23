#include "MyFunc.h"

#include <iostream>

#include "Exception.h"

using namespace std;
using namespace DemoData;

// 异常类
void func1()
{
    try
    {
        THROW_EXCEPTION(ArithmeticException, "testArithmeticException");
    }
    catch(const Exception& e)
    {
        cout << "catch(const Exception& e)" << endl;
        cout << "message : " << e.message() << endl;    // message : testArithmeticException
        cout << "location : " << e.location() << endl;  // location : ..\DemoData\MyFunc.cpp:15
    }
}

