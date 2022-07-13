#ifndef BTREENODE_H
#define BTREENODE_H

#include "TreeNode.h"

namespace DemoData
{

// 记录节点位置
enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template <typename T>
class BTreeNode : public TreeNode<T>
{
public:
    // 指向子节点
    BTreeNode<T>* m_left;
    // 指向兄弟节点
    BTreeNode<T>* m_right;

    BTreeNode<T>()
    {
        m_left = NULL;
        m_right = NULL;
    }

    // 提供静态构造函数(工厂模式)
    static BTreeNode<T>* newNode()
    {
        // new函数被重载且被父类定义为保护类型, 所以外部不能使用new在堆上创建该节点对象
        BTreeNode<T>* ret = new BTreeNode<T>();

        if(ret)
        {
            // 将该节点标记为true, 表明节点空间在堆上(new在堆上开辟内存空间)
            ret->m_flag = true;
        }

        return ret;
    }
};

}

#endif // BTREENODE_H
