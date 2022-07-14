#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "LinkQueue.h"

namespace DemoData
{

template <typename T>
class BTree : public Tree<T>
{
protected:

    // 按层次入队存储的树节点队列
    LinkQueue<BTreeNode<T>*> m_queue;

    /* 禁止树之间的相互赋值 */
    BTree<T>(const BTree<T>&);
    BTree<T>& operator =(const BTree&);

    // 递归查找函数
    BTreeNode<T>* find(BTreeNode<T>* node, const T& value) const;
    BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const;

    // 删除函数 => 清理节点关联信息
    void remove(BTreeNode<T>* node, BTree<T>*& ret);

    // 递归清除节点函数
    void free(BTreeNode<T>* node);

    // 树属性递归函数
    int degree(BTreeNode<T>* node) const;
    int count(BTreeNode<T>* node) const;
    int height(BTreeNode<T>* node) const;

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
    SharedPointer<Tree<T>> remove(const T& value);
    SharedPointer<Tree<T>> remove(TreeNode<T>* node);

    // 查找函数
    BTreeNode<T>* find(const T& value) const;
    BTreeNode<T>* find(TreeNode<T>* node) const;

    // 树属性函数
    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
    }
    int degree() const;
    int count() const;
    int height() const;

    /* 遍历功能函数 */
    bool begin();
    bool next();
    BTreeNode<T>* current();    // 返回值类型可用子类类型代替
    bool end();

    void clear();

    ~BTree<T>();
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
    BTreeNode<T>* node = BTreeNode<T>::NewNode();

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
    BTreeNode<T>* node = BTreeNode<T>::NewNode();

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

// 删除函数 => 清理节点关联信息
template <typename T>
void BTree<T>::remove(BTreeNode<T>* node, BTree<T>*& ret)
{
    // 获取删除节点的父节点
    BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

    // 创建树对象堆空间
    ret = new BTree<T>();

    // 判读父节点是否为空(父节点为空时, 删除节点为根节点)
    if(parent != NULL)
    {
        // 删除节点为父节点的左节点时, 左节点信息赋空
        if(parent->m_left == node)
        {
            parent->m_left = NULL;
        }
        // 删除节点为父节点的右节点时, 右节点信息赋空
        else if(parent->m_right == node)
        {
            parent->m_right = NULL;
        }
        // 正常情况不会出现父节点没有子节点信息, 应报异常
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Paramter node is invalid...");
        }

        // 删除节点的父节点信息更新(赋空)
        node->parent = NULL;
    }
    else
    {
        // 删除节点为根节点时, 赋空
        this->m_root = NULL;

        // 不要使用清空函数, 该函数会释放树对象指向的树节点, 树节点对象在这里不需要释放
        //clear();
    }

    ret->m_root = node;
}
// 删除函数
template <typename T>
SharedPointer<Tree<T>> BTree<T>::remove(const T& value)
{
    BTree<T>* ret = NULL;

    // 在树中查找节点
    BTreeNode<T>* node = find(value);

    // 判断该节点是否是树节点
    if(node != NULL)
    {
        // 删除以该节点为根的子树
        remove(node, ret);

        // 树节点被删除时, 清空队列
        m_queue.clear();
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parmeter value is invalid...");
    }

    return ret;
}
template <typename T>
SharedPointer<Tree<T>> BTree<T>::remove(TreeNode<T>* node)
{
    BTree<T>* ret = NULL;

    // 在树中查找节点
    BTreeNode<T>* n = find(node);

    // 判断该节点是否是树节点
    if(n != NULL)
    {
        // 删除以该节点为根的子树
        remove(n, ret);

        // 树节点被删除时, 清空队列
        m_queue.clear();
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parmeter node is invalid...");
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

/* 树属性函数 */
// 树的最大度数
template <typename T>
int BTree<T>::degree(BTreeNode<T>* node) const
{
    int ret = 0;

    // 判断节点是否为空
    if(node != NULL)
    {
        // !值只能是0或1, 使用俩个!!来判断是否有值, 从而计算该节点度数
        ret = !!node->m_left + !!node->m_right;

        // 获取子节点集合, 为遍历循环做准备
        BTreeNode<T>* child[] = { node->m_left, node->m_right };

        // 获取子节点的最大度数, 因为是二叉树(度数<=2), 所以当获取度数为2时, 循环结束
        for(int i = 0; (i < 2) && (ret < 2); i++)
        {
            // 子节点的度数
            int h = degree(child[i]);

            // 更新最大度数
            if(h > ret)
            {
                ret = h;
            }
        }
    }

    return ret;
}
template <typename T>
int BTree<T>::degree() const
{
    return degree(root());
}
// 树的节点数
template <typename T>
int BTree<T>::count(BTreeNode<T>* node) const
{
    // 左子节点数 + 右子节点数 + 1(自节点数)
    return (node != NULL) ? (count(node->m_left) + count(node->m_right) + 1) : 0;
}
template <typename T>
int BTree<T>::count() const
{
    return count(root());
}
// 树的最大高度
template <typename T>
int BTree<T>::height(BTreeNode<T>* node) const
{
    int ret = 0;

    // 判断节点是否为空
    if(node != NULL)
    {
        // 不为空时, 树高度加1
        ret += 1;

        // 左子节点高度
        int lh = height(node->m_left);
        // 右子节点高度
        int rh = height(node->m_right);

        // 自节点高度 + 最大子节点高度
        ret += ((lh > rh) ? lh : rh);
    }

    return ret;
}
template <typename T>
int BTree<T>::height() const
{
    return height(root());
}

/* 遍历功能函数 */
template <typename T>
bool BTree<T>::begin()
{
    bool ret = false;

    // 判断树是否为空
    if(root() != NULL)
    {
        // 清空队列
        m_queue.clear();
        // 将根节点加入队列
        m_queue.add(root());

        // 表明将根节点加入队列成功
        ret = true;
    }

    return ret;
}
template <typename T>
bool BTree<T>::next()
{
    bool ret = end();

    // 判断队列是否为空
    if(!ret)
    {
        // 获取队头元素
        BTreeNode<T>* node = m_queue.front();

        // 将队头元素的左子节点加入队列
        if(node->m_left != NULL)
        {
            m_queue.add(node->m_left);
        }

        // 将队头元素的右子节点加入队列
        if(node->m_right != NULL)
        {
            m_queue.add(node->m_right);
        }

        // 将队头元素弹出队列
        m_queue.remove();
    }

    return ret;
}
template <typename T>
BTreeNode<T>* BTree<T>::current()
{
    BTreeNode<T>* ret = NULL;

    // 判断队列是否为空
    if(!end())
    {
        // 获取队头元素
        ret = m_queue.front();
    }

    return ret;
}
template <typename T>
bool BTree<T>::end()
{
    // 返回队列为否为空的判断
    return (m_queue.size() == 0);
}

// 递归清除节点函数
template <typename T>
void BTree<T>::free(BTreeNode<T>* node)
{
    if(node != NULL)
    {
        // 清除左节点
        free(node->m_left);
        // 清除右节点
        free(node->m_right);

        // 获取清楚节点的父节点
        BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);

        // 判断父节点是否为空, 不为空时, 清理父节点中关于清除节点的信息
        if(parent != NULL)
        {
            // 删除节点为父节点的左节点时, 左节点信息赋空
            if(parent->m_left == node)
            {
                parent->m_left = NULL;
            }
            // 删除节点为父节点的右节点时, 右节点信息赋空
            else if(parent->m_right == node)
            {
                parent->m_right = NULL;
            }
            // 正常情况不会出现父节点没有子节点信息, 应报异常
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "Paramter node is invalid...");
            }
        }

        // 释放清除节点的内存堆空间
        if(node->flag())
        {
            delete node;
        }
    }
}
// 清除所有树节点
template <typename T>
void BTree<T>::clear()
{
    // 释放树节点所使用的内存堆空间
    free(root());

    // 树根节点赋空, 防止由于其为栈空间而没释放问题
    this->m_root = NULL;

    // 清空队列
    m_queue.clear();
}

template <typename T>
BTree<T>::~BTree<T>()
{
    // 析构时清空树
    clear();
}

}

#endif // BTREE_H
