#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace DemoData
{

template <typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];

public:
    StaticStack();

    bool push(const T&);
    bool pop();
    T top() const;
    void clear();
    int size() const;

    int capacity() const;

    ~StaticStack();
};

template <typename T, int N>
StaticStack<T, N>::StaticStack()
{
    this->m_top = -1;
    this->m_size = 0;
}

template <typename T, int N>
bool StaticStack<T, N>::push(const T& e)
{
    bool ret = (this->m_size != N);

    if(ret)
    {
        m_space[this->m_top + 1] = e;
        this->m_top++;
        this->m_size++;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No space to push ");
    }

    return ret;
}
template <typename T, int N>
bool StaticStack<T, N>::pop()
{
    bool ret = (0 < this->m_size);

    if(ret)
    {
        this->m_top--;
        this->m_size--;
    }

    return ret;
}
template <typename T, int N>
T StaticStack<T, N>::top() const
{
    return m_space[this->m_top];
}
template <typename T, int N>
void StaticStack<T, N>::clear()
{
    this->m_top = -1;
    this->m_size = 0;
}
template <typename T, int N>
int StaticStack<T, N>::size() const
{
    return this->m_size;
}

template <typename T, int N>
int StaticStack<T, N>::capacity() const
{
    return N;
}

template <typename T, int N>
StaticStack<T, N>::~StaticStack()
{

}

}

#endif // STATICSTACK_H
