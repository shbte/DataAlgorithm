#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DemoData
{

/*
静态单链表的实现思路
    通过模板定义静态单链表(StaticLinkList)
    在类中定义固定大小的空间(unsigned char[]), 用于存储链表节点数据
    重写create和destroy函数, 改变内存的分配和归还方式
    在Node类中重载operator new, 用于在指定内存上创建对象
 */
template <typename T, int N>
class StaticLinkList : public LinkList<T>
{
protected:
    // typedef: 重命名, typename: 明确告诉编译器其后的标识符为类型(还可以, 在模板定义中声明泛指类型)
    typedef typename LinkList<T>::Node Node;

    struct SNode : public Node
    {
        // 这里本可以使用系统提供的new操作符函数, 但是顶层父类Object重载了new操作符函数, 因此, 系统将不会提供默认的new操作符函数, 需要自己手动重载实现
        void* operator new(size_t size, void* loc)
        {
            (void)size;
            return loc;
        }
    };

    // 预留节点空间
    unsigned char m_space[sizeof(SNode) * N];
    // 标记数组, 标记节点空间是否可用, 可用(0), 不可用(1)
    int m_use[N];

    // 在指定内存空间创建对象, 使用智能指针(SharedPointer)代替Node*
    SharedPointer<Node> create()
    {
        SNode* ret = NULL;

        for(int i = 0; i < N; i++)
        {
            // 可用(0), 不可用(1)
            if(!m_use[i])
            {
                // 将指定的内存地址解释为SNode类型, 然后后移找到指定可用空间
                ret = reinterpret_cast<SNode*>(m_space) + i;
                // 在指定内存空间创建对象
                ret = new(ret) SNode();

                // 标记为不可用
                m_use[i] = 1;
                // 对象创建结束
                break;
            }
        }

        return ret;
    }

    /* 使用智能指针(SharedPointer)代替Node*, 会自动释放内存空间, 不用手动 */
    // 归还指定内存空间上的对象
    //    void destroy(Node* pn)
    //    {
    //        // 将内存解释为SNode类型
    //        SNode* space = reinterpret_cast<SNode*>(m_space);
    //        SNode* psn = reinterpret_cast<SNode*>(pn);

    //        for(int i = 0; i < N; i++)
    //        {
    //            if((space + i) == psn)
    //            {
    //                (space + i)->~SNode();
    //                m_use[i] = 0;

    //                // 不会出现两个相同对象(对象的相同默认是以地址比较的), 因此, 此处结束循环
    //                break;
    //            }
    //        }
    //    }

public:

    StaticLinkList()
    {
        for(int i = 0; i < N; i++)
        {
            m_use[i] = 0;
        }
    }

    int capacity()
    {
        return N;
    }

    ~StaticLinkList()
    {
        // 子类调用父类clear函数, 再调用自身类destroy释放自身类指定空间
        // 如果自身没调用父类clear函数, 则因为析构函数不会发生多态的特性而调用的是父类的destroy函数, 释放的是父类的堆空间
        // 子类释放指定空间后, 链表长度为0, 然后父类会先进行长度判断再去释放堆空间 (长度为0, 则不释放, 保证了destroy函数能正确释放空间)
        this->clear();
    }

};

}

#endif // STATICLINKLIST_H
