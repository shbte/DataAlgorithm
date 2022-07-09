#ifndef GTREENODE_H
#define GTREENODE_H

#include "LinkList.h"
#include "TreeNode.h"

namespace DemoData
{

template <typename T>
class GTreeNode : public TreeNode<T>
{
protected:
    bool m_flag;

    void* operator new(size_t size)
    {
        return Object::operator new(size);
    }

public:
    // 将指向子类的指针保存进链表, 可以实现一个节点多个子类(不用数组是因为数组大小更改麻烦)
    LinkList<GTreeNode<T>*> child;

    GTreeNode()
    {
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret != NULL)
        {
            ret->m_flag = true;
        }

        return ret;
    }
};

}

#endif // GTREENODE_H
