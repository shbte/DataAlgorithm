#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include "Graph.h"

namespace DemoData
{

template <typename V, typename E, int N>
class MatrixGraph : public Graph<V, E>
{
protected:
    V* m_vertexes[N];   // 图的顶点集, 保存该顶点的值 => 指针数组, 数组内容为V类型的指针 => 防止数据类型过于多的无效构造, 因此使用的是指针数组, 而不直接使用数组
    E* m_edges[N][N];   // 图的边集, 保存点与点之间的权重 => 指针数组, 数组内容为E类型的指针
    int m_eCount;       // 图的边数

public:
    MatrixGraph<V, E, N>();

    /* 顶点函数 */
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

    ~MatrixGraph<V, E, N>();
};

// 构造函数 =>
template <typename V, typename E, int N>
MatrixGraph<V, E, N>::MatrixGraph()
{
    // 边数赋值0
    m_eCount = 0;

    for(int i = 0; i < N; i++)
    {
        // 顶点集赋空
        m_vertexes[i] = NULL;

        for(int j = 0; j < N; j++)
        {
            // 边集赋空
            m_edges[i][j] = NULL;
        }
    }
}

/* 顶点函数 */
// 获取i位置顶点值
template <typename V, typename E, int N>
V MatrixGraph<V, E, N>::getVertex(int i)
{
    V ret;

    // 判断顶点值是否获取成功
    if(!getVertex(i, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
    }

    return ret;
}
// 获取i位置顶点值, 并使用引用参数传出
template <typename V, typename E, int N>
bool MatrixGraph<V, E, N>::getVertex(int i, V& value)
{
    // 判断顶点位置是否合法
    bool ret = ((0 <= i) && (i < vCount()));

    if(ret)
    {
        // 判断该顶点是否为空
        if(m_vertexes[i] != NULL)
        {
            // 获取顶点值
            value = *(m_vertexes[i]);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "No value assigned to this vertexes...");
        }
    }

    return ret;
}
// 设置i位置顶点值
template <typename V, typename E, int N>
bool MatrixGraph<V, E, N>::setVertex(int i, const V& value)
{
    // 判断顶点位置是否合法
    bool ret = ((0 <= i) && (i < vCount()));

    if(ret)
    {
        V* tmpV = m_vertexes[i];

        // 判断顶点是否为空
        if(tmpV == NULL)
        {
            // 创建内存堆空间对象
            tmpV = new V();
        }

        // 判断定点对象是否创建成功
        if(tmpV != NULL)
        {
            // 顶点对象赋值
            *tmpV = value;

            // 将顶点对象赋值给图
            m_vertexes[i] = tmpV;
        }
        // 对象创建失败时, 报异常
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new vertexes...");
        }
    }

    return ret;
}
// 获取i位置顶点的相邻顶点 => 能到达的顶点
template <typename V, typename E, int N>
SharedPointer<Array<int>> MatrixGraph<V, E, N>::getAdjacent(int i)
{
    DynamicArray<int>* ret = NULL;

    // 判断顶点位置是否合法
    if((0 <= i) && (i < vCount()))
    {
        // 记录相邻的顶点个数
        int n = 0;

        // 循环该顶点相关的出度边集
        for(int j = 0; j < vCount(); j++)
        {
            // 如果出度边集有值, 则相邻顶点个数+1
            if(m_edges[i][j] != NULL)
            {
                n++;
            }
        }

        // 创建动态数组以存储相邻顶点的位置
        ret = new DynamicArray<int>(n);

        // 判断动态数组创建是否成功
        if(ret != NULL)
        {
            // 循环该顶点相关的出度边集
            for(int j = 0, k = 0; j < vCount(); j++)
            {
                // 如果出度边集有值, 则获取该位置的下标值
                if(m_edges[i][j] != NULL)
                {
                    //ret[k] = j;   //不能使用这个对自定义的动态数组赋值, 这里调用的是构造函数, 而不是赋值函数
                    ret->set(k++, j);
                }
            }
        }
        // 创建数组失败则报异常
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create ret object(dynamicArray)...");
        }

        return ret;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
    }
}

/* 边函数 */
// 获取边集的权重值(顶点i和顶点j是否有边)
template <typename V, typename E, int N>
E MatrixGraph<V, E, N>::getEdge(int i, int j)
{
    E ret;

    // 判断边值是否获取成功
    if(!getEdge(i, j, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i/j is invalid...");
    }

    return ret;
}
// 获取边集值的权重值, 并使用引用参数传出
template <typename V, typename E, int N>
bool MatrixGraph<V, E, N>::getEdge(int i, int j, E& value)
{
    // 判断顶点位置是否合法
    bool ret = (((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount())));

    if(ret)
    {
        // 判断边集权重是否为空
        if(m_edges[i][j] != NULL)
        {
            // 获取边集的权重值
            value = *(m_edges[i][j]);
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "No value assigned to this edge");
        }
    }

    return ret;
}
// 设置边集的权重值
template <typename V, typename E, int N>
bool MatrixGraph<V, E, N>::setEdge(int i, int j, const E& value)
{
    // 判断顶点位置是否合法
    bool ret = (((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount())));

    if(ret)
    {
        E* tmpE = m_edges[i][j];

        // 判断顶点是否为空
        if(tmpE == NULL)
        {
            // 创建内存堆空间对象
            tmpE = new E();

            // 边数+1
            m_eCount++;
        }

        // 判断边集对象创建是否成功
        if(tmpE != NULL)
        {
            // 边集对象赋值
            *tmpE = value;

            // 将边集对象赋值给图
            m_edges[i][j] = tmpE;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create new edge...");
        }
    }

    return ret;
}
// 删除边集
template <typename V, typename E, int N>
bool MatrixGraph<V, E, N>::removeEdge(int i, int j)
{
    // 判断顶点位置是否合法
    bool ret = (((0 <= i) && (i < vCount())) && ((0 <= j) && (j < vCount())));

    if(ret)
    {
        E* toDel = m_edges[i][j];

        // 边集赋空
        m_edges[i][j] = NULL;

        // 判断边集是否为空
        if(toDel != NULL)
        {
            // 释放对应顶点边集的内存堆空间
            delete toDel;

            // 边数=1
            m_eCount--;
        }
    }

    return ret;
}

/* 属性函数 */
// 获取图的顶点数
template <typename V, typename E, int N>
int MatrixGraph<V, E, N>::vCount()
{
    return N;
}
// 获取图的边数
template <typename V, typename E, int N>
int MatrixGraph<V, E, N>::eCount()
{
    return m_eCount;
}
// 获取顶点的出度数
template <typename V, typename E, int N>
int MatrixGraph<V, E, N>::OD(int i)
{
    // 判断顶点位置是否合法
    if((0 <= i) && (i < vCount()))
    {
        int ret = 0;

        // 循环该顶点相关的出度边集
        for(int j = 0; j < vCount(); j++)
        {
            // 边集值不为空时, 出度+1
            if(m_edges[i][j] != NULL)
            {
                ret++;
            }
        }

        return ret;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
    }
}
// 获取顶点的入度数
template <typename V, typename E, int N>
int MatrixGraph<V, E, N>::ID(int i)
{
    // 判断顶点位置是否合法
    if((0 <= i) && (i < vCount()))
    {
        int ret = 0;

        // 循环该顶点相关的入度边集
        for(int j = 0; j < vCount(); j++)
        {
            // 边集不为空时, 入度+1
            if(m_edges[j][i] != NULL)
            {
                ret++;
            }
        }

        return ret;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter i is invalid...");
    }
}
// 获取顶点的度数
template <typename V, typename E, int N>
int MatrixGraph<V, E, N>::TD(int i)
{
    return (ID(i) + OD(i));
}

// 析构函数
template <typename V, typename E, int N>
MatrixGraph<V, E, N>::~MatrixGraph<V, E, N>()
{
    for(int i = 0; i < N; i++)
    {
        // 释放顶点集所使用的内存空间
        if(m_vertexes[i] != NULL)
        {
            delete m_vertexes[i];
        }

        for(int j = 0; j < N; j++)
        {
            if(m_edges[i][j] != NULL)
            {
                // 释放边集所使用的内存空间
                delete m_edges[i][j];

                // 边数-1
                m_eCount--;
            }
        }
    }
}

}

#endif // MATRIXGRAPH_H
