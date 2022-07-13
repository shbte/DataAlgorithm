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

    // 指定位置的节点插入函数
    bool insert(BTreeNode<T>* node, TreeNode<T>* parent, BTNodePos pos);
    bool insert(BTreeNode<T>* node, BTNodePos pos);
    bool insert(const T& value, TreeNode<T>* parent, BTNodePos pos);
    // 插入函数
    bool insert(TreeNode<T>* node);
    bool insert(const T& value, TreeNode<T>* parent);

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
// 指定位置的节点插入函数
template <typename T>
bool BTree<T>::insert(BTreeNode<T>* node, TreeNode<T>* parent, BTNodePos pos)
{
    bool ret = false;
    BTreeNode<T>* np = dynamic_cast<BTreeNode<T>*>(parent);

    // 指定插入位置为任意
    if(pos == ANY)
    {
        // 父节点的左节点为空时, 新节点插入
        if(np->m_left == NULL)
        {
            // 在左节点位置插入新节点(节点信息更新)
            np->m_left = node;

            // 表明插入成功
            ret = true;
        }
        // 父节点的右节点为空时, 新节点插入
        else if(np->m_right == NULL)
        {
            // 在右节点位置插入新节点(节点信息更新)
            np->m_right = node;

            // 表明插入成功
            ret = true;
        }
        else
        {
            // 表明父节点的左右节点都不为空, 新节点插入失败
            ret = false;
        }
    }
    // 指定插入位置为左节点
    else if(pos == LEFT)
    {
        // 父节点的左节点为空时, 新节点插入
        if(np->m_left == NULL)
        {
            // 在左节点位置插入新节点(节点信息更新)
            np->m_left = node;

            // 表明插入成功
            ret = true;
        }
        else
        {
            // 表明父节点的左节点不为空, 新节点插入失败
            ret = false;
        }
    }
    // 指定插入位置为右节点
    else if(pos == RIGHT)
    {
        // 父节点的右节点为空时, 新节点插入
        if(np->m_right == NULL)
        {
            // 在右节点位置插入新节点(节点信息更新)
            np->m_right = node;

            // 表明插入成功
            ret = true;
        }
        else
        {
            // 表明父节点的右节点不为空, 新节点插入失败
            ret = false;
        }
    }
    // 指定的插入位置参数错误
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter pos is invalid...");
    }

    return ret;
}
template <typename T>
bool BTree<T>::insert(BTreeNode<T>* node, BTNodePos pos)
{
    bool ret = false;

    // 判断插入节点为否为空
    if(node != NULL)
    {
        // 获取插入节点的父节点
        TreeNode<T>* parent = node->parent;

        // 父节点为空时, 新节点作为树的根节点
        if(parent == NULL)
        {
            this->m_root = node;
        }
        else
        {
            // 在树中插入新节点
            ret = insert(node, parent, pos);
        }
    }

    return ret;
}
template <typename T>
bool BTree<T>::insert(const T& value, TreeNode<T>* parent, BTNodePos pos)
{
    bool ret = false;

    // 创建树节点对象
    BTreeNode<T>* node = BTreeNode<T>::newNode();

    // 判断节点对象创建是否成功
    if(node != NULL)
    {
        // 节点信息赋值
        node->value = value;
        node->parent = parent;

        // 将新节点插入树中
        ret = insert(node, parent, pos);

        // 新节点对象插入失败时, 释放节点对象的堆内存空间
        if(!ret && node->flag())
        {
            delete node;
        }
    }

    return ret;
}
// 插入函数 => 该节点的parent已经指定
template <typename T>
bool BTree<T>::insert(TreeNode<T>* node)
{
    return insert(dynamic_cast<BTreeNode<T>*>(node), ANY);
}
template <typename T>
bool BTree<T>::insert(const T& value, TreeNode<T>* obj)
{
    bool ret = false;

    // 创建树节点对象
    BTreeNode<T>* node = BTreeNode<T>::newNode();

    // 判断节点对象创建是否成功
    if(node != NULL)
    {
        // 节点信息赋值
        node->value = value;
        node->parent = obj;

        // 将新节点插入树中
        ret = insert(node, ANY);

        // 新节点对象插入失败时, 释放节点对象的堆内存空间
        if(!ret && node->flag())
        {
            delete node;
        }
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new BTreeNode...");
    }

    return ret;
}

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
