#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "Array.h"
#include "SharedPointer.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace DemoData
{

/* 图(抽象类) */
template <typename V, typename E>
class Graph : public Object
{
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V& value) = 0;
    virtual bool setVertex(int i, const V& value) = 0;
    virtual SharedPointer<Array<int>> getAdjacent(int i) = 0;
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E& value) = 0;
    virtual bool setEdge(int i, int j, const E& value) = 0;
    virtual bool removeEdge(int i, int j) = 0;
    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;
    virtual int TD(int i) = 0;

    // 广度优先算法(Breadth First Search)
    virtual SharedPointer<Array<int>> BFS(int i);
};

// 广度优先算法(Breadth First Search)
template <typename V, typename E>
SharedPointer<Array<int>> Graph<V, E>::BFS(int i)
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

                    if(aj->length() > 0)
                    {
                        for(int j = 0; j < aj->length(); j++)
                        {
                            // 将邻接顶点加入重复队列中
                            tmpQueue.add((*aj)[j]);
                        }
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

}

#endif // GRAPH_H
