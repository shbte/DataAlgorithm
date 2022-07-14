#ifndef GTREENODE_H
#define GTREENODE_H

#include "LinkList.h"
#include "TreeNode.h"

namespace DemoData
{

template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    // 将指向子类的指针保存进链表, 可以实现一个节点多个子类(不用数组是因为数组大小更改麻烦)
    LinkList<GTreeNode<T>*> child;

    // 提供静态构造函数(工厂模式)
    static GTreeNode<T>* NewNode()
    {
        // new函数被重载且被父类定义为保护类型, 所以外部不能使用new在堆上创建该节点对象
        GTreeNode<T>* ret = new GTreeNode<T>();

        if(ret)
        {
            // 将该节点标记为true, 表明节点空间在堆上(new在堆上开辟内存空间)
            ret->m_flag = true;
        }

        return ret;
    }
};

}

#endif // GTREENODE_H
