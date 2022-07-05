#ifndef SORT_H
#define SORT_H

#include <iostream>

#include "Exception.h"

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

    // 归并排序子函数 => 归并(使用begin、end记录数组下标, 在不断递归的过程中, begin、end不断变化, 直至begin==end时结束递归而开始回溯; 回溯时把begin、end分割的数组元素归并: 排序并赋值给辅助数组, 然后再赋值给原数组)
    template <typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool min2max)
    {
        // 当begin==end时(只有一个数组元素时不需要排序), 为最小颗粒, 作为出口并开始回溯
        if(begin < end)
        {
            int mid = (begin + end) / 2;

            // 分解数组, 直至begin==end时跳出
            Merge(src, helper, 0, mid, min2max);
            Merge(src, helper, mid + 1, end, min2max);

            // 将上面分解的数组元素排序, 并且合并
            Merge(src, helper, begin, mid, end, min2max);
        }
    }
    // 归并排序子函数 => 排序与合并
    template <typename T>
    static void Merge(T src[], T helper[], int begin, int mid, int end, bool min2max)
    {
        // 原数组的前半段元素下标(begin)
        int i = begin;
        // 原数组的后半段元素下标(mid + 1)
        int j = mid + 1;
        // 辅助函数的元素下标(begin), 与原数组的元素下标(begin)相等对称
        int k = begin;

        // 任意半段结束时, 比较赋值结束(剩下的另半段数组元素在该段内是有序的)
        while((i <= mid) && (j <= end))
        {
            //  原数组的前半段和后半段元素值比较, 较小/较大的先进入辅助数组
            if(min2max ? (src[i] > src[j]) : (src[i] < src[j]))
            {
                helper[k++] = src[j++];
            }
            else
            {
                helper[k++] = src[i++];
            }
        }

        // 前半段剩余, 直接赋值给辅助数组, 因剩下的半段数组元素在该段内是有序的, 所以不用排序直接赋值
        while(i <= mid)
        {
            helper[k++] = src[i++];
        }

        // 后半段剩余, 直接赋值给辅助数组, 因剩下的半段数组元素在该段内是有序的, 所以不用排序直接赋值
        while(j <= end)
        {
            helper[k++] = src[j++];
        }

        // 将排好序的辅助数组元素值赋给原数组, 注意保存元素的下标要对称
        for(i = begin; i <= end; i++)
        {
            src[i] = helper[i];
        }
    }

    // 快速排序子函数 => 使用数组任意元素分割数组, 不断递归, 直至数组元素有序
    template <typename T>
    static void Quick(T array[], int begin, int end, bool min2max)
    {
        if(begin < end)
        {
            // 获取排序后的基准下标
            int pivot = Partition(array, begin, end, min2max);

            // 对基准两侧数组元素排序
            Quick(array, 0, pivot, min2max);
            Quick(array, pivot + 1, end, min2max);
        }
    }
    // 快速排序子函数 => 使用数组任意元素分割数组, 较小/较大在一边, 较大/较小在另一边, 不断递归, 直至基准元素至头尾, 则排序完毕
    template <typename T>
    static int Partition(T array[], int begin, int end, bool min2max)
    {
        // 基准值
        T pv = array[begin];

        // 当begin==end时, 说明数组遍历结束, 结束排序
        while(begin < end)
        {
            // 先比较尾标记数组元素, 较大/较小时, 说明排序完毕, 尾标记前移
            while(min2max ? (array[end] > pv) : (array[end] < pv))
            {
                end--;
            }

            // 将排序好的元素放在基准元素一侧(基准元素和尾标记(end)元素交换, 保证基准元素一直在中, 并为与前标记元素比较做准备)
            Swap(array[begin], array[end]);

            // 尾标记可能前移而等于前标记, 所以需要保证它们的大小于关系; 比较前标记数组元素后, 前标记前移
            while((begin < end) && (min2max ? (array[begin] <= pv) : (array[begin] >= pv)))
            {
                begin++;
            }

            // 将排序好的元素放在基准元素另一侧(基准元素和前标记(begin)元素交换, 保证基准元素一直在中, 并为与后标记元素比较做准备)
            Swap(array[begin], array[end]);
        }

        // 当前后标记相等时, 说明整个数组排序完毕
        if(begin == end)
        {
            return begin;
        }
        else
        {
            THROW_EXCEPTION(ArithmeticException, "begin != end...");
        }
    }

public:

    // 选择排序函数(不稳定, O(n^2))> => 获取最小/最大值的坐标, 然后进行交换
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

    // 插入排序函数(稳定, O(n^2)) => 使用未排序的数组元素, 与排序好的数组元素进行比较后插入
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

    // 冒泡排序函数(稳定, O(n^2)) => 每次比较相邻的两个数组元素值, 较大/较小的进行移动
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

    // 希尔排序(不稳定, O(n^(3/2))) => 将待排序列划分若干组，在每一组内进行插入排序，以使整个序列基本有序，然后再对整个序列进行插入排序
    template <typename T>
    static void Shell(T array[], int size, bool min2max = true)
    {
        int d = size;

        do
        {
            d = d / 3 + 1;

            // 打印d值
            //cout << "d = " << d << endl;

            for(int i = 0; i < d; i++)
            {
                for(int j = i + d; j < size; j += d)
                {
                    // 获取标记数组元素下标(插入位置下标)
                    int m = j;
                    // 获取本次排序的数组元素值
                    T v = array[m];

                    // 本次排序的数组元素值与排序好的数组元素进行比较 => 将比较操作加入for循环: 因已排好序而不用遍历比较到底, 所以条件不符合时, 后续也不会有符合的情况, 可直接中断循环
                    for(int k = j - d; (k >= 0) && (min2max ? (array[k] > v) : (array[k] < v)); k -= d)
                    {
                        // 较大/较小数组元素后移
                        array[k + d] = array[k];
                        // 更新插入位置下标
                        m = k;

                        // 打印交换位置(下标)
                        //cout << "  <" << k + d << ", " << k << ">" << endl;
                    }

                    // 本次排序的数组元素下标与标记元素下标不一致时, 将本次排序的数组元素值放入插入位置下标
                    if(m != j)
                    {
                        array[m] = v;
                    }
                }
            }

            /* 这个排序只需要前几次让数组基本有序即可, 没必要完全按照思想做, 因此, 可使用以下代码
            // 打印d值
            //cout << "d = " << d << endl;

            for(int i = d; i < size; i += d)
            {
                // 获取标记数组元素下标(插入位置下标)
                int k = i;
                // 获取本次排序的数组元素值
                T e = array[i];

                // 本次排序的数组元素值与排序好的数组元素进行比较 => 将比较操作加入for循环: 因已排好序而不用遍历比较到底, 所以条件不符合时, 后续也不会有符合的情况, 可直接中断循环
                for(int j = i - d; (j >= 0) && (min2max ? (array[j] > e) : (array[j] < e)); j -= d)
                {
                    // 较大/较小数组元素后移
                    array[j + d] = array[j];
                    // 更新插入位置下标
                    k = j;

                    // 打印交换位置(下标)
                    //cout << "  <" << j + d << ", " << j << ">";
                }

                // 本次排序的数组元素下标与标记元素下标不一致时, 将本次排序的数组元素值放入插入位置下标
                if(k != i)
                {
                    array[k] = e;
                }
            }
            //cout << endl;
            */
            // 打印单轮排序后的数组
            //cout << " => ";
            //print_array(array, len);

        } while(d > 1);
    }

    // 归并排序(稳定, O(n*logn)) => 将数组元素不断分割, 然后排序合并
    template <typename T>
    static void Merge(T array[], int size, bool min2max = true)
    {
        // 辅助数组, 保存已经排好序的数组元素(相当于swap的temp), 然后再把数组元素给原数组赋值
        T* helper = new T[size];

        if(helper != NULL)
        {
            // 归并排序
            Merge(array, helper, 0, size - 1, min2max);
        }

        // 释放辅助数组内存空间
        delete[] helper;
    }

    // 快速排序(不稳定, O(n*logn)) => 使用数组任意元素分割数组, 较小/较大在一边, 较大/较小在另一边, 不断递归, 直至基准元素至头尾, 则排序完毕
    template <typename T>
    static void Quick(T array[], int size, bool min2max = true)
    {
        Quick(array, 0, size - 1, min2max);
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
