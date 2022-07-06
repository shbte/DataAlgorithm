#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"

namespace DemoData
{

template <typename T>
class GTree : public Tree<T>
{
    // 递归查找函数
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const;
    GTreeNode<T>* find(GTreeNode<T>* node, TreeNode<T>* nodee) const;

    // 释放堆空间节点空间
    void free(GTreeNode<T>* node);
public:
    bool insert(TreeNode<T>* node);
    bool insert(const T& value, TreeNode<T>* parent);
    SharedPointer<Tree<T>> remove(const T& value) {};
    SharedPointer<Tree<T>> remove(TreeNode<T>* node) {};
    GTreeNode<T>* find(const T& value) const       // 由于GTreeNode为TreeNode的子类, 所以返回类型可以使用子类代替, 但参数类型不可使用子类代替父类
    {
        return find(root(), value);
    }
    GTreeNode<T>* find(TreeNode<T>* node) const
    {
        return find(root(), node);
    }
    GTreeNode<T>* root() const
    {
        return this->m_root ? dynamic_cast<GTreeNode<T>*>(this->m_root) : NULL;
    }
    int degree() const {}
    int count() const {}
    int height() const {}
    void clear();

    ~GTree<T>();
};

// 递归查找函数, 从node节点按值查找
template <typename T>
GTreeNode<T>* GTree<T>::find(GTreeNode<T>* node, const T& value) const
{
    GTreeNode<T>* ret = NULL;

    // 节点为空, 不查找, 直接返回空(递归查找函数出口)
    if(node != NULL)
    {
        // 查找到值相等时, 返回节点
        if(node->value == value)
        {
            ret = node;
        }
        else
        {
            if(node->child.length() > 0)
            {
                // 该节点拥有N个子节点, 所以使用for循环遍历, 并判断是否查找到, 查找到直接结束循环
                for(node->child.moveInit(0); !node->child.end() && (ret == NULL); node->child.next())
                {
                    // 递归查找
                    ret = find(node->child.currentValue(), value);
                }
            }
        }
    }

    return ret;
}
// 递归查找函数, 从node节点按节点(地址)查找
template <typename T>
GTreeNode<T>* GTree<T>::find(GTreeNode<T>* node, TreeNode<T>* obj) const
{
    GTreeNode<T>* ret = NULL;

    // 节点为空, 不查找, 直接返回空(递归查找函数出口)
    if(node != NULL)
    {
        // 查找到节点(地址)相等时, 返回节点
        if(node == obj)
        {
            ret = dynamic_cast<GTreeNode<T>*>(obj);
        }
        else
        {
            if(node->child.length() > 0)
            {
                // 该节点拥有N个子节点, 所以使用for循环遍历, 并判断是否查找到, 查找到直接结束循环
                for(node->child.moveInit(0); !node->child.end() && (ret == NULL); node->child.next())
                {
                    // 递归查找
                    ret = find(node->child.currentValue(), obj);
                }
            }
        }
    }

    return ret;
}

// 插入节点函数 => 插入节点的父类已经存在, 该函数作用是: 将该节点加入指向父类的子类链表中
template <typename T>
bool GTree<T>::insert(TreeNode<T>* node)
{
    bool ret = false;

    // 插入的新节点不能为空
    if(node != NULL)
    {
        // 插入的新节点为该树的第一个节点
        if(this->m_root == NULL)
        {
            node->parent = NULL;
            this->m_root = node;
        }
        else
        {
            // 查找插入节点的父节点
            GTreeNode<T>* parent = find(node->parent);

            if(parent != NULL)
            {
                // 将插入的新节点类型转换
                GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);

                // 插入的新节点不在父类的子类中才插入
                if(parent->child.find(n) < 0)
                {
                    parent->child.insert(n);

                    ret = true;
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be NULL...");
    }

    return ret;
}
template <typename T>
bool GTree<T>::insert(const T& value, TreeNode<T>* parent)
{
    bool ret = false;

    // 创建新节点对象
    GTreeNode<T>* node = GTreeNode<T>::NewNode();

    if(node != NULL)
    {
        // 新节点赋值
        node->value = value;
        node->parent = parent;

        // 将新节点插入树中
        ret = insert(node);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node...");
    }

    return ret;
}

// 释放堆空间节点空间
template <typename T>
void GTree<T>::free(GTreeNode<T>* node)
{
    if(node != NULL)
    {
        // 判断是否有子类链表
        if(node->child.length() > 0)
        {
            // 设置链表的当前节点为首节点
            node->child.moveInit(0);

            // 判断链表的当前节点是否为空
            while(!node->child.end())
            {
                GTreeNode<T>* del = node->child.currentValue();

                // 递归释放内存堆空间
                free(del);

                // 删除链表节点(当前节点后移), 链表节点的值为子类树节点地址, 子类树节点被释放后, 其父类的子类链表节点也应被移除
                node->child.remove(node->child.find(del));
            }
        }

        // 内存在堆空间时才释放空间
        if(node->flag())
        {
            delete node;
        }
    }
}
template <typename T>
void GTree<T>::clear()
{
    free(root());

    // 树根节点赋空, 防止由于其为栈空间而没释放问题
    this->m_root = NULL;
}

// 析构函数
template <typename T>
GTree<T>::~GTree<T>()
{
    clear();
}

}

#endif // GTREE_H
