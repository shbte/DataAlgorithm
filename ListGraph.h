#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "LinkList.h"
#include "DynamicArray.h"

namespace DemoData
{

// 边结构体
template <typename E>
struct Edge : public Object
{
    int b;  // 起始顶点
    int e;  // 邻接顶点
    E data; // 权重

    Edge<E>(int i = -1, int j = -1)
    {
        b = i;
        e = j;
    }

    Edge<E>(int i, int j, const E& value)
    {
        b = i;
        e = j;
        data = value;
    }

    // 重载比较操作符
    bool operator ==(const Edge& obj)
    {
        return ((b == obj.b) && (e == obj.e));
    }
};
// 顶点结构体
template <typename V, typename E>
struct Vertex : public Object
{
    V* data;    // 顶点值
    LinkList<Edge<E>> edge_list;    // 顶点出度(边)

    Vertex<V, E>()
    {
        data = NULL;
    }

    ~Vertex<V, E>()
    {
        if(data != NULL)
        {
            // 释放内存堆空间
            delete data;

            // 释放链表, 链表节点所使用的是内存堆空间(new Node)
            edge_list.clear();
        }
    }
};

// 邻接链表图
template <typename V, typename E>
class ListGraph : public Graph<V, E>
{
public:
    // 顶点链表, 相比数组可更省内存堆空间
    LinkList<Vertex<V, E>*> m_list;

public:
    ListGraph<V, E>(int n = 0);

    /* 顶点函数 */
    int addVertex();
    int addVertex(const V& value);
    void removeVertex();
    V getVertex(int i);
    bool getVertex(int i, V& value);
    bool setVertex(int i, const V& value);
    SharedPointer<Array<int>> getAdjacent(int i);

    /* 边函数 */
    E getEdge(int i, int j);
    bool getEdge(int i, int j, E& value);
    bool setEdge(int i, int j, const E& value);
    bool removeEdge(int i, int j);

    /* 属性函数 */
    int vCount();
    int eCount();
    int OD(int i);
    int ID(int i);
    int TD(int i);

    ~ListGraph<V, E>();
};

// 构造函数
template <typename V, typename E>
ListGraph<V, E>::ListGraph(int n)
{
    for(int i = 0; i < n; i++)
    {
        // 添加顶点
        addVertex();
    }
}

/* 顶点函数 */
// 创建新顶点对象, 不指定V
template <typename V, typename E>
int ListGraph<V, E>::addVertex()
{
    int ret = -1;

    // 创建顶点堆空间对象
    Vertex<V, E>* vertex = new Vertex<V, E>();

    // 判断对象是否创建成功
    if(vertex != NULL)
    {
        // 将顶点放进图的顶点链表中
        m_list.insert(vertex);

        // 返回新顶点的下标值
        ret = m_list.length() - 1;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new Vertex...");
    }

    return ret;
}
// 创建新顶点对象, 指定V
template <typename V, typename E>
int ListGraph<V, E>::addVertex(const V& value)
{
    // 创建新顶点对象
    int ret = addVertex();

    // 判断新顶点下标是否正确
    if(ret >= 0)
    {
        // 顶点赋值, 指定V
        setVertex(ret, value);
    }

    return ret;
}
// 删除顶点对象(从链表中删除), 为了防止中间顶点被删除而导致剩余顶点的下标值错乱等问题, 只能从链表尾部删除
template <typename V, typename E>
void ListGraph<V, E>::removeVertex()
{
    // 判断顶点链表是否为空
    if(m_list.length() > 0)
    {
        // 获取顶点链表尾部下标
        int index = m_list.length() - 1;
        // 获取链表的尾部顶点
        Vertex<V, E>* vertex = m_list.get(index);

        // 判断尾部顶点是否删除成功
        if(m_list.remove(index))
        {
            // 判断顶点链表是否为空
            if(m_list.length() > 0)
            {
                // 循环遍历顶点链表, 并删除与被删顶点相关联的边
                for(int i = (m_list.moveInit(0), 0); !m_list.end(); m_list.next())
                {
                    // 获取与被删顶点相关联的边节点下标
                    int pos = m_list.currentValue()->edge_list.find(Edge<E>(i++, index));

                    // 判断边节点下标是否合法
                    if(pos >= 0)
                    {
                        // 删除与被删顶点相关联的边节点
                        m_list.currentValue()->edge_list.remove(pos);
                    }
                }
            }

            // 释放节点对象中指针所使用的内存堆空间 => 因顶点链表的T为指针类型, remove只释放节点堆空间(指针空间被释放, 但指针指向的空间没有被释放), 因此T类型指针需要手动释放
            delete vertex;
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No vertex in current graph...");
    }
}
// 获取指定下标的顶点值
template <typename V, typename E>
V ListGraph<V, E>::getVertex(int i)
{
    V ret;

    // 判断节点值是否获取成功
    if(!getVertex(i, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid");
    }

    return ret;
}
// 获取指定下标的顶点值, 并使用引用类型参数传出
template <typename V, typename E>
bool ListGraph<V, E>::getVertex(int i, V& value)
{
    bool ret = false;

    // 判断顶点下标是否合法
    if((0 <= i) && (i < vCount()))
    {
        // 获取顶点
        Vertex<V, E>* vertex = m_list.get(i);

        // 判断顶点值是否为空
        if(vertex->data != NULL)
        {
            // 返回参数赋值
            value = *(vertex->data);

            // 表明获取指定下标的顶点值成功, 赋值true
            ret = true;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "No value assigned to this Vertex...");
        }
    }

    return ret;
}
// 设置指定顶点的值
template <typename V, typename E>
bool ListGraph<V, E>::setVertex(int i, const V& value)
{
    bool ret = false;

    // 判断顶点下标是否合法
    if((0 <= i) && (i < vCount()))
    {
        // 获取顶点
        Vertex<V, E>* vertex = m_list.get(i);
        // 获取顶点值
        V* data = vertex->data;

        // 判断顶点值是否为空
        if(data == NULL)
        {
            // 创建顶点值对象
            data = new V();
        }

        // 判断顶点值是否为空
        if(data != NULL)
        {
            // 顶点值赋值指定值
            *data = value;

            // 设置顶点对象的值
            vertex->data = data;

            // 表明设置指定顶点的顶点值成功, 赋值true
            ret = true;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new Vertex...");
        }
    }

    return ret;
}
// 获取顶点的邻接顶点 => 出度顶点
template <typename V, typename E>
SharedPointer<Array<int>> ListGraph<V, E>::getAdjacent(int i)
{
    // 判断顶底啊下标是否合法
    if((0 <= i) && (i < vCount()))
    {
        // 获取顶点
        Vertex<V, E>* vertex = m_list.get(i);
        // 获取顶点的邻接边链表
        LinkList<Edge<E>>& edge_list = vertex->edge_list;

        // 创建动态数组, 保存邻接顶点的下标
        DynamicArray<int>* ret = new DynamicArray<int>(edge_list.length());

        // 判断数组对象是否创建成功
        if(ret != NULL)
        {
            // 判断自顶点的出邻接顶点(出度边)是否为空
            if(edge_list.length() > 0)
            {
                // 循环遍历邻接顶点边
                for(int j = (edge_list.moveInit(0), 0); !edge_list.end(); edge_list.next())
                {
                    // 保存邻接顶点的下标
                    ret->set(j++, edge_list.currentValue().e);
                }
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create ret DynamicArray...");
        }

        return ret;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter index is invalid...");
    }
}

/* 边函数 */
// 获取指定顶点间的权重
template <typename V, typename E>
E ListGraph<V, E>::getEdge(int i, int j)
{
    E ret;

    // 判断指定顶点间的权重是否获取成功
    if(!getEdge(i, j, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "Edge<i, j> is invalid...");
    }

    return ret;
}
// 获取指定顶点间的权重, 并使用引用参数返回
template <typename V, typename E>
bool ListGraph<V, E>::getEdge(int i, int j, E& value)
{
    bool ret = false;

    // 判断顶点下标是否合法
    if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
    {
        // 获取顶点
        Vertex<V, E>* vertex = m_list.get(i);
        // 获取顶点的邻接边链表
        LinkList<Edge<E>>& edge_list = vertex->edge_list;
        // 获取指定顶点关联边的下标
        int pos = edge_list.find(Edge<E>(i, j));

        // 判断关联边下标是否获取成功
        if(pos >= 0)
        {
            // 获取指定顶点间的权重
            value = edge_list.get(pos).data;

            // 表明获取指定顶点间的权重成功, 赋值true
            ret = true;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "No value assigned to this edge...");
        }
    }

    return ret;
}
// 设置指定顶点间的权重
template <typename V, typename E>
bool ListGraph<V, E>::setEdge(int i, int j, const E& value)
{
    bool ret = false;

    // 判断顶点下标是否合法
    if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
    {
        // 获取顶点
        Vertex<V, E>* vertex = m_list.get(i);
        // 获取顶点的邻接边链表
        LinkList<Edge<E>>& edge_list = vertex->edge_list;
        // 获取指定顶点关联边的下标
        int pos = edge_list.find(Edge<E>(i, j));

        // 判断关联边下标是否获取成功
        if(pos >= 0)
        {
            // 指定顶点间的关联表存在时, 设置关联边节点
            ret = edge_list.set(pos, Edge<E>(i, j, value));
        }
        else
        {
            // 指定顶点间的关联表不存在时, 插入关联边节点
            ret = edge_list.insert(Edge<E>(i, j, value));
        }
    }

    return ret;
}
// 删除指定顶点间的关联边
template <typename V, typename E>
bool ListGraph<V, E>::removeEdge(int i, int j)
{
    bool ret = false;

    // 判断顶点下标是否合法
    if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
    {
        // 获取顶点
        Vertex<V, E>* vertex = m_list.get(i);
        // 获取指定顶点关联边的下标
        int pos = vertex->edge_list.find(Edge<E>(i, j));

        // 判断关联边下标是否获取成功
        if(pos >= 0)
        {
            // 删除指定顶点间的关联边
            ret = vertex->edge_list.remove(pos);
        }
    }

    return ret;
}

/* 属性函数 */
// 获取图顶点数
template <typename V, typename E>
int ListGraph<V, E>::vCount()
{
    return m_list.length();
}
// 获取图边数
template <typename V, typename E>
int ListGraph<V, E>::eCount()
{
    int ret = 0;

    // 判断顶点数是否合法
    if(vCount() > 0)
    {
        // 遍历循环顶点链表
        for(m_list.moveInit(0); !m_list.end(); m_list.next())
        {
            // 累加顶点链表的边数
            ret += m_list.currentValue()->edge_list.length();
        }
    }

    return ret;
}
// 获取指定顶点的出度边数
template <typename V, typename E>
int ListGraph<V, E>::OD(int i)
{
    int ret = 0;

    // 判断顶点下标是否合法
    if((0 <= i) && (i < vCount()))
    {
        // 获取顶点链表的边数
        ret = m_list.get(i)->edge_list.length();
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter index is invalid...");
    }

    return ret;
}
// 获取指定顶点的入度边数
template <typename V, typename E>
int ListGraph<V, E>::ID(int i)
{
    int ret = 0;

    // 判断顶点下标是否合法
    if((0 <= i) && (i < vCount()))
    {
        // 遍历循环顶点链表
        for(m_list.moveInit(0); !m_list.end(); m_list.next())
        {
            // 获取顶点
            Vertex<V, E>* vertex = m_list.currentValue();
            // 获取顶点的邻接边链表
            LinkList<Edge<E>>& edge_list = vertex->edge_list;

            // 判断顶点邻接边是否为空
            if(edge_list.length() > 0)
            {
                // 遍历循环顶点邻接边链表
                for(edge_list.moveInit(0); !edge_list.end(); edge_list.next())
                {
                    // 判断顶点的出度边是否为指定顶点
                    if(edge_list.currentValue().e == i)
                    {
                        // 顶点的出度边为指定顶点时, 入度边数+1
                        ret++;
                        // 结束顶点邻接链表的遍历
                        break;
                    }
                }
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter index is invalid...");
    }

    return ret;
}
// 获取指定顶点边
template <typename V, typename E>
int ListGraph<V, E>::TD(int i)
{
    return (OD(i) + ID(i));
}

// 析构函数
template <typename V, typename E>
ListGraph<V, E>::~ListGraph<V, E>()
{
    // 循环遍历释放图所使用的内存堆空间
    while(m_list.length() > 0)
    {
        // 获取顶点
        Vertex<V, E>* toDel = m_list.get(0);

        // 释放顶点所使用的链表节点堆空间(new Node)
        m_list.remove(0);

        // 释放节点对象中指针所使用的内存堆空间 => 因顶点链表的T为指针类型, remove只释放节点堆空间(指针空间被释放, 但指针指向的空间没有被释放), 因此T类型指针需要手动释放
        delete toDel;
    }
}

}

#endif // LISTGRAPH_H
