/* 备份 */
/* 使用智能指针(SharedPointer<Node>)替换链表类(LinkList)中的原生指针(Node*) */
#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"
#include "SharedPointer.h"

namespace DemoData
{

/*
LinkList设计要点
    类模板, 通过头节点访问后继节点
    定义内部节点类型Node, 用于描述数据域和指针域
    实现线性表的关键操作(增 删 改 查等)
 */
template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object // struct当作class, 也可以继承其它类
    {
        T value;    // 数据区
        SharedPointer<Node> next; // 指针区(指向下一节点: 后继节点)
    };

    // 定义的同时创建了Node对象, 而导致T类型具体构造了(如果T类型构造函数错误, LinkList将出错)
    // mutable Node m_header;  // 头信息节点

    mutable struct : public Object
    {
        char reserved[sizeof(T)]; // 只开辟T类型所使用的空间(不构造对象), 使用时再进行内存解释构造
        SharedPointer<Node> next;
    } m_header;

    int m_length;       // 链表长度
    SharedPointer<Node> m_current;    // 当前节点
    int m_step;         // 移动量级

    // 定义前置节点为类成员变量, 防止临时变量使用头信息节点后释放头信息节点
    SharedPointer<Node> lastNode;

    // 获取特定(index)位置节点
    SharedPointer<Node> position(int index) const
    {
        // 从头信息节点开始往后遍历获取特定节点位置, 头信息节点不计入节点长度
        SharedPointer<Node> current = reinterpret_cast<Node*>(&m_header);  // 类型转换, 内存解释为Node*
        for(int i = 0; i <= index; i++)
        {
            current = current->next;
        }
        return current;
    }

    // 设置为虚函数, 实现多态特性(子类StaticLinkList需要动态调用自身的重载函数)
    virtual SharedPointer<Node> create()
    {
        return new Node();
    }
    /* 使用智能指针(SharedPointer<Node>)代替Node*, 会自动释放内存空间, 不用手动释放 */
    //     virtual void destroy(SharedPointer<Node> pn)
    //     {
    //     delete pn;
    //     }

public:
    LinkList();

    bool insert(const T& e);
    bool insert(int index, const T& e);
    bool remove(int index);
    void clear();
    bool set(int index, const T& e);
    bool get(int index, T& e) const;
    T get(int index) const;

    // 获取链表长度
    int length() const;
    // 查找函数, >=0说明存在, =-1说明不存在
    int find(const T& e) const;

    /* 遍历函数重设计: 意义在于把遍历输出函数的时间复杂度变小( O(n^2) ==> O(n) ) */

    // 设置当前节点, 并设置移动量级
    bool moveInit(int index, int step = 1);
    // 判断当前节点是否为空, 为空说明链表结束
    bool end();
    // 获取当前节点的数据
    T currentValue();
    // 移动一个量级当前节点
    bool next();

    ~LinkList();
};

// 构造函数
template <typename T>
LinkList<T>::LinkList()
{
    // m_header.value = NULL; // 头信息节点不存储数据, 只存储链表的第一个元素指针
    m_header.next = NULL;
    m_length = 0;
    m_current = NULL;
    m_step = 1;
}

// 增: 尾增
template <typename T>
bool LinkList<T>::insert(const T& e)
{
    bool ret = insert(m_length, e);
    return ret;
}
// 增
template <typename T>
bool LinkList<T>::insert(int index, const T& e)
{
    // 判断位置是否合法
    bool ret = ((0 <= index) && (index <= m_length));

    if(ret)
    {
        // 创建新节点的堆空间
        SharedPointer<Node> newNode = create();
        if(newNode != NULL)
        {
            // 获取新节点的前置节点位置(-1)
            lastNode = position(index - 1);

            // 赋值新节点数据域
            newNode->value = e;
            // 赋值新节点指针域, 值为前置节点的后继节点
            newNode->next = lastNode->next;
            // 更新前置节点的后继节点为新节点
            lastNode->next = newNode;

            // 更新链表长度, 加1
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new Node...");
        }
    }

    return ret;
}

// 删
template <typename T>
bool LinkList<T>::remove(int index)
{
    // 判断位置是否合法
    bool ret = ((0 <= index) && (index < m_length));

    if(ret)
    {
        // 获取删除节点的前置节点位置(-1)
        lastNode = position(index - 1);

        // 获取删除节点位置
        SharedPointer<Node> toDel = lastNode->next;
        // 更新前置节点指针域, 值为删除节点的后继节点
        lastNode->next = toDel->next;

        // 如果当前游标位置被删除, 游标后移
        if(m_current == toDel)
        {
            m_current = m_current->next;
        }

        // 删除节点
        // destroy(toDel); // SharedPointer<Node>析构时自动释放内存空间

        // 更新链表长度, 减1
        m_length--;
    }

    return ret;
}
// 删: 全删
template <typename T>
void LinkList<T>::clear()
{
    while(m_header.next.get())
    {
        // 获取删除节点位置
        SharedPointer<Node> toDel = m_header.next;
        // 头节点后移
        m_header.next = toDel->next;
        // 删除节点
        // destroy(toDel); // SharedPointer<Node>析构时自动释放内存空间

        // 更新链表长度, 减1
        m_length--;
    }
}

// 改
template <typename T>
bool LinkList<T>::set(int index, const T& e)
{
    // 判断位置是否合法
    bool ret = ((0 <= index) && (index < m_length));

    if(ret)
    {
        // 获取当前节点位置
        SharedPointer<Node> current = position(index);
        current->value = e;
    }

    return ret;
}

// 查
template <typename T>
bool LinkList<T>::get(int index, T& e) const
{
    // 判断位置是否合法
    bool ret = ((0 <= index) && (index < m_length));

    if(ret)
    {
        // 获取当前节点位置
        SharedPointer<Node> current = position(index);
        e = current->value;
    }

    return ret;
}
// 查
template <typename T>
T LinkList<T>::get(int index) const
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

// 获取链表长度
template <typename T>
int LinkList<T>::length() const
{
    return m_length;
}

// 查找函数, >=0说明存在, =-1说明不存在
template <typename T>
int LinkList<T>::find(const T& e) const
{
    int ret = -1;

    int i = 0;
    SharedPointer<Node> node = m_header.next;

    while(node.get())
    {
        if(node->value == e)
        {
            ret = i;
            break;
        }
        else
        {
            node = node->next;
            i++;
        }
    }

    return ret;
}

/* 遍历函数重设计: 意义在于把遍历输出函数的时间复杂度变小( O(n^2) ==> O(n) ) */
// 设置当前节点, 并设置移动量级
template <typename T>
bool LinkList<T>::moveInit(int index, int step)
{
    // 判断参数是否合法
    bool ret = ((0 <= index) && (index < m_length) && (0 < step));

    if(ret)
    {
        // 设置当前节点
        m_current = position(index);
        // 设置移动量级
        m_step = step;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "parameter is invalid...");
    }

    return ret;
}

// 判断当前节点是否为空, 为空说明链表结束
template <typename T>
bool LinkList<T>::end()
{
    return (m_current == NULL);
}

// 获取当前节点的数据
template <typename T>
T LinkList<T>::currentValue()
{
    if(!end())
    {
        return m_current->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No value at current position...");
    }
}

// 移动一个量级当前节点
template <typename T>
bool LinkList<T>::next()
{
    int i = 0;

    // 移动一个量级, 并判断是否移动结束
    while((i < m_step) && !end())
    {
        m_current = m_current->next;
        i++;
    }

    // 移动次数等于移动量级时, 移动成功
    return (i == m_step);
}

template <typename T>
LinkList<T>::~LinkList()
{
    // 构造函数和析构函数中, 不会发生多态, 因此, 此处调用的是自身类函数
    // 危险: clear中调用了destroy函数, 由于不会发生多态, 所以该自身类destroy函数释放的是自身堆空间
    //      预期应该是调用子类destroy释放子类指定空间
    clear();
}

}

#endif // LINKLIST_H
