
#include <iostream>

#include "Recursion.h"

using namespace std;

// 第一种命名空间函数绑定方式: namespace DemoData{ xxx } 中直接实现
namespace DemoData
{

// 以递归的方式求字符串长度
int _strlen_(const char* s)
{
    /*
    if(*s != '\0')
    {
        return (1 + _strlen_(s + 1));
    }
    else
    {
        return 0;
    }
    */

    //return (s ? ((*s != '\0') ? (1 + _strlen_(s + 1)) : 0) : 0);
    return (s ? (*s ? (1 + _strlen_(s + 1)) : 0) : 0);
}

// 创建链表
Node* create_list(int v, int len)
{
    Node* ret = NULL;
    Node* slider = NULL;

    for(int i = 0; i < len; i++)
    {
        Node* n = new Node();

        n->value = v++;
        n->next = NULL;

        if(slider == NULL)
        {
            slider = n;
            ret = n;
        }
        else
        {
            slider->next = n;
            slider = n;
        }
    }

    return ret;
}
// 释放链表空间
void destroy_list(Node* list)
{
    while(list)
    {
        Node* del = list;

        list = list->next;

        delete del;
    }
}

// 合并链表
Node* merge(Node* list1, Node* list2)
{
    if(list1 == NULL)
    {
        return list2;
    }
    else if(list2 == NULL)
    {
        return list1;
    }
    else if(list1->value > list2->value)
    {
        /*
        Node* ret = list1;

        list1->next = merge(list1->next, list2);

        return ret;
        */
        return (list1->next = merge(list1->next, list2), list1);
    }
    else
    {
        /*
        Node* ret = list2;

        list2->next = merge(list1, list2->next);

        return ret;
        */
        return (list2->next = merge(list1, list2->next), list2);
    }
}

// 汉诺塔移动问题 (a => src, b => middle, c => dest)
void HanoiTower(int n, char a, char b, char c)
{
    if(n == 1)
    {
        cout << a << " ==> " << c << " ";
    }
    else
    {
        // 把(n-1)的木块, a ==> b
        HanoiTower(n - 1, a, c, b);
        // 把最下面的木块, a ==> c
        HanoiTower(1, a, b, c);
        // 把(n-1)的木块, b ==> c
        HanoiTower(n - 1, b, a, c);
    }
}
// 全排列的递归解法
void permutation(char* s, char* begins)
{
    if(*s == '\0')
    {
        cout << begins << " ";
    }
    else
    {
        int len = _strlen_(s);

        for(int i = 0; i < len; i++)
        {
            if((i == 0) || (s[0] != s[i]))
            {
                swap(s[0], s[i]);
                permutation(s + 1, begins);
                swap(s[0], s[i]);
            }
        }
    }
}
// 逆序打印单链表中值为偶数的节点
void r_print_even(Node* list)
{
    if(list != NULL)
    {
        r_print_even(list->next);

        if((list->value % 2) == 0)
        {
            cout << "->" << list->value;
        }
    }
}

}

// 第二种命名空间绑定函数方式: 使用DemoData::来指定特定命名空间, 以此来绑定函数实现
void DemoData::print_list(Node* list)
{
    while(list)
    {
        cout << list->value << "->";

        list = list->next;
    }
    cout << "NULL" << endl;
}

// 反转链表
DemoData::Node* DemoData::reverse(DemoData::Node* list)
{
    if((list == NULL) || (list->next == NULL))
    {
        return list;
    }
    else
    {
        Node* guard = list->next;
        Node* ret = reverse(list->next);

        guard->next = list;
        list->next = NULL;

        return ret;
    }
}
