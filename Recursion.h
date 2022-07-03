#ifndef RECURSION_H
#define RECURSION_H

#include "Object.h"

namespace DemoData
{

struct Node : public Object
{
    int value;
    Node* next;
};

// 以递归的方式求字符串长度
int _strlen_(const char* s);

// 创建链表
Node* create_list(int v, int len);
// 释放链表空间
void destroy_list(Node* list);
// 打印链表
void print_list(Node* list);

// 反转链表
Node* reverse(Node* list);
// 合并链表
Node* merge(Node* list1, Node* list2);

// 汉诺塔移动问题
void HanoiTower(int n, char a, char b, char c);
// 全排列的递归解法
void permutation(char* s, char* begins);
// 逆序打印单链表中值为偶数的节点
void r_print_even(Node* list);

}

#endif // RECURSION_H
