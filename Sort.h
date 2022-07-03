#ifndef SORT_H
#define SORT_H

#include <iostream>
#include "Object.h"

using namespace std;

namespace DemoData
{

class Sort : public Object
{
protected:
    Sort();
    Sort(const Sort&);
    Sort& operator =(const Sort&);

    // 交换函数
    template <typename T>
    static void Swap(T& a, T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

public:

    // 选择排序函数(不稳定> => 获取最小/最大值的坐标, 然后进行交换
    template <typename T>
    static void Select(T array[], int size, bool min2max = true)
    {
        for(int i = 0; i < size; i++)
        {
            // 记录最小/最大值数组元素的下标
            int m = i;

            // 遍历获取未排序的最小/最大数组元素值的下标
            for(int j = i + 1; (j < size); j++)
            {
                // 获取最小值: m > j, 获取最大值: m < j
                if(min2max ? (array[m] > array[j]) : (array[m] < array[j]))
                {
                    m = j;
                }
            }

            // 当前位置不为最小/最大数组元素值时, 交换
            if(m != i)
            {
                Swap(array[i], array[m]);
            }
        }
    }

    // 插入排序函数(稳定) => 使用未排序的数组元素, 与排序好的数组元素进行比较后插入
    template <typename T>
    static void Insert(T array[], int size, bool min2max = true)
    {
        for(int i = 1; i < size; i++)
        {
            // 获取标记数组元素下标(插入位置下标)
            int mark = i;
            // 获取本次排序的数组元素值
            T v = array[mark];

            // 本次排序的数组元素值与排序好的数组元素进行比较 => 将比较操作加入for循环: 因已排好序而不用遍历比较到底, 所以条件不符合时, 后续也不会有符合的情况, 可直接中断循环
            for(int j = i - 1; (j >= 0) && (min2max ? (array[j] > v) : (array[j] < v)); j--)
            {
                // 较大/较小数组元素后移
                array[j + 1] = array[j];
                // 更新插入位置下标
                mark = j;
            }

            // 本次排序的数组元素下标与标记元素下标不一致时, 将本次排序的数组元素值放入插入位置下标
            if(mark != i)
            {
                array[mark] = v;
            }
        }
    }

    // 冒泡排序函数(稳定) => 每次比较相邻的两个数组元素值, 较大/较小的进行移动
    template <typename T>
    static void Bubble(T array[], int size, bool min2max = true)
    {
        // 交换标记
        bool exchang = true;

        // 如果进行遍历完毕而没有发生交换, 说明数组已经是排序好的状态, 无需再进行排序遍历
        for(int i = 0; (i < size) && exchang; i++)
        {
            // 设置为false, 表明交换次数为0
            exchang = false;

            // 每一次遍历排序, 都完成至少一个数组为元素的有序, 所以需要减i次
            for(int j = 0; j < size - 1 - i; j++)
            {
                // 每次比较相邻的两个数组元素值, 较大/较小的进行交接, 并设置交换标记为true
                if(min2max ? (array[j] > array[j + 1]) : (array[j] < array[j + 1]))
                {
                    // 较大/较小数组元素交换
                    Swap(array[j], array[j + 1]);
                    // 发生了交换, 设置为true
                    exchang = true;
                }
            }
        }
    }

    // 打印数组元素
    template <typename T>
    static void print_array(T array[], int size)
    {
        for(int i = 0; i < size; i++)
        {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};

}

#endif // SORT_H
