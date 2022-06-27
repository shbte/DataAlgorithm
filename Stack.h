#ifndef STACK_H
#define STACK_H

#include "Object.h"

namespace DemoData
{

template <typename T>
class Stack : public Object
{
protected:
    int m_top;
    int m_size;

public:
    virtual bool push(const T&) = 0;
    virtual bool pop() = 0;
    virtual T top() const = 0;
    virtual void clear() = 0;
    virtual int size() const = 0;
};

}

#endif // STACK_H
