#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "Array.h"
#include "SharedPointer.h"
#include "LinkQueue.h"
#include "DynamicArray.h"
#include "LinkStack.h"
#include "Sort.h"

namespace DemoData
{

// 边结构体
template <typename W>
struct Edge : public Object
{
    int b;  // 起始顶点
    int e;  // 邻接顶点
    W w;    // 权重

    Edge<W>(int i = -1, int j = -1)
    {
        b = i;
        e = j;
    }

    Edge<W>(int i, int j, const W& weight)
    {
        b = i;
        e = j;
        w = weight;
    }

    // 重载比较操作符
    bool operator ==(const Edge<W>& obj)
    {
        return ((b == obj.b) && (e == obj.e));
    }

    bool operator > (const Edge<W>& obj)
    {
        return (w > obj.w);
    }
    bool operator < (const Edge<W>& obj)
    {
        return (w < obj.w);
    }
};

/* 图(抽象类) */
template <typename V, typename W>
class Graph : public Object
{
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharedPointer<Array<int>> getAdjacent(int i) = 0;
    virtual W getEdgeWeight(int i, int j) = 0;
    virtual bool getEdgeWeight(int i, int j, W& weight) = 0;
    virtual bool setEdgeWeight(int i, int j, const W& weight) = 0;
    virtual bool removeEdgeWeight(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;
    virtual int TD(int i) = 0;

    // 广度优先算法(Breadth First Search) => 队列实现, 层次遍历
    SharedPointer<Array<int>> BFS(int i);
    // 深度优先算法(Depth First Search) => 栈实现, 先序遍历, 非递归
    SharedPointer<Array<int>> DFS(int i);
    // 深度优先算法(Depth First Search) => 栈实现, 先序遍历, 递归
    SharedPointer<Array<int>> DFS1(int i);
    // 先序遍历图顶点核心函数 => 递归实现
    void DFS1(int i, Array<int>* ret, int& size, Array<bool>& visited);

    // 顶点间邻接判断函数
    bool isAdjacent(int i, int j);
    // 无向图判断函数 => 有向图: false、无向图: true
    bool isUndirected();
    // 最小/最大生成树 => 连接顶点间的最小/最大权值 => 以顶点为核心
    SharedPointer<Array<Edge<W>>> Prim(bool min = true);

    // 获取无向图的所有非重复边
    SharedPointer<Array<Edge<W>>> getUndirectedEdges();
    // 获取顶点的最前驱顶点下标
    int find(Array<int>& p, int i);
    // 最小/最大生成树 => 连接顶点间的最小/最大权值 => 以边为核心
    SharedPointer<Array<Edge<W>>> Kruskal(bool min = true);
};

// 广度优先算法(Breadth First Search)
template <typename V, typename W>
SharedPointer<Array<int>> Graph<V, W>::BFS(int i)
{
    // 判断顶点下标是否合法
    if((0 <= i) && (i < vCount()))
    {
        // 临时队列, 保存邻接顶点(重复)
        LinkQueue<int> tmpQueue;
        // 临时队列, 保存邻接顶点(非重复)
        LinkQueue<int> queue;

        // 记录邻接顶点释放被保存进非重复队列
        DynamicArray<bool> visited(vCount());
        // 保存遍历顶点的下标
        DynamicArray<int>* ret = NULL;

        for(int j = 0; j < visited.length(); j++)
        {
            // 顶点没被保存, 标记默认值false
            visited.set(j, false);
        }

        // 创建返回动态数组内存堆空间, 保存层次遍历顶点的下标
        ret = new DynamicArray<int>(vCount());

        // 判断动态数组是否创建成功
        if(ret)
        {
            // 将顶点加入重复队列
            tmpQueue.add(i);

            // 判断非重复队列是否获取完毕
            while(queue.size() != vCount())
            {
                // 获取重复队列头元素
                int front = tmpQueue.front();

                // 移除重复队列头元素
                tmpQueue.remove();

                // 判断头元素是否已经加入了队列
                if(!visited[front])
                {
                    // 获取头元素的邻接顶点
                    SharedPointer<Array<int>> aj = getAdjacent(front);

                    for(int j = 0; j < aj->length(); j++)
                    {
                        // 将邻接顶点加入重复队列中
                        tmpQueue.add((*aj)[j]);
                    }

                    // 将头元素加入非重复队列
                    queue.add(front);
                    // 表明顶点下标已获取, 标记值设为true
                    visited.set(front, true);
                }
            }

            // 获取队列大小, 理应与vCount相等
            int size = queue.size();
            for(int j = 0; j < size; j++, queue.remove())
            {
                // 将队列元素(层次遍历顶点)加入动态数组中
                ret->set(j, queue.front());
            }

            return ret;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create ret object(DynamicArray)...");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter index is invalid...");
    }
}
// 深度优先算法(Depth First Search) => 栈实现, 先序遍历
template <typename V, typename W>
SharedPointer<Array<int>> Graph<V, W>::DFS(int i)
{
    if((0 <= i) && (i < vCount()))
    {
        // 临时栈, 保存邻接顶点(重复)
        LinkStack<int> tmpStack;
        // 临时栈, 保存邻接顶点(重复)
        LinkStack<int> stack;

        // 记录邻接顶点释放被保存进非重复队列
        DynamicArray<bool> visited(vCount());
        // 保存遍历顶点的下标
        DynamicArray<int>* ret = NULL;

        for(int j = 0; j < visited.length(); j++)
        {
            // 顶点没被保存, 标记默认值false
            visited.set(j, false);
        }

        // 创建返回动态数组内存堆空间, 保存层次遍历顶点的下标
        ret = new DynamicArray<int>(vCount());

        // 判断动态数组是否创建成功
        if(ret != NULL)
        {
            // 将顶点加入重复栈
            tmpStack.push(i);

            // 判断重复栈是否为空
            while(tmpStack.size() > 0)
            {
                // 获取重复栈的栈顶元素
                int top = tmpStack.top();

                // 移除重复栈的栈顶元素
                tmpStack.pop();

                // 判断栈顶元素是否加入了栈
                if(!visited[top])
                {
                    // 获取栈顶元素的邻接顶点
                    SharedPointer<Array<int>> aj = getAdjacent(top);

                    // 将先序顶点压入栈 => 先序遍历核心
                    for(int j = (aj->length() - 1); j >= 0; j--)
                    {
                        // 将重复顶点压入栈中
                        tmpStack.push((*aj)[j]);
                    }

                    // 将顶点压入非重复栈
                    stack.push(top);
                    // 表明顶点下标已获取, 标记值设为true
                    visited.set(top, true);
                }
            }

            // 获取队列大小, 理应与vCount相等
            int size = stack.size();
            // 按照栈的先序顺序加入数组
            for(int j = (size - 1); j >= 0; j--, stack.pop())
            {
                // 将栈顶元素(先序遍历顶点)加入动态数组中
                ret->set(j, stack.top());
            }

            return ret;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create ret object(DynamicArray)...");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter index is invalid...");
    }
}
// 深度优先算法(Depth First Search) => 栈实现, 先序遍历, 递归
template <typename V, typename W>
SharedPointer<Array<int>> Graph<V, W>::DFS1(int i)
{
    // 判断顶点下标是否合法
    if((0 <= i) && (i < vCount()))
    {
        // 记录邻接顶点释放被保存进非重复队列
        DynamicArray<bool> visited(vCount());
        // 保存遍历顶点的下标
        DynamicArray<int>* ret = NULL;

        for(int j = 0; j < visited.length(); j++)
        {
            // 顶点没被保存, 标记默认值false
            visited.set(j, false);
        }

        // 创建返回动态数组内存堆空间, 保存层次遍历顶点的下标
        ret = new DynamicArray<int>(vCount());

        // 判断动态数组是否创建成功
        if(ret != NULL)
        {
            // 记录已保存好的尾顶点下标
            int retIndex = -1;
            // 先序遍历获取图顶点 => 先序遍历图顶点核心函数
            DFS1(i, ret, retIndex, visited);

            return ret;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create ret object(DynamicArray)...");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter index is invalid...");
    }
}
// 先序遍历图顶点核心函数 => 递归实现
template <typename V, typename W>
void Graph<V, W>::DFS1(int i, Array<int>* ret, int& retIndex, Array<bool>& visited)
{
    // 判读顶点下标是否合法
    if((0 <= i) && (i < vCount()))
    {
        // 判断顶点元素是否已被保存
        if(!visited[i])
        {
            // 将顶点元素保存
            ret->set(++retIndex, i);
            // 表明顶点下标已获取, 标记值设为true
            visited[i] = true;

            // 获取顶点元素的邻接顶点
            SharedPointer<Array<int>> aj = getAdjacent(i);

            for(int j = 0; j < aj->length(); j++)
            {
                // 递归遍历邻接顶点
                DFS1((*aj)[j], ret, retIndex, visited);
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter index is invalid...");
    }
}

// 顶点间邻接判断函数
template <typename V, typename W>
bool Graph<V, W>::isAdjacent(int i, int j)
{
    bool ret = false;

    // 判断顶点位置是否合法
    if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
    {
        // 获取顶点的邻接顶点
        SharedPointer<Array<int>> aj = getAdjacent(i);

        // !ret: 邻接存在则循环结束
        for(int k = 0; (k < aj->length()) && (!ret); k++)
        {
            // 判断邻接顶点中是否存在指定顶点, 存在则说明指定顶尖间邻接, 赋值true
            if((*aj)[k] == j)
            {
                ret = true;
            }
        }
    }

    return ret;
}
// 无向图判断函数
template <typename V, typename W>
bool Graph<V, W>::isUndirected()
{
    bool ret = true;

    // ret为false时, 为无向图, 循环结束
    for(int i = 0; (i < vCount()) && (ret); i++)
    {
        SharedPointer<Array<int>> aj = getAdjacent(i);

        // ret为false时, 为无向图, 循环结束
        for(int j = 0; (j < aj->length()) && (ret); j++)
        {
            // 以邻接顶点为起始, 判断顶点间是否反邻接
            if(!isAdjacent((*aj)[j], i))
            {
                ret = false;
            }
        }
    }

    return ret;
}

// 最小/最大生成树 => 连接顶点间的最小/最大权值
template <typename V, typename W>
SharedPointer<Array<Edge<W>>> Graph<V, W>::Prim(bool min)
{
    if(isUndirected())
    {
        DynamicArray<Edge<W>>* ret = new DynamicArray<Edge<W>>(vCount() - 1);
        int retIndex = 0;

        if(ret != NULL)
        {
            // 标记顶点是否已连接 => 数组下标为顶点, 数组值为连接状态(已连接为true, 未连接未false)
            DynamicArray<bool> vexArray(vCount());
            // 已连接和未连接顶点 => 数组下标为未连接顶点, 数组值为已连接顶点
            DynamicArray<int> adjVexArray(vCount());
            // 已连接和未连接顶点间的最小权值 => 数组下标为未连接顶点, 数组值为最小权值(以为连接顶点为起始)
            DynamicArray<W> adjVexMWeiArray(vCount());

            // 最小权值集合中的最小值
            W mAdjVexWei;
            // 最小权值的连接顶点下标
            int mVexIndex;
            // 最小权值的未连接顶点下标
            int mAdjVexIndex;

            // 以0顶点为起始(赋值true), 其余顶点为未连接顶点
            vexArray[0] = true;
            for(int i = 1; i < vCount(); i++)
            {
                vexArray[i] = false;
            }

            // 判断已获取的连接边 => 边数 = 顶点个数 - 1
            while(retIndex < (vCount() - 1))
            {
                // 初始化
                for(int i = 0; i < vCount(); i++)
                {
                    if(!vexArray[i])
                    {
                        adjVexArray[i] = -1;
                        adjVexMWeiArray[i] = min ? 999999999 : -1;
                        mAdjVexWei = adjVexMWeiArray[i];
                    }
                }
                mVexIndex = 0;
                mAdjVexIndex = -1;

                for(int i = 0; i < vCount(); i++)
                {
                    // 判断该顶点是否已连接, 未连接则结束(获取已连接顶点)
                    if(vexArray[i])
                    {
                        SharedPointer<Array<int>> aj = getAdjacent(i);

                        for(int j = 0; j < aj->length(); j++)
                        {
                            // 获取已连接顶点的邻接顶点
                            int adjVexIndex = (*aj)[j];

                            // 判断邻接顶点是否已连接, 连接则结束(获取未连接顶点)
                            if(!vexArray[adjVexIndex])
                            {
                                // 获取已连接顶点与未连接顶点的边的权值
                                W adjVexWei = getEdgeWeight(i, adjVexIndex);

                                // 判断权值
                                if(min ? (adjVexMWeiArray[adjVexIndex] > adjVexWei) : (adjVexMWeiArray[adjVexIndex] < adjVexWei))
                                {
                                    // i: 起始顶点(已连接)  adjVexIndex: 结束顶点(未连接)
                                    adjVexArray[adjVexIndex] = i;
                                    // 保存已连接顶点与未连接顶点的边的权值
                                    adjVexMWeiArray[adjVexIndex] = adjVexWei;

                                    // 判断是否为最小/最大
                                    if(min ? (mAdjVexWei > adjVexWei) : (mAdjVexWei < adjVexWei))
                                    {
                                        // 已连接顶点与未连接顶点的起始顶点下标、结束顶点下标、权值
                                        mVexIndex = i;
                                        mAdjVexIndex = adjVexIndex;
                                        mAdjVexWei = adjVexWei;
                                    }
                                }
                            }
                        }
                    }
                }

                // 保存 已连接顶点与未连接顶点间的最小权值边
                ret->set(retIndex++, Edge<W>(mVexIndex, mAdjVexIndex, mAdjVexWei));
                // 将未连接顶点设置为已连接
                vexArray[mAdjVexIndex] = true;
            }

            return ret;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create ret object(DynamicArray)");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidOperatorException, "Prim operation is for undirected argph only...");
    }
}

// 获取无向图的所有非重复边
template <typename V, typename W>
SharedPointer<Array<Edge<W>>>  Graph<V, W>::getUndirectedEdges()
{
    if(isUndirected())
    {
        DynamicArray<Edge<W>>* ret = NULL;
        LinkQueue<Edge<W>> queue;

        // 循环遍历顶点, 获取顶点间的边
        for(int i = 0; i < vCount(); i++)
        {
            // 为了获取的边不前后重复, 因此邻接顶点要大于起始顶点
            for(int j = (i + 1) ; j < vCount(); j++)
            {
                if(isAdjacent(i, j))
                {
                    // 顶点间相邻时, 加入边队列
                    queue.add(Edge<W>(i, j, getEdgeWeight(i, j)));
                }
            }
        }

        // 以边队列大小创建返回堆空间数组对象
        ret = new DynamicArray<Edge<W>>(queue.size());

        if(ret != NULL)
        {
            for(int i = 0; i < ret->length(); i++)
            {
                // 将队列头元素放入返回数组
                ret->set(i, queue.front());
                // 移除队列头元素
                queue.remove();
            }

            return ret;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create ret object(DynamicArray)...");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "GetUndirectedEdges operation is for undirected argph only...");
    }
}
// 获取顶点的最前驱顶点下标 => p[n]为顶点n的前驱顶点
template <typename V, typename W>
int Graph<V, W>::find(Array<int>& p, int i)
{
    int ret = -1;

    // p[i]不为-1时, 说明i有p[i]为前驱节点, 需要再往前寻找前驱顶点, 直至最前驱顶点
    while(p[i] != -1)
    {
        i = p[i];
    }
    ret = i;

    return ret;
}
// 最小/最大生成树 => 连接顶点间的最小/最大权值 => 以边为核心
template <typename V, typename W>
SharedPointer<Array<Edge<W>>> Graph<V, W>::Kruskal(bool min)
{
    if(isUndirected())
    {
        DynamicArray<Edge<W>>* ret = NULL;
        // 因为不能确定边的数量, 所以使用中间队列来接收选择好的边
        LinkQueue<Edge<W>> queue;

        // pre[i]为i的前驱节点
        DynamicArray<int> pre(vCount());
        // 获取当前图的所有非重复边
        SharedPointer<Array<Edge<W>>> gEdges = getUndirectedEdges();

        for(int i = 0; i < pre.length(); i++)
        {
            // 初始化, 所有顶点的前驱顶点为空(-1)
            pre.set(i, -1);
        }

        // 将所有边按照权值排序 => 核心1 => 注意: Shell第一个参数是数组类指针(*gEdges不是数组类指针, 而是自定义数组类)
        Sort::Shell(gEdges.get()->array(), (*gEdges).length(), min);

        // 按顺序获取边, 并判断已选择边是否构造回路 => 核心2
        for(int i = 0; i < (*gEdges).length(); i++)
        {
            int b = find(pre, (*gEdges)[i].b);
            int e = find(pre, (*gEdges)[i].e);

            if(b != e)
            {
                // 该边与已选择的边不构成回路, 可加入选择边
                queue.add(Edge<W>((*gEdges)[i].b, (*gEdges)[i].e, getEdgeWeight((*gEdges)[i].b, (*gEdges)[i].e)));

                // 设置顶点e的前置顶点为b
                pre[e] = b;
            }
        }

        ret = new DynamicArray<Edge<W>>(queue.size());

        if(ret != NULL)
        {
            // 将选择好的边放入返回值对象中
            for(int i = 0; i < ret->length(); i++)
            {
                ret->set(i, queue.front());
                queue.remove();
            }

            return ret;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to create ret object<DynamicArray)...");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidOperatorException, "Prim operation is for undirected argph only...");
    }
}

}

#endif // GRAPH_H
