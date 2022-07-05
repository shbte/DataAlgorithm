#ifndef ARRAY_H
#define ARRAY_H

#include "Exception.h"

namespace DemoData
{

/*
Array设计要点
    抽象类模板, 存储空间的位置和大小由子类完成
    重载数组操作符, 判断访问下标是否合法
    提供数组长度的抽象访问函数
    提供数组对象间的复制操作
 */
template <typename T>
class Array : public Object
{
protected:
    T* m_array;

public:
    virtual bool set(int i, const T& e)
    {
        // 判断位置是否合法
        bool ret = ((0 <= i) && (i < length()));

        if(ret)
        {
            m_array[i] = e;
        }
        return ret;
    }
    virtual bool get(int i, T& e) const
    {
        // 判断位置是否合法
        bool ret = ((0 <= i) && (i < length()));

        if(ret)
        {
            e = m_array[i];
        }
        return ret;
    }
    virtual int length() const = 0;

    // 数组访问操作符
    T& operator [](int i)
    {
        if((0 <= i) && (i < length()))
        {
            return m_array[i];
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Array index out of bounds...");
        }
    }
    T operator [](int i) const
    {
        return (const_cast<Array<T> &>(*this))[i];
    }

    // 返回数组指针
    T* array() const
    {
        return m_array;
    }
};

}

#endif // ARRAY_H
