#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace DemoData
{
template <typename T>
class SeqList : public List<T>
{
protected:
    T* m_array; // 顺序存储空间
    int m_length; // 当前线性表长度

public:
    virtual bool insert(const T& e);
    virtual bool insert(int i, const T& e);
    virtual bool remove(int i);
    virtual bool set(int i, const T& e);
    virtual bool get(int i, T& e) const;
    virtual int length() const;
    virtual void clear();
    int find(const T& e) const;

    // 顺序存储线性表的数组访问方式
    T& operator [](int i);
    T operator [](int i) const;
    // 顺序存储空间的容量
    virtual int capacity() const = 0;
};
template <typename T>
bool SeqList<T>::insert(const T& e)
{
    return insert(m_length, e);
}
template <typename T>
bool SeqList<T>::insert(int i, const T& e)
{
    // 判断目标位置是否合法
    bool ret = ((0 <= i) && (i <= m_length));
    ret = ret && ((m_length + 1) <= capacity());

    if(ret)
    {
        // 将目标位置之后的所有元素后移一个位置
        for(int index = m_length - 1; index >= i; index--)
        {
            m_array[index + 1] = m_array[index];
        }

        // 将新元素插入目标位置
        m_array[i] = e;
        // 线性表长度加1
        m_length++;
    }
    return ret;
}

template <typename T>
bool SeqList<T>::remove(int i)
{
    // 判断位置是否合法
    bool ret = ((0 <= i) && (i < m_length));

    if(ret)
    {
        // 将目标位置后的所有元素前移一个位置
        for(int index = i; index < m_length - 1; index++)
        {
            m_array[index] = m_array[index + 1];
        }
        // 线性表长度减1
        m_length--;
    }
    return ret;
}

template <typename T>
bool SeqList<T>::set(int i, const T& e)
{
    // 判断位置是否合法
    bool ret = ((0 <= i) && (i < m_length));

    if(ret)
    {
        // 将目标位置作为数组下标设置元素
        m_array[i] = e;
    }
    return ret;
}

template <typename T>
bool SeqList<T>::get(int i, T& e) const
{
    // 判断位置是否合法
    bool ret = ((0 <= i) && (i < m_length));

    // 将目标位置作为数组下标获取元素
    if(ret)
    {
        e = m_array[i];
    }
    return ret;
}

template <typename T>
int SeqList<T>::length() const
{
    return m_length;
}

template <typename T>
void SeqList<T>::clear()
{
    m_length = 0;
}

template <typename T>
int SeqList<T>::find(const T& e) const
{
    int ret = -1;

    for(int i = 0; i < m_length; i++)
    {
        if(m_array[i] == e)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

template <typename T>
T& SeqList<T>::operator [](int i)
{
    // 判断位置是否合法
    bool ret = ((0 <= i) && (i < m_length));

    if(ret)
    {
        return m_array[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Array index out of bounds.");
    }
}

template <typename T>
T SeqList<T>::operator [](int i) const
{
    return (const_cast<SeqList<T> &>(*this))[i];
}

}

#endif // SEQLIST_H
