#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>

namespace DemoData
{

class Object
{
public:
    void* operator new(size_t size) throw(); // throw()表示该函数不抛出任何异常
    void operator delete(void* p);
    void* operator new[](size_t size) throw();
    void operator delete[](void* p);

    bool operator ==(const Object&);
    bool operator != (const Object&);

    virtual ~Object() = 0; // virtual = 0 表示为纯虚函数，不能被调用，该类为接口类
};

};

#endif // OBJECT_H
