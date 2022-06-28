#ifndef QUEUE_H
#define QUEUE_H

#include "Object.h"

namespace DemoData
{

template <typename T>
class Queue : public Object
{
protected:
    int m_front;
    int m_rear;
    int m_length;

public:
    virtual bool add(const T&) = 0;
    virtual bool remove() = 0;
    virtual T front() const = 0;
    virtual void clear() = 0;
    virtual int size() const = 0;
};

}

#endif // QUEUE_H
