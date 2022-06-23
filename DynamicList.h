#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace DemoData
{

/*
Static设计要点
类模板
    申请连续堆空间作为顺序存储空间
    动态设置顺序存储空间大小
    保证重置顺序存储空间时的异常安全性
函数异常安全的概念
    不泄露异常安全的概念
    不允许破坏数据
函数异常安全的基本保证
    如果异常被抛出
        对象内的任何成员仍然能保持有效状态
        没有数据的破坏及资源泄露
 */
template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity; // 顺序存储空间大小

public:
    // 申请空间
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];
        this->m_length = 0;
        m_capacity = capacity;
    }

    // 获取顺序存储空间容量
    int capacity() const
    {
        return m_capacity;
    }

    // 重新设置顺序存储空间大小
    void resize(int capacity)
    {
        // 判断重置空间大小是否一致
        if(m_capacity != capacity)
        {
            // 创建新的顺序存储空间
            T* array = new T[capacity];
            // 新顺序存储空间成功
            if(array != NULL)
            {
                // 获取新顺序存储空间应存储的元素个数
                int nCount = (capacity > this->m_length ? this->m_length : capacity);

                // 对新顺序存储空间元素进行拷贝赋值
                for(int i = 0; i < nCount; i++)
                {
                    array[i] = this->m_array[i];
                }
                // 创建临时指针, 指向旧顺序存储空间
                T* temp = this->m_array;

                // 设置新顺序存储空间成员属性
                this->m_array = array;
                this->m_length = nCount;
                this->m_capacity = capacity;

                // 释放旧顺序存储空间(保证异常安全)
                delete[] temp;
                // temp = NULL;
                // array = NULL;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicList Object...");
            }
        }
    }

    // 归还空间
    ~DynamicList()
    {
        delete[] this->m_array;
    }
};

}

#endif // DYNAMICLIST_H
