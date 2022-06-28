#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "LinuxList.h"
#include "Exception.h"

namespace DemoData
{

template <typename T>
class LinkQueue : public Queue<T>
{
protected:
    struct Node : public Object
    {
        struct list_head head;
        T value;
    };

    mutable list_head m_header;
    list_head* m_current;

public:
    LinkQueue();

    bool add(const T&);
    bool remove();
    T front() const;
    void clear();
    int size() const;

    ~LinkQueue();
};

template <typename T>
LinkQueue<T>::LinkQueue()
{
    m_header.prev = NULL;
    m_header.next = NULL;
    m_current = NULL;
    this->m_front = 0;
    this->m_rear = -1;
    this->m_length = 0;
}

template <typename T>
bool LinkQueue<T>::add(const T& e)
{
    bool ret = false;

    Node* newNode = new Node();
    if(newNode)
    {
        newNode->value = e;

        if(this->m_length == 0)
        {
            INIT_LIST_HEAD(&newNode->head);
            m_header.next = &newNode->head;
        }
        else
        {
            list_add_tail(&newNode->head, m_header.next);
        }
        this->m_rear++;
        this->m_length++;
        ret = true;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No emough to create node Object...");
    }

    return ret;
}
template <typename T>
bool LinkQueue<T>::remove()
{
    bool ret = (this->m_length > 0);

    if(ret)
    {
        list_head* toDelNode = m_header.next;

        if(this->m_length == 1)
        {
            m_header.next = NULL;
            m_current = NULL;
        }
        else
        {
            m_header.next = toDelNode->next;
            if(toDelNode == m_current)
            {
                m_current = m_current->next;
            }
        }

        list_del(toDelNode);
        delete list_entry(toDelNode, Node, head);
        this->m_rear--;
        this->m_length--;
    }

    return ret;
}
template <typename T>
T LinkQueue<T>::front() const
{
    if(this->m_length > 0)
    {
        return list_entry(m_header.next, Node, head)->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No element...");
    }
}
template <typename T>
void LinkQueue<T>::clear()
{
    while(this->m_length > 0)
    {
        remove();
    }
}
template <typename T>
int LinkQueue<T>::size() const
{
    if(this->m_length == (this->m_rear + 1))
    {
        return this->m_length;
    }
}

template <typename T>
LinkQueue<T>::~LinkQueue()
{
    clear();
}

}

#endif // LINKQUEUE_H
