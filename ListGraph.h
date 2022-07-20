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

    bool operator ==(const Edge& obj)
    {
        return ((b == obj.b) && (e == obj.e));
    }
};
// 顶点结构体
template <typename V, typename E>
struct Vertex : public Object
{
    V* data;
    LinkList<Edge<E>> edge_list;

    Vertex<V, E>()
    {
        data = NULL;
    }

    ~Vertex<V, E>()
    {
        if(data != NULL)
        {
            delete data;
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
template <typename V, typename E>
int ListGraph<V, E>::addVertex()
{
    int ret = -1;

    Vertex<V, E>* vertex = new Vertex<V, E>();

    if(vertex != NULL)
    {
        m_list.insert(vertex);

        ret = m_list.length() - 1;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new Vertex...");
    }

    return ret;
}
template <typename V, typename E>
int ListGraph<V, E>::addVertex(const V& value)
{
    int ret = addVertex();

    if(ret >= 0)
    {
        setVertex(ret, value);
    }

    return ret;
}
template <typename V, typename E>
void ListGraph<V, E>::removeVertex()
{
    if(m_list.length() > 0)
    {
        int index = m_list.length() - 1;
        Vertex<V, E>* vertex = m_list.get(index);

        if(m_list.remove(index))
        {
            for(int i = (m_list.moveInit(0), 0); !m_list.end(); m_list.next())
            {
                int pos = m_list.currentValue()->edge_list.find(Edge<E>(i++, index));

                if(pos >= 0)
                {
                    m_list.currentValue()->edge.remvoe(pos);
                }
            }

            delete vertex;
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No vertex in current graph...");
    }
}
template <typename V, typename E>
V ListGraph<V, E>::getVertex(int i)
{
    V ret;

    if(!getVertex(i, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid");
    }

    return ret;
}
template <typename V, typename E>
bool ListGraph<V, E>::getVertex(int i, V& value)
{
    bool ret = false;

    if((0 <= i) && (i < vCount()))
    {
        Vertex<V, E>* vertex = m_list.get(i);

        if(vertex->data != NULL)
        {
            value = *(vertex->data);

            ret = true;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "No value assigned to this Vertex...");
        }
    }

    return ret;
}
template <typename V, typename E>
bool ListGraph<V, E>::setVertex(int i, const V& value)
{
    bool ret = ((0 <= i) && (i < vCount()));

    if(ret)
    {
        Vertex<V, E>* vertex = m_list.get(i);
        V* data = vertex->data;

        if(data == NULL)
        {
            data = new V();
        }

        if(data != NULL)
        {
            *data = value;

            vertex->data = data;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new Vertex...");
        }
    }

    return ret;
}
template <typename V, typename E>
SharedPointer<Array<int>> ListGraph<V, E>::getAdjacent(int i)
{
    if((0 <= i) && (i < vCount()))
    {

        Vertex<V, E>* vertex = m_list.get(i);
        LinkList<Edge<E>>& edge_list = vertex->edge_list;

        int n = edge_list.length();

        DynamicArray<int>* ret = new DynamicArray<int>(n);

        if(ret != NULL)
        {
            if(edge_list.length() > 0)
            {
                for(int j = (edge_list.moveInit(0), 0); !edge_list.end(); edge_list.next())
                {
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
template <typename V, typename E>
E ListGraph<V, E>::getEdge(int i, int j)
{
    E ret;

    if(!getEdge(i, j, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "Edge<i, j> is invalid...");
    }

    return ret;
}
template <typename V, typename E>
bool ListGraph<V, E>::getEdge(int i, int j, E& value)
{
    bool ret = false;

    if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
    {
        Vertex<V, E>* vertex = m_list.get(i);

        LinkList<Edge<E>>& edge_list = vertex->edge_list;

        int pos = edge_list.find(Edge<E>(i, j));

        if(pos >= 0)
        {
            value = edge_list.get(pos).data;

            ret = true;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "No value assigned to this edge...");
        }
    }

    return ret;
}
template <typename V, typename E>
bool ListGraph<V, E>::setEdge(int i, int j, const E& value)
{
    bool ret = false;

    if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
    {
        Vertex<V, E>* vertex = m_list.get(i);

        LinkList<Edge<E>>& edge_list = vertex->edge_list;

        int pos = edge_list.find(Edge<E>(i, j));

        if(pos >= 0)
        {
            ret = edge_list.set(pos, Edge<E>(i, j, value));
        }
        else
        {
            ret = edge_list.insert(Edge<E>(i, j, value));
        }

        ret = true;
    }

    return ret;
}
template <typename V, typename E>
bool ListGraph<V, E>::removeEdge(int i, int j)
{
    bool ret = false;

    if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
    {
        Vertex<V, E>* vertex = m_list.get(i);

        int pos = vertex->edge_list.find(Edge<E>(i, j));

        if(pos >= 0)
        {
            ret = vertex->edge_list.remove(pos);
        }
    }

    return ret;
}

/* 属性函数 */
template <typename V, typename E>
int ListGraph<V, E>::vCount()
{
    return m_list.length();
}
template <typename V, typename E>
int ListGraph<V, E>::eCount()
{
    int ret = 0;

    if(vCount() > 0)
    {
        for(m_list.moveInit(0); !m_list.end(); m_list.next())
        {
            ret += m_list.currentValue()->edge_list.length();
        }
    }

    return ret;
}
template <typename V, typename E>
int ListGraph<V, E>::OD(int i)
{
    int ret = 0;

    if((0 <= i) && (i < m_list.length()))
    {
        ret = m_list.get(i)->edge_list.length();
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter index is invalid...");
    }

    return ret;
}
template <typename V, typename E>
int ListGraph<V, E>::ID(int i)
{
    int ret = 0;

    if((0 <= i) && (i < vCount()))
    {
        //ret = m_list.get(i)->edge.length();

        for(m_list.moveInit(0); !m_list.end(); m_list.next())
        {
            Vertex<V, E>* vertex = m_list.currentValue();
            LinkList<Edge<E>>& edge_list = vertex->edge_list;

            if(edge_list.length() > 0)
            {
                for(edge_list.moveInit(0); !edge_list.end(); edge_list.next())
                {
                    if(edge_list.currentValue().e == i)
                    {
                        ret++;
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
template <typename V, typename E>
int ListGraph<V, E>::TD(int i)
{
    return (OD(i) + ID(i));
}

// 析构函数
template <typename V, typename E>
ListGraph<V, E>::~ListGraph<V, E>()
{
    m_list.clear();
}

}

#endif // LISTGRAPH_H
