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
};

}

#endif // GTREENODE_H
