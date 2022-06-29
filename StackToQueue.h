#ifndef STACKTOQUEUE_H
#define STACKTOQUEUE_H

#include "Queue.h"
#include "LinkStack.h"

namespace DemoData
{

/*
双栈实现队列

实现思路
    当有新元素时, 将其压入stack_in
    当需要出队时
        stack_out.size() == 0
            将stack_in中的元素逐一弹出并压入stack_out
            将stack_out的栈顶元素弹出
        stack_out.size() > 0
            将stack_out的栈顶元素弹出
 */
template <typename T>
class StackToQueue : public Queue<T>
{
protected:
    mutable LinkStack<T> m_stack_in;
    mutable LinkStack<T> m_stack_out;

    // 栈元素间的转移
    void move() const
    {
        if(m_stack_out.size() == 0)
        {
            while(m_stack_in.size() > 0)
            {
                m_stack_out.push(m_stack_in.top());
                m_stack_in.pop();
            }
        }
    }

public:
    bool add(const T&);
    bool remove();
    T front() const;
    void clear();
    int size() const;
};

template <typename T>
bool StackToQueue<T>::add(const T& e)
{
    bool ret = m_stack_in.push(e);

    return ret;
}
template <typename T>
bool StackToQueue<T>::remove()
{
    bool ret = false;

    move();

    if(m_stack_out.size() > 0)
    {
        ret = m_stack_out.pop();
    }

    return ret;
}
template <typename T>
T StackToQueue<T>::front() const
{
    T ret;

    move();

    if(m_stack_out.size() > 0)
    {
        ret = m_stack_out.top();
    }

    return ret;
}
template <typename T>
void StackToQueue<T>::clear()
{
    m_stack_in.clear();
    m_stack_out.clear();
}
template <typename T>
int StackToQueue<T>::size() const
{
    return (m_stack_in.size() + m_stack_out.size());
}

}

#endif // STACKTOQUEUE_H
