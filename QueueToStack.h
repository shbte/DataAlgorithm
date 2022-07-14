#ifndef QUEUETOSTACK_H
#define QUEUETOSTACK_H

#include "Stack.h"
#include "LinkQueue.h"

namespace DemoData
{

/*
双队列实现栈

实现思路
    当有新元素入栈时, 将其加入队列[in]
    当需要出栈时
        将队列[in]中的n-1个元素出队列, 并进入队列[out]中
        将队列[in]中的最后一个元素出队列(出栈)
        交换两个队列的角色, [in]和[out]
 */
template <typename T>
class QueueToStack : public Stack<T>
{
protected:
    LinkQueue<T> m_queue_in;
    LinkQueue<T> m_queue_out;

    LinkQueue<T>* m_pIn;
    LinkQueue<T>* m_pOut;

    // 队列元素间的转移
    void move() const
    {
        int n = m_pIn->size() - 1;

        for(int i = 0; i < n; i++)
        {
            m_pOut->add(m_pIn->front());
            m_pIn->remove();
        }
    }

    // 交换队列
    void swap()
    {
        LinkQueue<T>* temp;

        temp = m_pIn;
        m_pIn = m_pOut;
        m_pOut = temp;
    }

public:
    QueueToStack();

    bool push(const T&);
    bool pop();
    T top() const;
    void clear();
    int size() const;

};

template <typename T>
QueueToStack<T>::QueueToStack()
{
    m_pIn = &m_queue_in;
    m_pOut = &m_queue_out;
}

template <typename T>
bool QueueToStack<T>::push(const T& e)
{
    bool ret = m_pIn->add(e);
    return ret;
}
template <typename T>
bool QueueToStack<T>::pop()
{
    bool ret = false;

    if(m_pIn->size() > 0)
    {
        move();

        m_pIn->remove();

        swap();

        ret = true;
    }

    return ret;
}
template <typename T>
T QueueToStack<T>::top() const
{
    if(m_pIn->size() > 0)
    {
        move();

        return m_pIn->front();
    }

    return NULL;
}
template <typename T>
void QueueToStack<T>::clear()
{
    m_queue_in.clear();
    m_queue_out.clear();
}
template <typename T>
int QueueToStack<T>::size() const
{
    return (m_queue_in.size() + m_queue_out.size());
}

}

#endif // QUEUETOSTACK_H
