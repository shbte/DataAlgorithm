#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DemoData
{

template <typename T>
class TreeNode : public Object
{
public:
    T value;
    TreeNode<T>* parent;

    TreeNode()
    {
        parent = NULL;
    }

    virtual ~TreeNode()
    {
        delete parent;
    };
};

}

#endif // TREENODE_H
