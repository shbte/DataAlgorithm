#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Object.h"

namespace DemoData
{

// 前提: 类模板要进行两次编译, 一次是类模板编译, 一次是具体类型的编译实现
// 类模板的声明和实现不可以用h和cpp分离, 因为C++是独立编译的,一个一个cpp文件进行编译, 然后在链接在一起
// 在cpp文件编译过程中, 由于是独立编译, 所以编译器是无法知道其它cpp文件是否调用了该模板(无法确定typename), 所以不会进行模板的具体类型的编译实现
template <typename T>
class SmartPointer : public Object
{
protected:
    T* m_pointer;

public:
    SmartPointer(T* p = NULL);

    SmartPointer(const SmartPointer<T>& obj);
    SmartPointer<T>& operator =(const SmartPointer<T>& obj);

    T* operator ->();
    T& operator *();

    bool isNULL();
    T* get();

    ~SmartPointer<T>();
};

template <typename T>
SmartPointer<T>::SmartPointer(T* p)
{
    m_pointer = p;
}

template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& obj)
{
    m_pointer = obj.m_pointer;
}

template <typename T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& obj)
{
    if(this != &obj)
    {
        delete m_pointer;
        m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T> &>(obj).m_pointer = NULL;
    }
    return *this;
}

template <typename T>
T* SmartPointer<T>::operator ->()
{
    return m_pointer;
}

template <typename T>
T& SmartPointer<T>::operator *()
{
    return *m_pointer;
}

template <typename T>
bool SmartPointer<T>::isNULL()
{
    return (m_pointer == NULL);
}

template <typename T>
T* SmartPointer<T>::get()
{
    return m_pointer;
}

template <typename T>
SmartPointer<T>::~SmartPointer<T>()
{
    delete m_pointer;
}

};

#endif // SMARTPOINTER_H
