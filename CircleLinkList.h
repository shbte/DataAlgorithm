#ifndef CIRCLELINKLIST_H
#define CIRCLELINKLIST_H

#include "LinkList.h"

/*
循环链表的实现思路
    通过模板定义CircleList类, 继承自LinkList类
    定义内部函数last_to_first(), 用于将单链表首尾相连
    特殊处理: 首元素的插入操作和删除
    重新实现: 清空操作和遍历操作

循环链表的实现要点
    插入位置为0时:
        头节点和尾节点均指向新节点
        新节点成为首节点插入链表
    删除位置为0时:
        头节点和尾结点指向位置为1的节点
        安全销毁首节点
 */
namespace DemoData
{

template <typename T>
class CircleLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    // 将单链表首尾相连
    void last_to_first();

    int mod(int i, int divisor) const;

public:
    CircleLinkList();

    bool insert(const T& e);
    bool insert(int index, const T& e);
    bool remove(int index);
    void clear();
    bool set(int index, const T& e);
    bool get(int index, T& e) const;
    T get(int index) const;

    int length() const;
    int find(const T&) const;

    bool moveInit(int, int = 1);
    bool end();
    T currentValue();
    bool next();

    ~CircleLinkList();
};

// 将单链表首尾相连
template <typename T>
void CircleLinkList<T>::last_to_first()
{
    if(this->m_length > 0)
    {
        // 首节点(index==0)
        Node* beginNode = LinkList<T>::position(0);
        // 尾节点(index==length-1)
        Node* endNode = LinkList<T>::position(this->m_length - 1);
        // 将首节点作为尾节点的后续节点
        endNode->next = beginNode;
    }
}

// 构造函数
template <typename T>
CircleLinkList<T>::CircleLinkList() : LinkList<T>() {}

template <typename T>
int CircleLinkList<T>::mod(int index, int divisor) const
{
    // 获取实际元素下标位置, 防止输入位置大于长度
    int ret = ((this->m_length) < 1 ? 0 : (index % divisor)); // 0不作为被除数, 因此使用三目运算符判断合法性
    return ret;
}

template <typename T>
bool CircleLinkList<T>::insert(const T& e)
{
    return insert(this->m_length, e);
}
template <typename T>
bool CircleLinkList<T>::insert(int index, const T& e)
{
    bool ret = false;

    // 获取合法的元素下标位置
    index = mod(index, this->m_length + 1);

    // 判断插入的新节点是否为首节点
    if(index == 0)
    {
        // 头信息节点
        Node* headNode = reinterpret_cast<Node*>(&this->m_header);
        // 尾节点(链表元素为0时, 获取的是头信息节点)
        Node* endNode = LinkList<T>::position(this->m_length - 1);

        Node* newNode = LinkList<T>::create();
        newNode->value = e;

        // 判断新节点插入前是否有元素节点
        if(headNode->next)
        {
            newNode->next = headNode->next;
        }
        else
        {
            newNode->next = newNode;
        }

        headNode->next = newNode;
        endNode->next = newNode;
    }
    else
    {
        // 新节点的前置节点
        Node* lastNode = LinkList<T>::position(index - 1);

        Node* newNode = LinkList<T>::create();
        newNode->value = e;
        newNode->next = lastNode->next;

        lastNode->next = newNode;
    }

    this->m_length++;
    ret = true;

    return ret;
}

template <typename T>
bool CircleLinkList<T>::remove(int index)
{
    bool ret = (0 < this->m_length);

    if(ret)
    {
        // 获取合法的元素下标位置
        index = mod(index, this->m_length);

        Node* toDelNode;

        // 判断删除的节点是否为首节点
        if(index == 0)
        {
            // 头信息节点
            Node* headNode = reinterpret_cast<Node*>(&this->m_header);
            // 尾节点
            Node* endNode = LinkList<T>::position(this->m_length - 1);

            toDelNode = LinkList<T>::position(index);
            headNode->next = toDelNode->next;
            endNode->next = toDelNode->next;
        }
        else
        {
            // 前置节点
            Node* lastNode = LinkList<T>::position(index - 1);

            toDelNode = lastNode->next;
            lastNode->next = toDelNode->next;
        }

        // 当前节点为被删节点时, 当前节点后移
        if(this->m_current == toDelNode)
        {
            this->m_current = toDelNode->next;
        }

        LinkList<T>::destroy(toDelNode);
        this->m_length--;

        // 循环链表元素为0时, 重置类成员值
        if(this->m_length == 0)
        {
            this->m_header.next = NULL;
            this->m_current = NULL;
        }
    }

    return ret;
}
template <typename T>
void CircleLinkList<T>::clear()
{
    while(this->m_length)
    {
        // 从尾节点开始删, 可以防止头信息节点的后续节点频繁变更
        remove(this->m_length - 1);
    }
}

template <typename T>
bool CircleLinkList<T>::set(int index, const T& e)
{
    bool ret = (0 < this->m_length);

    if(ret)
    {
        index = mod(index, this->m_length);

        Node* currentNode = LinkList<T>::position(index);
        currentNode->value = e;
    }

    return ret;
}

template <typename T>
bool CircleLinkList<T>::get(int index, T& e) const
{
    bool ret = (0 < this->m_length);

    if(ret)
    {
        index = mod(index, this->m_length);

        Node* currentNode = LinkList<T>::position(index);
        e = currentNode->value;
    }

    return ret;
}

template <typename T>
T CircleLinkList<T>::get(int index) const
{
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
int CircleLinkList<T>::length() const
{
    return this->m_length;
}

template <typename T>
int CircleLinkList<T>::find(const T& e) const
{
    // return LinkList<T>::find(e); // 循环链表不适用LinkList的find函数

    int ret = -1;

    for(int i = 0; i < this->m_length; i++)
    {
        Node* currentNode = LinkList<T>::position(i);

        if(currentNode->value == e)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

template <typename T>
bool CircleLinkList<T>::moveInit(int index, int step)
{
    return LinkList<T>::moveInit(index, step);
}

template <typename T>
bool CircleLinkList<T>::end()
{
    return LinkList<T>::end();
}

template <typename T>
T CircleLinkList<T>::currentValue()
{
    return LinkList<T>::currentValue();
}

template <typename T>
bool CircleLinkList<T>::next()
{
    return LinkList<T>::next();
}

template <typename T>
CircleLinkList<T>::~CircleLinkList()
{
    clear();
}

}

#endif // CIRCLELINKLIST_H
