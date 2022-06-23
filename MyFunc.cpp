#include "MyFunc.h"

#include <iostream>

#include "Object.h"

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
