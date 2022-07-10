#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"

namespace DemoData
{

template <typename T>
class GTree : public Tree<T>
{
protected:
    // 按层次入队存储的树节点队列
    LinkQueue<GTreeNode<T>*> m_queue;

    // 递归查找函数
    GTreeNode<T>* find(GTreeNode<T>* node, const T& value) const;
    GTreeNode<T>* find(GTreeNode<T>* node, TreeNode<T>* nodee) const;

    // 递归释放树堆空间节点
    void free(GTreeNode<T>* node);
    // 删除树节点
    void remove(GTreeNode<T>* node, GTree<T>*& ret);

    // 获取以该节点为根的最大度数
    int degree(GTreeNode<T>* node) const;
    // 获取以该节点为根的节点数
    int count(GTreeNode<T>* node) const;
    // 获取以该节点为根的高度
    int height(GTreeNode<T>* node) const;

    // 拷贝构造函数私有化
    GTree<T>(const GTree<T>&);
    // 赋值操作符函数私有化
    GTree<T>& operator =(const GTree<T>&);
public:
    GTree<T>() {}

    bool insert(TreeNode<T>* node);
    bool insert(const T& value, TreeNode<T>* parent);
    SharedPointer<Tree<T>> remove(const T& value);
    SharedPointer<Tree<T>> remove(TreeNode<T>* node);
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
    int degree() const;
    int count() const;
    int height() const;
    void clear();

    // 遍历功能函数
    bool begin();
    bool next();
    GTreeNode<T>* current();
    bool end();

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

// 删除树节点(在父类的子类链表中, 删除该节点)
template <typename T>
void GTree<T>::remove(GTreeNode<T>* node, GTree<T>*& ret)
{
    // 创建删除树空间并赋值
    ret = new GTree<T>();

    if(ret != NULL)
    {
        // 获取删除节点的父类, 不直接获取是因为父节点可能为空(根节点的父节点为空)
        GTreeNode<T>* parent = dynamic_cast<GTreeNode<T>*>(node->parent);

        // (根节点的父节点为空)
        if(parent != NULL)
        {
            // 获取子类链表
            LinkList<GTreeNode<T> *>& child = parent->child;

            // 从子类链表中删除记录子类节点信息的链表节点(将删除节点从树信息中删除)
            child.remove(child.find(node));

            // 删除节点的父节点清空(将树信息从删除节点中清除)
            node->parent = NULL;
        }
        else
        {
            // 删除节点为根节点时, 原对象树删除(根节点赋空)
            this->m_root = NULL;
        }

        // 将删除树节点树作为新树根节点返回(没创建树空间时, 树指针为空)
        ret->m_root = node;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree...");
    }
}
template <typename T>
SharedPointer<Tree<T>> GTree<T>::remove(const T& value)
{
    // 将删除节点所在的分支作为树返回
    GTree<T>* ret = NULL;

    // 在树中查找删除节点
    GTreeNode<T>* n = find(value);

    // 判断删除节点是否存在树中
    if(n != NULL)
    {
        remove(n, ret);
    }

    // 会调用SharedPointer的构造函数
    return ret;
}
template <typename T>
SharedPointer<Tree<T>> GTree<T>::remove(TreeNode<T>* node)
{
    // 将删除节点所在的分支作为树返回
    GTree<T>* ret = NULL;

    // 在树中查找删除节点
    GTreeNode<T>* n = find(node);

    // 判断删除节点是否存在树中
    if(n != NULL)
    {
        remove(n, ret);
    }

    // 会调用SharedPointer的构造函数
    return ret;
}

// 获取以该节点为根的最大度数
template <typename T>
int GTree<T>::degree(GTreeNode<T>* node) const
{
    int ret = 0;

    // 判断该节点是否为空
    if(node != NULL)
    {
        // 使用引用&, 而不会创建对象
        LinkList<GTreeNode<T>*>& child = node->child;

        // 判断该节点是否存在子类
        if(child.length() > 0)
        {
            // 该节点的子类树等于该节点的度数
            ret = child.length();

            // 循环遍历子类链表, 计算各个子类的度数
            for(child.moveInit(0); !child.end(); child.next())
            {
                // 递归调用, 获取该节点的子类的度数
                int d = degree(child.currentValue());

                // 获取最大度数
                if(d > ret)
                {
                    ret = d;
                }
            }
        }
    }

    return ret;
}
// 树的最大度数
template <typename T>
int GTree<T>::degree() const
{
    return degree(root());
}
// 获取以该节点为根的节点数
template <typename T>
int GTree<T>::count(GTreeNode<T>* node) const
{
    int ret = 0;

    // 判断该节点是否为空
    if(node != NULL)
    {
        // 不为空时, 节点数+1
        ret += 1;

        LinkList<GTreeNode<T>*>& child = node->child;

        // 判断该节点子是否存在子类
        if(child.length() > 0)
        {
            // 遍历追加该节点的子类树的节点数
            for(child.moveInit(0); !child.end(); child.next())
            {
                ret += count(child.currentValue());
            }
        }
    }

    return ret;
}
// 树中节点的数目
template <typename T>
int GTree<T>::count() const
{
    return count(root());
}
// 获取以该节点为根的高度
template <typename T>
int GTree<T>::height(GTreeNode<T>* node) const
{
    int ret = 0;

    // 判断该节点是否为空
    if(node != NULL)
    {
        // 该节点不为空时, 树高度+1
        ret += 1;

        LinkList<GTreeNode<T>*>& child = node->child;

        // 判断该节点是否存在子类
        if(child.length() > 0)
        {
            int h = 0;

            // 遍历获取该节点的的子树的最大高度
            for(child.moveInit(0); !child.end(); child.next())
            {
                int temph = height(child.currentValue());

                // 更新该节点的子树的最大高度
                if(temph > h)
                {
                    h = temph;
                }
            }

            // 将子类树的最大高度加入
            ret += h;
        }
    }

    return ret;
}
// 树的最大高度
template <typename T>
int GTree<T>::height() const
{
    return height(root());
}

/* 遍历功能函数 */
// 将根节点压入队列中给你
template <typename T>
bool GTree<T>::begin()
{
    bool ret = (root() != NULL);

    // 判断树节点是否合法
    if(ret)
    {
        // 将树节点队列清空
        m_queue.clear();

        // 将树的根节点加入队列
        m_queue.add(root());
    }

    return ret;
}
// 队头元素弹出, 将队头元素的孩子压入队列中
template <typename T>
bool GTree<T>::next()
{
    bool ret = !end();

    // 判断队列是否为空
    if(ret)
    {
        // 获取队列头元素
        GTreeNode<T>* node = m_queue.front();

        // 删除队列头元素 => value(GTreeNode<T>*)为指针, 所以此处并不会把树节点空间释放
        m_queue.remove();

        // 判断该节点是否存在子节点
        if(node->child.length() > 0)
        {
            // 循环遍历, 将该节点的子节点元素加入队列
            for(node->child.moveInit(0); !node->child.end(); node->child.next())
            {
                m_queue.add(node->child.currentValue());
            }
        }
    }

    return ret;
}
// 访问队头元素指向的数据元素
template <typename T>
GTreeNode<T>* GTree<T>::current()
{
    GTreeNode<T>* ret = NULL;

    // 判断队列元素是否为空
    if(!end())
    {
        // 返回队列头元素
        ret = m_queue.front();
    }

    return ret;
}
// 判断队列是否为空
template <typename T>
bool GTree<T>::end()
{
    // 队列大小为空时, 当前游标为空(队列游标永远指向队列头元素)
    return (m_queue.size() == 0);
}

// 递归释放树堆空间节点
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

                // 删除链表节点(且当前链表节点会从删除节点后移), 链表节点的值为子类树节点地址, 子类树节点被释放后, 其父类的子类链表节点也应被移除
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
