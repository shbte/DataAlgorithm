#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace DemoData
{

template <typename T, int N>
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];

public:
    StaticQueue();

    bool add(const T&);
    bool remove();
    T front() const;
    void clear();
    int size() const;

    int capacity() const;
};

template <typename T, int N>
StaticQueue<T, N>::StaticQueue()
{
    this->m_front = 0;
    this->m_rear = -1;
    this->m_length = 0;
}

template <typename T, int N>
bool StaticQueue<T, N>::add(const T& e)
{
    bool ret = (this->m_length < N);

    if(ret)
    {
        int index = (this->m_rear + 1) % N;
        m_space[index] = e;
        this->m_rear = index;
        this->m_length++;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No space in add element...");
    }

    return ret;
}
template <typename T, int N>
bool StaticQueue<T, N>::remove()
{
    bool ret = (this->m_length > 0);

    if(ret)
    {
        this->m_front = (this->m_front + 1) % N;
        this->m_length--;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No element in remove...");
    }

    return ret;
}
template <typename T, int N>
T StaticQueue<T, N>::front() const
{
    T ret;

    if(this->m_length > 0)
    {
        ret = m_space[this->m_front];
    }

    return ret;
}
template <typename T, int N>
void StaticQueue<T, N>::clear()
{
    while(this->m_length)
    {
        remove();
    }
}
template <typename T, int N>
int StaticQueue<T, N>::size() const
{
    return this->m_length;
}

template <typename T, int N>
int StaticQueue<T, N>::capacity() const
{
    return N;
}

}

#endif // STATICQUEUE_H
