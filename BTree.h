#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace DemoData
{

enum BTTraversal
{
    PreOrder,   // 先序
    InOrder,    // 中序
    PostOrder   // 后续
};

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

    // 先序遍历, 使用引用参数, 防止新建队列对象
    void preOrderTraversal(BTreeNode<T>* node, LinkQueue<T>& queue);
    // 中序遍历, 使用引用参数, 防止新建队列对象
    void inOrderTraversal(BTreeNode<T>* node, LinkQueue<T>& queue);
    // 后序遍历, 使用引用参数, 防止新建队列对象
    void postOrderTraversal(BTreeNode<T>* node, LinkQueue<T>& queue);

    // 递归克隆函数
    BTreeNode<T>* clone(BTreeNode<T>* node) const;
    // 递归比较函数
    bool equal(BTreeNode<T>* ln, BTreeNode<T>* rn) const;
    // 递归相加函数
    BTreeNode<T>* add(BTreeNode<T>* ln, BTreeNode<T>* rn) const;

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

    // 顺序遍历函数
    SharedPointer<Array<T>> traversal(BTTraversal order);
    // 克隆函数(值相等)
    SharedPointer<BTree<T>> clone() const;
    // 相加函数(值相加)
    SharedPointer<BTree<T>> add(const BTree<T>& btree) const;

    // 比较操作符重载(值比较)
    bool operator ==(const BTree<T>& btree) const;
    bool operator !=(const BTree<T>& btree) const;

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
    if(node != NULL)
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

// 先序遍历
template <typename T>
void BTree<T>::preOrderTraversal(BTreeNode<T>* node, LinkQueue<T>& queue)
{
    if(node != NULL)
    {
        queue.add(node->value);
        preOrderTraversal(node->m_left, queue);
        preOrderTraversal(node->m_right, queue);
    }
}
// 中序遍历
template <typename T>
void BTree<T>::inOrderTraversal(BTreeNode<T>* node, LinkQueue<T>& queue)
{
    if(node != NULL)
    {
        inOrderTraversal(node->m_left, queue);
        queue.add(node->value);
        inOrderTraversal(node->m_right, queue);
    }
}
// 后序遍历
template <typename T>
void BTree<T>::postOrderTraversal(BTreeNode<T>* node, LinkQueue<T>& queue)
{
    if(node != NULL)
    {
        postOrderTraversal(node->m_left, queue);
        postOrderTraversal(node->m_right, queue);
        queue.add(node->value);
    }
}
// 顺序遍历函数
template <typename T>
SharedPointer<Array<T>> BTree<T>::traversal(BTTraversal order)
{
    // 存放树节点值数组
    DynamicArray<T>* ret = NULL;
    // 存放树节点值队列, 起过度作用
    LinkQueue<T> queue;

    // 判断排序方式, 并将树节点值存储进队列
    switch(order)
    {
        case PreOrder:
            preOrderTraversal(root(), queue);
            break;
        case InOrder:
            inOrderTraversal(root(), queue);
            break;
        case PostOrder:
            postOrderTraversal(root(), queue);
            break;
        default:
            THROW_EXCEPTION(InvalidParameterException, "parameter order is invalid...");
            break;
    }

    // 创建堆空间动态数组对象
    ret = new DynamicArray<T>(queue.size());

    // 判断数组对象是否创建成功
    if(ret != NULL)
    {
        // 循环将队列元素存储进数组
        for(int i = 0; i < ret->length(); i++)
        {
            // 将队头元素存储进数组
            ret->set(i, queue.front());
            // 移除队头元素
            queue.remove();
        }
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new DynamicArray...");
    }

    return ret;
}
// 递归克隆函数
template <typename T>
BTreeNode<T>* BTree<T>::clone(BTreeNode<T>* node) const
{
    BTreeNode<T>* ret = NULL;

    // 判断当前节点是否为空
    if(node != NULL)
    {
        // 创建内存堆空间节点对象
        ret = BTreeNode<T>::NewNode();

        // 节点创建成功时, 节点元素赋值
        if(ret != NULL)
        {
            // 节点自身信息赋值
            ret->parent = node->parent;
            ret->value = node->value;

            // 子节点信息赋值
            ret->m_left = clone(node->m_left);
            ret->m_right = clone(node->m_right);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No Enough memory to create new BtreeNode...");
        }
    }

    return ret;
}
// 克隆函数(节点值相等)
template <typename T>
SharedPointer<BTree<T>> BTree<T>::clone() const
{
    // 创建内存堆空间树对象
    BTree<T>* ret = new BTree<T>();

    // 树对象创建成功时, 赋值树根节点
    if(ret != NULL)
    {
        // 递归克隆树节点, 并返回根节点
        ret->m_root = clone(root());
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new BTree...");
    }

    return ret;
}

// 递归比较函数
template <typename T>
bool BTree<T>::equal(BTreeNode<T>* ln, BTreeNode<T>* rn) const
{
    bool ret = false;

    // 两个树节点都不为空时, 进一步比较节点值
    if(!!ln && !!rn)
    {
        // 节点地址值相等时, 值一定相等(value, left, right, parent), 可直接返回true
        if(ln == rn)
        {
            ret = true;
        }
        // 节点地址值不相等时, 比较节点值
        else
        {
            // 比较节点值 + 递归比较左节点 + 递归比较右节点
            ret = ((ln->value == rn->value) && equal(ln->m_left, rn->m_left) && equal(ln->m_right, rn->m_right));
        }
    }
    // 两个树节点都为空时, 返回true
    else if(!ln && !rn)
    {
        ret = true;
    }
    else
    {
        ret = false;
    }

    return ret;
}
// 比较操作符重载(值比较)
template <typename T>
bool BTree<T>::operator ==(const BTree<T>& btree) const
{
    bool ret = false;

    // 从根节点开始递归比较树的各个节点
    ret = equal(root(), btree.root());

    return ret;
}
template <typename T>
bool BTree<T>::operator !=(const BTree<T>& btree) const
{
    return !(*this == btree);
}

// 递归相加函数
template <typename T>
BTreeNode<T>* BTree<T>::add(BTreeNode<T>* ln, BTreeNode<T>* rn) const
{
    BTreeNode<T>* ret = NULL;

    // 左右节点都不为空, 左右节点值相加
    if(!!ln && !!rn)
    {
        // 创建内存堆空间节点对象
        ret = BTreeNode<T>::NewNode();

        // 判断节点是否为空, 不为空时, 新节点正常赋值
        if(ret != NULL)
        {
            // 新节点赋值(父节点尚不存在)
            ret->parent = NULL;
            ret->value = ln->value + rn->value;

            // 子节点信息赋值
            ret->m_left = add(ln->m_left, rn->m_left);
            ret->m_right = add(ln->m_right, rn->m_right);

            // 指定左节点的父节点
            if(ret->m_left != NULL)
            {
                ret->m_left->parent = ret;
            }
            // 指定右节点的父节点
            if(ret->m_right != NULL)
            {
                ret->m_right->parent = ret;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new BTreeNode...");
        }
    }
    // 左节点不为空, 右节点为空时, 克隆以左节点为根的子树
    else if(!!ln && !rn)
    {
        ret = clone(ln);
    }
    // 左节点为空, 右节点不为空, 克隆以右节点为根的子树
    else if(!ln && !!rn)
    {
        ret = clone(rn);
    }
    // 左右节点都为空, 返回空
    else if(!ln && !rn)
    {
        ret = NULL;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter BTreeNode is invalid...");
    }

    return ret;
}
// 相加函数(值相加)
template <typename T>
SharedPointer<BTree<T>> BTree<T>::add(const BTree<T>& btree) const
{
    BTree<T>* ret = new BTree<T>();

    if(ret != NULL)
    {
        // 从根节点开始递归相加树的各个节点
        ret->m_root = add(root(), btree.root());
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new BTree...");
    }

    return ret;
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
