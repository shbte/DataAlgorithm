#ifndef LIST_H
#define LIST_H

#include "Object.h"
#include <iostream>

using namespace std;

/*
线性表(List)的表现形式
    零个或多个数据元素组成的集合
    数据元素在位置上是有序排列的
    数据元素的个数是有限的
    数据元素的类型必须相同

小结:
    线性表是数据元素的有序并且有限的集合
    线性表中的数据元素必须是类型相同
    线性表可用于描述排队关系的问题
    线性表在程序中表现为一种特殊的数据类型
    线性表在C++中表现为一个抽象类

顺序表: StaticList, DynamicList
    基于顺序存储结构的线性表
链表: LinkList
    基于链式存储结构的线性表
        单链表: 每个节点只包含直接后继节点的地址信息
        循环链表: 单链表中的最后一个节点的直接后继节点为第一个节点
        双向链表: 单链表中的节点包含直接前驱和后继节点的地址信息

效率的深度分析
    插入和删除
        顺序表: 涉及大量数据对象的赋值操作
        单链表: 只设计指针操作, 效率与数据对象无关
    访问操作
        顺序表: 随机访问, 可直接定位数据对象
        单链表: 顺序访问, 必须从头访问数据对象, 无法直接定位

    实际工程开发中, 时间复杂度只是效率的一个参考指标
        对于内置基础类型, 顺序表和单链表的效率不相上下
        对于自定义类类型, 顺序表在效率上低于单链表

工程开发中的选择
    顺序表
        数据元素的类型相对简单, 不涉及深拷贝
        数据元素相对稳定, 访问操作远多于插入和删除操作
    单链表
        数据元素的类型相对复杂, 复制操作相对耗时
        数据元素不稳定, 需要经常插入和删除, 访问操作较少
*/
namespace DemoData
{

template <typename T>
class List : public Object
{
protected:
    List(const List&); // 拷贝构造函数保护化以后, 需要手动提供公有的构造函数(不提供则没有)
    List& operator =(const List&);

public:
    List()
    {
        // cout << "List::List()" << endl;
    }
    virtual bool insert(const T& e) = 0;
    virtual bool insert(int i, const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i, const T& e) = 0;
    virtual bool get(int i, T& e) const = 0;
    virtual int length() const = 0;
    virtual int find(const T& e) const = 0;
    // virtual int capacity() const = 0;
    virtual void clear() = 0;
};

}

#endif // LIST_H
