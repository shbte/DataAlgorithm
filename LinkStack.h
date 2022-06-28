#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "LinkList.h"

namespace DemoData
{

template <typename T>
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> list;

public:
    LinkStack();

    bool push(const T&);
    bool pop();
    T top() const;
    void clear();
    int size() const;
};

template <typename T>
LinkStack<T>::LinkStack()
{
    this->m_top = 0;
    this->m_size = 0;
}

template <typename T>
bool LinkStack<T>::push(const T& e)
{
    bool ret = list.insert(0, e);

    this->m_top = 0;
    this->m_size++;

    return ret;
}
template <typename T>
bool LinkStack<T>::pop()
{
    bool ret = this->m_size;

    if(ret)
    {
        list.remove(0);
        this->m_size--;
    }

    return ret;
}
template <typename T>
T LinkStack<T>::top() const
{
    T ret;

    if(list.get(0, ret) && (this->m_size))
    {
        return ret;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No top element...");
    }
}
template <typename T>
void LinkStack<T>::clear()
{
    while(this->m_size)
    {
        list.remove(0);
        this->m_size--;
    }
}
template <typename T>
int LinkStack<T>::size() const
{
    return this->m_size;
}

}

#endif // LINKSTACK_H
