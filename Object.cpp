#include <iostream>

#include "Object.h"

using namespace std;

namespace DemoData
{

void* Object::operator new(size_t size) throw()
{
    // cout << "Object::operator new(size_t size) throw()::size = " << size << endl;
    return malloc(size);
}

void Object::operator delete(void* p)
{
    // cout << "Object::operator delete(void* p)::p = " << p << endl;
    free(p);
}

void* Object::operator new[](size_t size) throw()
{
    // cout << "Object::operator new[](size_t size) throw()::size = " << size << endl;
    return malloc(size);
}

void Object::operator delete[](void* p)
{
    // cout << "Object::operator delete[](void* p)::p = " << p << endl;
    free(p);
}

bool Object::operator ==(const Object& obj)
{
    return (this == &obj);
}

bool Object::operator !=(const Object& obj)
{
    return (this != &obj);
}

Object::~Object()
{
    // cout << "Object::~Object()" << endl;
}

};
