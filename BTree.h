#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"

namespace DemoData
{

template <typename T>
class BTree : public Tree<T>
{
protected:
    /* 禁止树之间的相互赋值 */
    BTree<T>(const BTree<T>&);
    BTree<T>& operator =(const BTree&);

    // 递归查找函数
    BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const;
    BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const;

public:
    BTree<T>() {}

    // 插入函数
    bool insert(TreeNode<T>* node)
    {
        bool ret = false;

        return ret;
    }
    bool insert(const T& value, TreeNode<T>* parent)
    {
        bool ret = false;

        return ret;
    }

    // 删除函数
    SharedPointer<Tree<T>> remove(const T& value)
    {
        BTree<T>* ret = NULL;

        return ret;
    }
    SharedPointer<Tree<T>> remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;

        return ret;
    }

    // 查找函数
    BTreeNode<T>* find(const T& value) const;
    BTreeNode<T>* find(TreeNode<T>* node) const;

    // 节点属性函数
    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }
    int degree() const
    {

    }
    int count() const
    {

    }
    int height() const
    {

    }

    /* 遍历功能函数 */
    bool begin()
    {
        bool ret = false;

        return ret;
    }
    bool next()
    {
        bool ret = !end();

        return ret;
    }
    TreeNode<T>* current()
    {
        BTreeNode<T>* ret = NULL;

        return ret;
    }
    bool end()
    {
        bool ret = false;

        return ret;
    }

    void clear()
    {

    }
};

// 递归查找函数
template <typename T>
BTreeNode<T>* BTree<T>::find(BTreeNode<T>* node, const T& value) const
{
    BTreeNode<T>* ret = NULL;

    // 判断参数是否合法
    if((node != NULL) && (value))
    {
        // 先判断是否是查找节点值
        if(node->value == value)
        {
            ret = node;
        }
        else
        {
            // 递归查找左节点(子节点)值是否相同
            if(node->m_left != NULL)
            {
                ret = find(node->m_left, value);
            }

            // 左节点查找不到时, 再去右节点(兄弟节点)查找节点值是否相同
            if((ret == NULL) && (node->m_right != NULL))
            {
                ret = find(node->m_right, value);
            }
        }
    }

    return ret;
}
template <typename T>
BTreeNode<T>* BTree<T>::find(BTreeNode<T>* node, BTreeNode<T>* obj) const
{
    BTreeNode<T>* ret = NULL;

    // 判断参数是否合法
    if((node != NULL) && (obj != NULL))
    {
        // 先判断是否是查找节点
        if(node == obj)
        {
            ret = node;
        }
        else
        {
            // 递归查找左节点(子节点)是否相同
            if(node->m_left != NULL)
            {
                ret = find(node->m_left, obj);
            }

            // 左节点查找不到时, 再去右节点(兄弟节点)查找
            if((ret == NULL) && (node->m_right != NULL))
            {
                ret = find(node->m_right, obj);
            }
        }
    }

    return ret;
}
// 查找函数
template <typename T>
BTreeNode<T>* BTree<T>::find(const T& value) const
{
    return find(root(), value);
}
template <typename T>
BTreeNode<T>* BTree<T>::find(TreeNode<T>* node) const
{
    return find(root(), dynamic_cast<BTreeNode<T>*>(node));
}

}

#endif // BTREE_H
