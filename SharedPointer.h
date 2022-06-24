#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"

namespace DemoData
{

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;

public:
    SharedPointer(T* = NULL);
    SharedPointer(const SharedPointer<T>&);

    SharedPointer<T>& operator =(const SharedPointer<T>&);

    bool operator ==(const SharedPointer<T>&);

    void clear();
    void assign(const SharedPointer<T>&);

    ~SharedPointer();
};

// 构造函数
template <typename T>
SharedPointer<T>::SharedPointer(T* p) : m_ref(NULL)
{
    // 判断指针对象是否为空
    if(p)
    {
        // 开辟计数成员指针空间
        m_ref = static_cast<int*>(malloc(sizeof(int)));

        if(m_ref)
        {
            this->m_pointer = p;
            *(this->m_ref) = 1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough to create sharedPointer object...");
        }
    }
}

// 拷贝构造函数
template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& obj)
{
    assign(obj);
}

// 赋值操作符
template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& obj)
{
    if(this != &obj)
    {
        clear();

        assign(obj);
    }
}

// 比较函数
template <typename T>
bool SharedPointer<T>::operator==(const SharedPointer<T>& obj)
{
    return (this->m_pointer == obj.m_pointer);
}

// 清理函数
template <typename T>
void SharedPointer<T>::clear()
{
    T* toDel = this->m_pointer;
    int* ref = this->m_ref;

    this->m_pointer = NULL;
    this->m_ref = NULL;

    // 判断是否还有其它指针对象
    if(ref)
    {
        (*ref)--;

        // 不存在其它指针对象指向相同
        if(!*ref)
        {
            delete toDel;
            free(ref);
        }
    }
}

// 自定义赋值函数
template <typename T>
void SharedPointer<T>::assign(const SharedPointer<T>& obj)
{
    // 指针对象指针赋值
    this->m_pointer = obj.m_pointer;
    this->m_ref = obj.m_ref;

    // 更新计数, 加1
    if(this->m_ref)
    {
        *(this->m_ref)++;
    }
}

// 析构函数
template <typename T>
SharedPointer<T>::~SharedPointer()
{
    clear();
}

}

#endif // SHAREDPOINTER_H
