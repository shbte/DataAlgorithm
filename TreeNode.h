#ifndef TREENODE_H
#define TREENODE_H

#include "Object.h"

namespace DemoData
{

template <typename T>
class TreeNode : public Object
{
protected:
    bool m_flag;

    // 重载new操作符, 防止外部使用new构建对象, 让外部只能使用newNode函数
    static void* operator new(size_t size)
    {
        return (Object::operator new(size));
    }

    /* 私有化拷贝构造函数、赋值操作符, 防止树节点间的赋值 */
    TreeNode<T>(const TreeNode<T>&);
    TreeNode<T>& operator =(const TreeNode<T>&);

public:
    T value;
    // 指向父节点, 方便以链表方式从尾到头输出树节点
    TreeNode<T>* parent;

    TreeNode()
    {
        m_flag = false;
        parent = NULL;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode()
    {
        parent = NULL;
    };

};

}

#endif // TREENODE_H
