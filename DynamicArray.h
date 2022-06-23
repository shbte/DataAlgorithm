#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"

namespace DemoData
{

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;

    // 对象构造时的初始化操作
    void init(T* array, int len)
    {
        if(array != NULL)
        {
            this->m_array = array;
            this->m_length = len;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat DynamicArray object...");
        }
    }

    // 在堆空间中申请新的内存, 并执行拷贝操作
    T* copy(T* array, int len, int newLen)
    {
        // 重新创建对象数组, 实现深拷贝
        T* ret = new T[newLen];

        if(array != NULL)
        {
            int nCount = (len > newLen ? newLen : len);

            // 新数组对象元素赋值
            for(int i = 0; i < nCount; i++)
            {
                ret[i] = array[i];
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to copy DynamicArray object...");
        }

        return ret;
    }

    // 将指定的堆空间作为内部存储数组使用
    void update(T* array, int len)
    {
        // 指向旧数组的堆空间
        T* temp = this->m_array;

        // 新成员值设置
        this->m_array = array;
        this->m_length = len;

        // 释放旧数组指向的堆空间
        delete[] temp;
    }

public:
    DynamicArray(int length = 0)
    {
        init(new T[length], length);
    }

    // 拷贝构造函数
    DynamicArray(const DynamicArray<T>& obj)
    {
        update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }

    // 赋值操作符
    DynamicArray<T>& operator =(const DynamicArray<T>& obj)
    {
        if(this != &obj)
        {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }

        return *this;
    }

    // 获取数组长度
    int length() const
    {
        return m_length;
    }

    // 动态重置数组空间
    void resize(int length)
    {
        if(m_length != length)
        {
            update(copy(this->m_array, m_length, length), length);
        }
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};

}

#endif // DYNAMICARRAY_H
