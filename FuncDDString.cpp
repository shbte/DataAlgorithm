#include "FuncDDString.h"

#include <cstring>
#include <iostream>

#include "DDString.h"
#include "Exception.h"
#include "Recursion.h"

using namespace std;
using namespace DemoData;

void func001()
{
    cout << "func01: DDString " << endl;

    String s;

    s = 'D';

    cout << s.str() << endl;    // D
    cout << s.length() << endl; // 1
    cout << (s == "D") << endl; // 1
    cout << (s > "CCC") << endl;    // 1

    s += " Delphi Tang ";

    cout << s.str() << endl;    // D Delphi Tang
    cout << s.length() << endl; // 14
    cout << (s == "D Delphi Tang ") << endl;    // 1
    cout << (s == "D Delphi Tang") << endl;     // 0

    String a[] = {"E", "D", "C", "B", "A"};
    String min = a[0];

    int size = (sizeof(a) / sizeof(a[0]));
    for(int i = 0; i < size; i++)
    {
        if(min > a[i])
        {
            min = a[i];
        }
    }
    cout << "min = " << min.str() << endl;  // min = A
}

void func002()
{
    cout << "func002: DDString " << endl;

    const String cs = "D Delphi Tang ";
    for(int i = 0; i < cs.length(); i++)
    {
        cout << cs[i];  // D Delphi Tang
    }
    cout << endl;

    String s;
    s = "D.T.Software...";

    try
    {
        for(int i = 0; i < s.length(); i++)
        {
            cout << s[i];   // D.T.Software...
        }
        cout << endl;
    }
    catch(const Exception& e)
    {
        cout << e.message() << endl;
        cout << e.location() << endl;
    }

    cout << s.startWith("D.T.Software...") << endl; // 1
    cout << s.startWith("D") << endl;               // 1
    cout << s.startWith("D.T.software...") << endl; // 0
    cout << s.endOf("D.T.Software...") << endl;     // 1
    cout << s.endOf("..") << endl;                  // 1
    cout << s.endOf("D.T.software...") << endl;     // 0

    String snull = "   ";
    cout << snull.startWith(" ") << endl;   // 1
    cout << snull.startWith("1") << endl;   // 0
    cout << snull.endOf(" ") << endl;       // 1
    cout << snull.endOf("1") << endl;       // 0

    cout << s.str() << endl;    // D.T.Software...
    s.insert(1, " insert ");
    cout << s.str() << endl;    // D. insert .T.Software..

    s = " abc   ";

    if(s.trim().insert(0, "D.T.").endOf("abc") && s.startWith("D.T"))
    {
        cout << s.str() << endl;    // D.T.abc
    }

    s = " ";
    try
    {
        cout << s.trim().str() << endl;
    }
    catch(const Exception& e)
    {
        cout << e.message() << endl;    // parameter s is Invalid...
        cout << e.location() << endl;   // ..\DemoData\DDString.cpp:188
    }
}

// 字符串匹配表
int* make_pmt(const char* s)
{
    int len = strlen(s);
    int* ret = reinterpret_cast<int*>(malloc(sizeof(int) * len));

    if(ret)
    {
        ret[0] = 0;
        // 最大匹配长度(longest length) ==> index + 1
        int ll = ret[0];

        for(int i = 1; i < len; i++)
        {
            // 匹配不成功 ==> 匹配长度>0, 且扩展字符不匹配时, 匹配回退, 重新寻找前字符(ll-1)最大匹配长度和扩展字符进行匹配
            while((ll > 0) && (s[ll] != s[i]))
            {
                ll = ret[ll - 1];
            }

            // 匹配成功 ==> 最优情况, 扩展字符刚好匹配; 当ll==0时, 为首尾单个元素匹配(只匹配第一个和最后一个元素)
            if(s[ll] == s[i])
            {
                ll++;
            }

            ret[i] = ll;
        }
    }

    return ret;
}
// KMP字符串匹配查找算法(获取匹配字符串的头下标)
int kmp(const char* s, const char* p)
{
    int ret = -1;
    int slen = strlen(s);
    int plen = strlen(p);
    int* pmt = make_pmt(p);

    if((pmt != NULL) && (0 < plen) && (plen <= slen))
    {
        for(int si = 0, pi = 0; si < slen; si++)
        {
            // 当pi=0时, 前匹配成功数为0, 不需要减少位移数(左移)
            while((pi > 0) && (s[si] != p[pi]))
            {
                // -1是只获取匹配不成功前字符的最大匹配长度(pi位置已经匹配失败)
                pi = pmt[pi - 1];
            }

            // 元素匹配成功时, 进行下一元素比较
            if(s[si] == p[pi])
            {
                pi++;
            }

            // 匹配结束, 获取下表并结束循环
            if(pi == plen)
            {
                ret = si + 1 - plen;
                break;
            }
        }
    }

    free(pmt);

    return ret;
}
void func003()
{
    cout << "func003: " << endl;

    String s = "ABCDABD";
    int* pmt = make_pmt(s.str());

    for(int i = 0; i < s.length(); i++)
    {
        /*
        0 : 0
        1 : 0
        2 : 0
        3 : 0
        4 : 1
        5 : 2
        6 : 0
        */
        cout << i << " : " << pmt[i] << endl;
    }

    cout << kmp(s.str(), "CD") << endl;         // 2
    cout << kmp(s.str(), "CD") << endl;         // 2
    cout << kmp(s.str(), "CDE") << endl;        // -1
    cout << kmp(s.str(), "ABCDABD") << endl;    // 0

    free(pmt);
}

void func004()
{
    cout << "func004: " << endl;

    String s = "D.T.Software";

    cout << s.indexOf(String("D.")) << endl;            // 0
    cout << s.indexOf(String(".T.")) << endl;           // 1
    cout << s.indexOf(String("re")) << endl;            // 10
    cout << s.indexOf(String("D.T.Software")) << endl;  // 0

    cout << s.remove(String("D.")).str() << endl;       // T.Software
    cout << s.remove(String(".S")).str() << endl;       // Toftware
    cout << s.remove(String("re")).str() << endl;       // Toftwa
    cout << s.remove(String("Toftwa")).str() << endl;   //

    s = "D.T.Software";
    cout << (s - String("D.")).str() << endl;           // T.Software
    cout << (s - String(".S")).str() << endl;           // D.Toftware
    cout << (s - String("re")).str() << endl;           // D.T.Softwa
    cout << (s - String("D.T.Software")).str() << endl; //

    cout << s.replace("D.", "D..").str() << endl;                       // D..T.Software
    cout << s.replace(".S", ".S.").str() << endl;                       // D..T.S.oftware
    cout << s.replace("re", "re.").str() << endl;                       // D..T.S.oftware.
    cout << s.replace("D..T.S.oftware.", "D.T.Software").str() << endl; // D.T.Software

    cout << (s.sub(0, 1)).str() << endl;    // D
    cout << (s.sub(11, 1)).str() << endl;   // e
    cout << (s.sub(4, 14)).str() << endl;   // Software
    cout << (s.sub(0, 20)).str() << endl;   // D.T.Software
}

void func005()
{
    cout << "func005: " << endl;

    String s = "D.T.Software.";

    cout << _strlen_(s.str()) << endl;  // 13

    Node* list1 = create_list(1, 5);
    Node* list2 = create_list(3, 12);

    // 打印链表
    print_list(list1);  // 1->2->3->4->5->NULL
    print_list(list2);  // 3->4->5->6->7->8->9->10->11->12->13->14->NULL

    // 反转链表, 后打印
    list1 = reverse(list1);
    print_list(list1);  // 5->4->3->2->1->NULL

    // 链表合并
    Node* merge_list = merge(list1, list2);
    print_list(merge_list); // 5->4->3->4->5->6->7->8->9->10->11->12->13->14->3->2->1->NULL

    // 逆序打印单链表中值为偶数的节点
    r_print_even(merge_list);   // ->2->14->12->10->8->6->4->4
    cout << endl;

    // destroy_list(list1);
    // destroy_list(list2);
    // 释放list1和list2的内存空间 (因为list1和list2已经合并, 有可能释放其中一个时, 另一个也被释放, 造成重复释放错误, 从而使用merge_list来释放list1和list2的内存空间)
    destroy_list(merge_list);

    // 汉诺塔移动问题
    HanoiTower(1, 'a', 'b', 'c');   // a ==> c
    cout << endl;
    HanoiTower(2, 'a', 'b', 'c');   // a ==> b a ==> c b ==> c
    cout << endl;
    HanoiTower(3, 'a', 'b', 'c');   // a ==> c a ==> b c ==> b a ==> c b ==> a b ==> c a ==> c
    cout << endl;

    char cs[] = "acc";
    // 全排列的递归解法
    permutation(cs, cs);    // acc cac cca cca cac
    cout << endl;
}
