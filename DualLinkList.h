#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Exception.h"

namespace DemoData
{

template <typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        Node* last;  // 前驱节点
        T value;
        Node* next;
    };

    mutable struct : public Object
    {
        Node* last;
        char reserved[sizeof(T)];
        Node* next;
    } m_header;

    int m_length;
    Node* m_current;
    int m_step;

    Node* position(int index) const
    {
        Node* current = reinterpret_cast<Node*>(&m_header);
        for(int i = 0; i <= index; i++)
        {
            current = current->next;
        }
        return current;
    }

    virtual Node* create()
    {
        return new Node();
    }
    virtual void destroy(Node* pn)
    {
        delete pn;
    }

public:
    DualLinkList();

    virtual bool insert(const T&);
    virtual bool insert(int, const T&);
    virtual bool remove(int);
    virtual bool set(int, const T&);
    virtual bool get(int, T&) const;
    virtual int length() const;
    virtual int find(const T&) const;

    virtual bool moveInit(int, int = 1);
    virtual bool end();
    virtual T currentValue();
    virtual bool next();
    virtual bool last();

    virtual void clear();

    virtual ~DualLinkList();
};

template <typename T>
DualLinkList<T>::DualLinkList()
{
    m_header.last = NULL;
    // m_header.reserved = NULL;
    m_header.next = NULL;
    m_length = 0;
    m_current =  NULL;
    m_step = 1;
}

template <typename T>
bool DualLinkList<T>::insert(const T& e)
{
    bool ret = insert(m_length, e);
    return ret;
}
template <typename T>
bool DualLinkList<T>::insert(int index, const T& e)
{
    bool ret = ((0 <= index) && (index <= m_length));

    if(ret)
    {
        Node* newNode = create();

        if(newNode != NULL)
        {
            Node* lastNode = position(index - 1);
            Node* nextNode = lastNode->next;

            newNode->value = e;
            newNode->last = lastNode;
            newNode->next = lastNode->next;

            lastNode->next = newNode;
            if(nextNode)
            {
                nextNode->last = newNode;
            }

            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough to create Node Object...");
        }
    }

    return ret;
}

template <typename T>
bool DualLinkList<T>::remove(int index)
{
    bool ret = ((0 <= index) && (index < m_length));

    if(ret)
    {
        Node* toDelNode = position(index);
        Node* lastNode = toDelNode->last;
        Node* nextNode = toDelNode->next;

        lastNode->next = toDelNode->next;
        if(nextNode)
        {
            nextNode->last = toDelNode->last;
        }

        if(m_current == toDelNode)
        {
            m_current = toDelNode->next;
        }

        destroy(toDelNode);
        m_length--;

        if(m_length == 0)
        {
            m_header.last = NULL;
            m_header.next = NULL;
            m_current = NULL;
        }
    }

    return ret;
}

template <typename T>
bool DualLinkList<T>::set(int index, const T& e)
{
    bool ret = ((0 <= index) && (index < m_length));

    if(ret)
    {
        Node* current = position(index);
        current->value = e;
    }

    return ret;
}
template <typename T>
bool DualLinkList<T>::get(int index, T& e) const
{
    bool ret = ((0 <= index) && (index < m_length));

    if(ret)
    {
        Node* current = position(index);
        e = current->value;
    }

    return ret;
}

template <typename T>
int DualLinkList<T>::length() const
{
    return m_length;
}
template <typename T>
int DualLinkList<T>::find(const T& e) const
{
    Node* node = reinterpret_cast<Node*>(&m_header);
    int ret = -1;

    for(int index = 0; index < m_length; index++)
    {
        node = node->next;
        if(node->value == e)
        {
            ret = index;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Paramter is inval...");
        }
    }

    return ret;
}

template <typename T>
bool DualLinkList<T>::moveInit(int index, int step)
{
    bool ret = ((0 <= index) && (index < m_length));

    if(ret)
    {
        m_current = position(index);
        m_step = step;
    }

    return ret;
}
template <typename T>
bool DualLinkList<T>::end()
{
    return (m_current == NULL);
}
template <typename T>
bool DualLinkList<T>::next()
{
    int i = 0;

    while((i < m_step) && !end())
    {
        m_current = m_current->next;
        i++;
    }

    return (m_step == i);
}
template <typename T>
bool DualLinkList<T>::last()
{
    int i = 0;

    while((i < m_step) && !end())
    {
        m_current = m_current->last;
        i++;
    }

    return (m_step == i);
}
template <typename T>
T DualLinkList<T>::currentValue()
{
    return m_current->value;
}

template <typename T>
void DualLinkList<T>::clear()
{
    while(m_length)
    {
        remove(m_length - 1);
    }
}

template <typename T>
DualLinkList<T>::~DualLinkList()
{
    clear();
}

}

#endif // DUALLINKLIST_H
