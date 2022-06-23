#ifndef STATICLIST_H
#define STATICLIST_H

#include "SeqList.h"

namespace DemoData
{

/*
StaticList设计要点
类模板
    使用原生数组作为顺序存储空间
    使用模板参数决定数组大小
 */
template <typename T, int N>
class StaticList : public SeqList<T>
{
protected:
    T m_space[N]; // 顺序存储空间, N 为模板参数

public:
    StaticList() // 指定父类成员的具体值
    {
        this->m_array = m_space;
        this->m_length = 0;
    }

    int capacity() const
    {
        return N; // 顺序存储空间大小由创建时指定, 后续不可更改
    }
};

}

#endif // STATICLIST_H
