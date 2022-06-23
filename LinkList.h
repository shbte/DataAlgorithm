#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Object.h"
#include "Exception.h"

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
        Node* next; // 指针区(指向下一节点: 后继节点)
    };

    // 定义的同时创建了Node对象, 而导致T类型具体构造了(如果T类型构造函数错误, LinkList将出错)
    // mutable Node m_header;  // 头信息节点

    mutable struct : public Object
    {
        char reserved[sizeof(T)]; // 只开辟T类型所使用的空间(不构造对象), 使用时再进行内存解释构造
        Node* next;
    } m_header;

    int m_length;       // 链表长度
    Node* m_current;    // 当前节点
    int m_step;         // 移动量级

    // 获取特定(index)位置节点
    Node* position(int index) const
    {
        // 从头信息节点开始往后遍历获取特定节点位置, 头信息节点不计入节点长度
        Node* current = reinterpret_cast<Node*>(&m_header); // 类型转换, 内存解释为Node*
        for(int i = 0; i <= index; i++)
        {
            current = current->next;
        }
        return current;
    }

    // 设置为虚函数, 实现多态特性(子类StaticLinkList需要动态调用自身的重载函数)
    virtual Node* create()
    {
        return new Node();
    }
    virtual void destroy(Node* pn)
    {
        delete pn;
    }

public:
    LinkList()
    {
        // m_header.value = NULL; // 头信息节点不存储数据, 只存储链表的第一个元素指针
        m_header.next = NULL;
        m_length = 0;
        m_current = NULL;
        m_step = 1;
    }

    // 增: 尾增
    bool insert(const T& e)
    {
        bool ret = insert(m_length, e);
        return ret;
    }
    // 增
    bool insert(int index, const T& e)
    {
        // 判断位置是否合法
        bool ret = ((0 <= index) && (index <= m_length));

        if(ret)
        {
            // 创建新节点的堆空间
            Node* newNode = create();
            if(newNode != NULL)
            {
                // 获取新节点的前置节点位置(-1)
                Node* last = position(index - 1);

                // 赋值新节点数据域
                newNode->value = e;
                // 赋值新节点指针域, 值为前置节点的后继节点
                newNode->next = last->next;
                // 更新前置节点的后继节点为新节点
                last->next = newNode;

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
    bool remove(int index)
    {
        // 判断位置是否合法
        bool ret = ((0 <= index) && (index < m_length));

        if(ret)
        {
            // 获取删除节点的前置节点位置(-1)
            Node* last = position(index - 1);

            // 获取删除节点位置
            Node* toDel = last->next;
            // 更新前置节点指针域, 值为删除节点的后继节点
            last->next = toDel->next;
            // 删除节点
            destroy(toDel);

            // 更新链表长度, 减1
            m_length--;
        }

        return ret;
    }
    // 删: 全删
    void clear()
    {
        while(m_header.next)
        {
            // 获取删除节点位置
            Node* toDel = m_header.next;
            // 头节点后移
            m_header.next = toDel->next;
            // 删除节点
            destroy(toDel);
        }

        // 更新链表长度
        m_length = 0;
    }

    // 改
    bool set(int index, const T& e)
    {
        // 判断位置是否合法
        bool ret = ((0 <= index) && (index < m_length));

        if(ret)
        {
            // 获取当前节点位置
            Node* current = position(index);
            current->value = e;
        }

        return ret;
    }

    // 查
    bool get(int index, T& e) const
    {
        // 判断位置是否合法
        bool ret = ((0 <= index) && (index < m_length));

        if(ret)
        {
            // 获取当前节点位置
            Node* current = position(index);
            e = current->value;
        }

        return ret;
    }
    // 查
    T get(int index) const
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
    int length() const
    {
        return m_length;
    }

    // 查找函数, >=0说明存在, =-1说明不存在
    int find(const T& e) const
    {
        int ret = -1;

        int i = 0;
        Node* node = m_header.next;

        while(node)
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
    bool moveInit(int index, int step = 1)
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
    bool end()
    {
        return (m_current == NULL);
    }

    // 获取当前节点的数据
    T currentValue()
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
    bool next()
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

};

}

#endif // LINKLIST_H
