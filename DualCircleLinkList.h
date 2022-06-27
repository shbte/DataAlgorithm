#ifndef DUALCIRCLELINKLIST_H
#define DUALCIRCLELINKLIST_H

#include "DualLinkList.h"
#include "LinuxList.h"

namespace DemoData
{

template <typename T>
class DualCircleLinkList : public DualLinkList<T>
{
    struct Node : public Object
    {
        struct list_head head;
        T value;
    };

    mutable list_head m_header;

    list_head* m_current;

    list_head* position(int index) const
    {
        // Node* pos = reinterpret_cast<Node*>(&m_header);
        list_head* pos = &m_header;
        for(int i = 0; i <= index; i++)
        {
            pos = pos->next;
        }
        return pos;
    }

public:
    DualCircleLinkList();

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
    virtual T get(int);
    virtual bool next();
    virtual bool last();

    virtual void clear();

    ~DualCircleLinkList();
};

template <typename T>
DualCircleLinkList<T>::DualCircleLinkList()
{
    m_header.prev = NULL;
    m_header.next = NULL;
    // m_header.value = NULL;
    this->m_length = 0;
    m_current = NULL;
    this->m_step = 1;
}

template <typename T>
bool DualCircleLinkList<T>::insert(const T& e)
{
    return insert(this->m_length, e);
}
template <typename T>
bool DualCircleLinkList<T>::insert(int index, const T& e)
{
    index = (this->m_length == 0 ? 0 : index % (this->m_length + 1));
    bool ret = ((0 <= index) && (index <= this->m_length));

    if(ret)
    {
        Node* newNode = new Node();
        if(newNode != NULL)
        {
            // 首节点
            list_head* pos = position(index);

            newNode->value = e;
            if(pos)
            {
                list_add_tail(&newNode->head, pos);
            }
            else
            {
                INIT_LIST_HEAD(&newNode->head);
                m_header.next = &newNode->head;
            }
            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create Node Object...");
        }
    }

    return ret;
}
template <typename T>
bool DualCircleLinkList<T>::remove(int index)
{
    index = (this->m_length == 0 ? 0 : index % this->m_length);
    bool ret = ((0 <= index) && (index < this->m_length));

    if(ret)
    {
        list_head* toDelNode = position(index);

        if(toDelNode != toDelNode->next)
        {
            if(toDelNode == m_current)
            {
                m_current = m_current->next;
            }
        }
        else
        {
            m_header.next = NULL;
            m_current = NULL;
        }

        if(index == 0)
        {
            if(1 < this->m_length)
            {
                m_header.next = toDelNode->next;
            }
        }
        list_del(toDelNode);
        this->m_length--;
    }

    return ret;
}
template <typename T>
bool DualCircleLinkList<T>::set(int index, const T& e)
{
    index = (this->m_length == 0 ? 0 : index % this->m_length);
    bool ret = ((0 <= index) && (index < this->m_length));

    if(ret)
    {
        list_entry(position(index), Node, head)->value = e;
    }

    return ret;
}
template <typename T>
bool DualCircleLinkList<T>::get(int index, T& e) const
{
    index = (this->m_length == 0 ? 0 : index % this->m_length);
    bool ret = ((0 <= index) && (index < this->m_length));

    if(ret)
    {
        e = list_entry(position(index), Node, head)->value;
    }

    return ret;
}
template <typename T>
int DualCircleLinkList<T>::length() const
{
    return this->m_length;
}
template <typename T>
int DualCircleLinkList<T>::find(const T& e) const
{
    int index = -1;
    list_head* headNode = &m_header;
    list_head* sliderNode = NULL;
    list_for_each(sliderNode, headNode)
    {
        if(index < this->m_length)
        {
            index++;
            if(list_entry(sliderNode, Node, head)->value == e)
            {
                break;
            }
        }
        else
        {
            index = -1;
            break;
        }
    }

    return index;
}

template <typename T>
bool DualCircleLinkList<T>::moveInit(int index, int step)
{
    index = (this->m_length == 0 ? 0 : index % this->m_length);
    bool ret = ((0 <= index) && (index < this->m_length) && (0 < step));

    if(ret)
    {
        m_current = position(index);
        this->m_step = step;
    }

    return ret;
}
template <typename T>
bool DualCircleLinkList<T>::end()
{
    return (m_current == NULL);
}
template <typename T>
T DualCircleLinkList<T>::currentValue()
{
    return list_entry(m_current, Node, head)->value;
}
template <typename T>
T DualCircleLinkList<T>::get(int index)
{
    index = (this->m_length == 0 ? 0 : index % this->m_length);
    T ret;

    if(get(index, ret))
    {
        return ret;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Paramter is invalid...");
    }
}
template <typename T>
bool DualCircleLinkList<T>::next()
{
    int n = 0;

    while((n < this->m_step) && !end())
    {
        m_current = m_current->next;
        n++;
    }
    return (this->m_step == n);
}
template <typename T>
bool DualCircleLinkList<T>::last()
{
    int n = 0;

    while((n < this->m_step) && !end())
    {
        m_current = m_current->prev;
        n++;
    }
    return (this->m_step == n);
}

template <typename T>
void DualCircleLinkList<T>::clear()
{
    while(this->m_length)
    {
        remove(this->m_length - 1);
    }
}

template <typename T>
DualCircleLinkList<T>::~DualCircleLinkList()
{
    clear();
}

}

#endif // DUALCIRCLELINKLIST_H
