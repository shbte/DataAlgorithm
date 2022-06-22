#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"

namespace DemoData
{

/*
StaticArray设计要点
类模板
    封装原生数组
    使用模板参数决定数组大小
    实现函数返回数组长度
    拷贝构造和赋值操作
 */
template <typename T, int N>
class StaticArray : public Array<T>
{
protected:
    T m_space[N];

public:
    StaticArray()
    {
        this->m_array = m_space;
    }

    // 拷贝构造函数
    StaticArray(const StaticArray<T, N>& obj)
    {
        // 数组地址赋值
        this->m_array = m_space;

        // 数组元素拷贝赋值
        for(int i = 0; i < N; i++)
        {
            this->m_space[i] = obj.m_space[i];
        }
    }
    // 赋值操作符
    StaticArray<T, N>& operator =(const StaticArray<T, N>& obj)
    {
        if(this != &obj)
        {
            // 数组元素拷贝赋值
            for(int i = 0; i < N; i++)
            {
                this->m_space[i] = obj.m_space[i];
            }
        }
    }
    // 获取数组长度
    int length() const
    {
        return N;
    }
};

}

#endif // STATICARRAY_H
