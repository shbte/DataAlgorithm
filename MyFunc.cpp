#include "MyFunc.h"

#include <iostream>

#include "Object.h"
#include "Exception.h"
#include "SmartPointer.h"
#include "StaticList.h"
#include "DynamicList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "LinkList.h"
#include "StaticLinkList.h"
#include "SharedPointer.h"
#include "CircleLinkList.h"
#include "DualLinkList.h"
#include "DualCircleLinkList.h"
#include "StaticStack.h"
#include "LinkStack.h"
#include "StaticQueue.h"

using namespace std;
using namespace DemoData;

// Object
class Test : public Object // Object::operator new(size_t size) throw()::size = 16
{
public:
    int i;
    int j;
};
class Child : public Object // Object::operator new(size_t size) throw()::size = 16
{
public:
    int k;
};
void func1()
{
    Object* obj1 = new Test();
    Object* obj2 = new Child();

    // ... ....
    cout << "obj1 = " << obj1 << endl;  // obj1 = 0x19c490f6b50
    cout << "obj2 = " << obj2 << endl;  // obj2 = 0x19c490f6b70

    delete obj1;
    delete obj2;
}

// 异常类
void func2()
{
    try
    {
        THROW_EXCEPTION(ArithmeticException, "testArithmeticException");
    }
    catch(const Exception& e)
    {
        cout << "catch(const Exception& e)" << endl;
        cout << "message : " << e.message() << endl;    // message : testArithmeticException
        cout << "location : " << e.location() << endl;  // location : ..\DemoData\MyFunc.cpp:41
    }
}

// 智能指针
class Base
{
public:
    Base()
    {
        cout << "Base::Base()" << endl;
    }

    ~Base()
    {
        cout << "Base::~Base()" << endl;
    }
};
void func3()
{
    cout << "func3:: SmartPointer " << endl;

    SmartPointer<Base> spb = new Base();
    SmartPointer<Base> nspb;

    cout << "spb.isNull = " << spb.isNull() << ", this = " << spb.get() << endl;      // spb.isNull = 0, this = 0x25fe2886b50
    cout << "nspb.isNull = " << nspb.isNull() << ", this = " << nspb.get() << endl;   // nspb.isNull = 1, this = 0

    nspb = spb;

    cout << "spb.isNull = " << spb.isNull() << ", this = " << spb.get() << endl;    // spb.isNULL = 1, this = 0
    cout << "nspb.isNull = " << nspb.isNull() << ", this = " << nspb.get() << endl; // nspb.isNULL = 0, this = 0x19c490f6b50
}

// 线性表
void func4()
{
    StaticList<int, 5> sl;

    for(int i = 0; i < sl.capacity(); i++)
    {
        sl.insert(i, i);
    }
    for(int i = 0; i < sl.length(); i++)
    {
        cout << "sl[" << i << "] = " << sl[i] << "    ";    // sl[0] = 0    sl[1] = 1    sl[2] = 2    sl[3] = 3    sl[4] = 4
    }
    cout << endl;

    sl[0] = sl[0] + 5;
    for(int i = 0; i < sl.length(); i++)
    {
        cout << "sl[" << i << "] = " << sl[i] << "    ";    // sl[0] = 5    sl[1] = 1    sl[2] = 2    sl[3] = 3    sl[4] = 4
    }
    cout << endl;

    try
    {
        sl[5] = 6;
    }
    catch(const Exception& e)
    {
        cout << "const Exception: " << endl;
        cout << e.message() << endl;    // Array index out of bounds.
        cout << e.location() << endl;   // ..\DemoData\SeqList.h:148
    }
    cout << endl;

    DynamicList<int> dl(5);

    for(int i = 0; i < dl.capacity(); i++)
    {
        dl.insert(i, i);
    }
    for(int i = 0; i < dl.length(); i++)
    {
        cout << "dl[" << i << "] = " << dl[i] << "    ";    // dl[0] = 0    dl[1] = 1    dl[2] = 2    dl[3] = 3    dl[4] = 4
    }
    cout << endl;

    dl[0] = dl[0] + 5;
    for(int i = 0; i < dl.length(); i++)
    {
        cout << "dl[" << i << "] = " << dl[i] << "    ";    // dl[0] = 5    dl[1] = 1    dl[2] = 2    dl[3] = 3    dl[4] = 4
    }
    cout << endl;

    try
    {
        dl[5] = 6;
    }
    catch(const Exception& e)
    {
        cout << "const Exception: " << endl;
        cout << e.message() << endl;    // Array index out of bounds.
        cout << e.location() << endl;   // ..\DemoData\SeqList.h:148
    }

    dl.resize(4);
    for(int i = 0; i < dl.length(); i++)
    {
        cout << "dl[" << i << "] = " << dl[i] << "    ";    // dl[0] = 5    dl[1] = 1    dl[2] = 2    dl[3] = 3
    }
    cout << endl;
    dl.resize(9);
    for(int i = 0; i < dl.length(); i++)
    {
        cout << "dl[" << i << "] = " << dl[i] << "    ";    // dl[0] = 5    dl[1] = 1    dl[2] = 2    dl[3] = 3
    }
    cout << endl;
    dl.insert(3, 9);
    dl.insert(9);
    for(int i = 0; i < dl.length(); i++)
    {
        cout << "dl[" << i << "] = " << dl[i] << "    ";    // dl[0] = 5    dl[1] = 1    dl[2] = 2    dl[3] = 9    dl[4] = 3    dl[5] = 9
    }
    cout << endl;
}

// 数组类
void func5()
{
    cout << "func5:: Array " << endl;

    StaticArray<int, 5> sa;

    for(int i = 0; i < sa.length(); i++)
    {
        sa[i] = i * i;
    }
    for(int i = 0; i < sa.length(); i++)
    {
        cout << "sa[" << i << "] = " << sa[i] << "   ";     // sa[0] = 0   sa[1] = 1   sa[2] = 4   sa[3] = 9   sa[4] = 16
    }
    cout << endl;
    sa.set(1, 9);
    for(int i = 0; i < sa.length(); i++)
    {
        cout << "sa[" << i << "] = " << sa[i] << "   ";     // sa[0] = 0   sa[1] = 9   sa[2] = 4   sa[3] = 9   sa[4] = 16
    }
    cout << endl;

    int value;
    sa.get(3, value);
    cout << "sa[3] = " << value << endl;    // sa[3] = 9

    cout << endl;
    DynamicArray<int> da(5);

    for(int i = 0; i < da.length(); i++)
    {
        da[i] = i * i;
    }
    for(int i = 0; i < da.length(); i++)
    {
        cout << "da[" << i << "] = " << da[i] << "   "; // da[0] = 0   da[1] = 1   da[2] = 4   da[3] = 9   da[4] = 16
    }
    cout << endl;

    DynamicArray<int> da1(10);
    da1 = da;
    for(int i = 0; i < da1.length(); i++)
    {
        cout << "da1[" << i << "] = " << da1[i] << "   ";   // da1[0] = 0   da1[1] = 1   da1[2] = 4   da1[3] = 9   da1[4] = 16
    }
    cout << endl;

    da1.resize(3);
    for(int i = 0; i < da1.length(); i++)
    {
        cout << "da1[" << i << "] = " << da1[i] << "   ";   // da1[0] = 0   da1[1] = 1   da1[2] = 4
    }
    cout << endl;

    try
    {
        da1[3] = 3;
    }
    catch(const Exception& e)
    {
        cout << "catch(const Exception& e)" << endl;
        cout << e.message() << endl;    // Array index out of bounds...
        cout << e.location() << endl;   // ..\DemoData\Array.h:57
    }

    for(int i = 0; i < da1.length(); i++)
    {
        cout << "da1[" << i << "] = " << da1[i] << "   ";   // da1[0] = 0   da1[1] = 1   da1[2] = 4
    }
    cout << endl;

    DynamicArray<DynamicArray<int>> dd;

    dd.resize(5);

    for(int i = 0; i < dd.length(); i++)
    {
        dd[i].resize(i + 1);
    }
    for(int i = 0; i < dd.length(); i++)
    {
        for(int j = 0; j < dd[i].length(); j++)
        {
            dd[i][j] = i * j;
        }
    }
    for(int i = 0; i < dd.length(); i++)
    {
        for(int j = 0; j < dd[i].length(); j++)
        {
            // dd[0][0] = 0
            // dd[1][0] = 0  dd[1][1] = 1
            // dd[2][0] = 0  dd[2][1] = 2  dd[2][2] = 4
            // dd[3][0] = 0  dd[3][1] = 3  dd[3][2] = 6  dd[3][3] = 9
            // dd[4][0] = 0  dd[4][1] = 4  dd[4][2] = 8  dd[4][3] = 12  dd[4][4] = 16
            cout << "dd[" << i << "][" << j << "] = " << dd[i][j] << "  ";
        }
        cout << endl;
    }
}

// 链表类
class LinkListBase : public Object
{
private:
    int mi = 0;

public:
    LinkListBase(int i = 0)
    {
        mi = i;
    }
    // 重载比较操作符函数(==), 实现值相等, 父类只实现地址相等
    bool operator==(const LinkListBase& obj)
    {
        return (mi == obj.mi);
    }
};
void func6()
{
    cout << "func6:: LinkList " << endl;

    LinkList<int> ll;

    for(int i = 0; i < 5; i++)
    {
        ll.insert(i, i);
    }
    for(int i = 0; i < ll.length(); i++)
    {
        cout << "ll[" << i << "] = " << ll.get(i) << "  ";  // ll[0] = 0  ll[1] = 1  ll[2] = 2  ll[3] = 3  ll[4] = 4
    }
    cout << endl;

    for(int i = 0; i < 5; i++)
    {
        ll.insert(i + 6);
    }
    for(int i = 0; i < ll.length(); i++)
    {
        cout << "ll[" << i << "] = " << ll.get(i) << "  ";  // ll[0] = 0  ll[1] = 1  ll[2] = 2  ll[3] = 3  ll[4] = 4  ll[5] = 6  ll[6] = 7  ll[7] = 8  ll[8] = 9  ll[9] = 10
    }
    cout << endl;

    ll.remove(1);
    for(int i = 0; i < ll.length(); i++)
    {
        cout << "ll[" << i << "] = " << ll.get(i) << "  ";  // ll[0] = 0  ll[1] = 2  ll[2] = 3  ll[3] = 4  ll[4] = 6  ll[5] = 7  ll[6] = 8  ll[7] = 9  ll[8] = 10
    }
    cout << endl;

    ll.set(1, 5);
    for(int i = 0; i < ll.length(); i++)
    {
        cout << "ll[" << i << "] = " << ll.get(i) << "  ";  // ll[0] = 0  ll[1] = 5  ll[2] = 3  ll[3] = 4  ll[4] = 6  ll[5] = 7  ll[6] = 8  ll[7] = 9  ll[8] = 10
    }
    cout << endl;

    ll.clear();
    try
    {
        ll.get(0);
    }
    catch(const Exception& e)
    {
        cout << "catch (const Exception& e)" << endl;
        cout << e.message() << endl;    // Paramter is invalid...
        cout << e.location() << endl;   // ..\DemoData\LinkList.h:180
    }

    for(int i = 0; i < 5; i++)
    {
        ll.insert(i, i + 5);
    }
    for(int i = 0; i < ll.length(); i++)
    {
        cout << "ll[" << i << "] = " << ll.get(i) << "  ";  // ll[0] = 5  ll[1] = 6  ll[2] = 7  ll[3] = 8  ll[4] = 9
    }
    cout << endl;

    // 意义在于把遍历输出函数的时间复杂度变小: O(n^2) ==> O(n)
    for(ll.moveInit(1, 2); !ll.end(); ll.next())
    {
        cout << ll.currentValue() << "  ";  // 6  8
    }
    cout << endl;

    cout << ll.find(7) << endl; // 2
    cout << ll.find(4) << endl; // -1

    LinkList<LinkListBase> llb;
    LinkListBase b0(0);
    LinkListBase b1(1);
    LinkListBase b2(2);
    llb.insert(b1);

    cout << llb.find(b0) << endl;   // -1
    cout << llb.find(b1) << endl;   // 0
    cout << llb.find(b2) << endl;   // -1
}

// 静态单链表
void func7()
{
    cout << "func7:: StaticLinkList " << endl;

    StaticLinkList<int, 5> sll;

    for(int i = 0; i < sll.capacity(); i++)
    {
        sll.insert(i);
    }
    for(sll.moveInit(0); !sll.end(); sll.next())
    {
        cout << sll.currentValue() << "  "; // 0  1  2  3  4
    }
    cout << endl;

    try
    {
        sll.insert(5);
    }
    catch(const Exception& e)
    {
        cout << "catch(const Exception& e)" << endl;    // catch(const Exception& e)
        cout << e.message() << endl;    // No memory to insert new Node...
        cout << e.location() << endl;   // ..\DemoData\LinkList.h:105
    }
    for(sll.moveInit(0); !sll.end(); sll.next())
    {
        cout << sll.currentValue() << "  "; // 0  1  2  3  4
    }
    cout << endl;

    for(sll.moveInit(0); !sll.end(); sll.next())
    {
        if(sll.currentValue() == 2)
        {
            sll.remove(sll.find(sll.currentValue()));
            cout << "sll[2] = " << sll.currentValue() << endl;  // sll[2] = 3
        }
    }
    for(sll.moveInit(0); !sll.end(); sll.next())
    {
        cout << sll.currentValue() << "  "; // 0  1  3  4
    }
    cout << endl;

    sll.remove(1);
    for(sll.moveInit(0); !sll.end(); sll.next())
    {
        cout << sll.currentValue() << "  "; // 0  3  4
    }
    cout << endl;
}

// 共享指针类
class SPBase
{
protected:
    int mi;
public:
    SPBase() : mi(1)
    {
        cout << "SPBase::SPBase()::mi = " << mi << endl;
    }

    void setMi(int i)
    {
        mi = i;
    }
    int getMi()
    {
        return mi;
    }

    ~SPBase()
    {
        cout << "SPBase::~SPBase()" << endl;
    }
};
void func8()
{
    cout << "func8::SharedPointer " << endl;

    SharedPointer<SPBase> sp0 = new SPBase();
    SharedPointer<SPBase> sp1 = 0;
    SharedPointer<SPBase> sp2 = NULL;
    SharedPointer<SPBase> sp3 = sp0;
    cout << "sp0.mi = " << sp0->getMi() << ", this = " << sp0.get() << ", ref = " << sp0.getRef() << endl;
    cout << "sp1.mi = " << "0" << ", this = " << sp1.get() << ", ref = " << sp1.getRef() << endl;
    cout << "sp2.mi = " << "NULL" << ", this = " << sp2.get() << ", ref = " << sp2.getRef() << endl;
    cout << "sp3.mi = " << sp3->getMi() << ", this = " << sp3.get() << ", ref = " << sp3.getRef() << endl;
    cout << endl;

    sp1 = sp0;
    sp2 = sp1;
    cout << "sp0.mi = " << sp0->getMi() << ", this = " << sp0.get() << ", ref = " << sp0.getRef() << endl;
    cout << "sp1.mi = " << sp1->getMi() << ", this = " << sp1.get() << ", ref = " << sp1.getRef() << endl;
    cout << "sp2.mi = " << sp2->getMi() << ", this = " << sp2.get() << ", ref = " << sp2.getRef() << endl;
    cout << "sp3.mi = " << sp3->getMi() << ", this = " << sp3.get() << ", ref = " << sp3.getRef() << endl;
    cout << endl;

    sp3->setMi(10);
    cout << "sp0.mi = " << sp0->getMi() << ", this = " << sp0.get() << ", ref = " << sp0.getRef() << endl;
    cout << "sp1.mi = " << sp1->getMi() << ", this = " << sp1.get() << ", ref = " << sp1.getRef() << endl;
    cout << "sp2.mi = " << sp2->getMi() << ", this = " << sp2.get() << ", ref = " << sp2.getRef() << endl;
    cout << "sp3.mi = " << sp3->getMi() << ", this = " << sp3.get() << ", ref = " << sp3.getRef() << endl;
    cout << endl;

    sp2 = 0;
    cout << "sp0.mi = " << sp0->getMi() << ", this = " << sp0.get() << ", ref = " << sp0.getRef() << endl;
    cout << "sp1.mi = " << sp1->getMi() << ", this = " << sp1.get() << ", ref = " << sp1.getRef() << endl;
    cout << "sp2.mi = " << "sp2->getMi()" << ", this = " << sp2.get() << ", ref = " << sp2.getRef() << endl;
    cout << "sp3.mi = " << sp3->getMi() << ", this = " << sp3.get() << ", ref = " << sp3.getRef() << endl;
}

// 循环链表类
void func9()
{
    cout << "func9:: CircleLinkList " << endl;

    CircleLinkList<int> cll;

    for(int i = 0; i < 5; i++)
    {
        cll.insert(0, i);
    }
    for(int i = 0; i < 5; i++)
    {
        cll.insert(i + 1);
    }

    for(int i = 0; i < cll.length(); i++)
    {
        cout << cll.get(i) << " ";  // 4 3 2 1 0 1 2 3 4 5
    }
    cout << endl;

    for(int i = 0; i < cll.length(); i++)
    {
        int mi;
        cll.get(i, mi);
        cout << mi << " ";  // 4 3 2 1 0 1 2 3 4 5
    }
    cout << endl;

    cll.remove(10);
    for(int i = 0; i < cll.length(); i++)
    {
        cout << cll.get(i) << " ";  // 3 2 1 0 1 2 3 4 5
    }
    cout << endl;
    cll.remove(0);
    for(int i = 0; i < cll.length(); i++)
    {
        cout << cll.get(i) << " ";  // 2 1 0 1 2 3 4 5
    }
    cout << endl;

    cll.clear();
    for(int i = 0; i < cll.length(); i++)
    {
        cout << cll.get(i) << " ";  //
    }
    cout << cll.find(5) << endl;    // -1

    for(int i = 0; i < 5; i++)
    {
        cll.insert(i, i);
    }
    for(int i = 0; i < 5; i++)
    {
        cll.insert(i + 1);
    }
    for(int i = 0; i < cll.length(); i++)
    {
        cout << cll.get(i) << " ";  // 0 1 2 3 4 1 2 3 4 5
    }
    cout << endl;
    cout << cll.find(-1) << endl;   // -1
    cout << cll.find(2) << endl;    // 2
    cout << cll.find(5) << endl;    // 9

    cll.clear();

    for(int i = 0; i < 41; i++)
    {
        cll.insert(i, i + 1);
    }
    for(int i = 0; i < cll.length(); i++)
    {
        cout << cll.get(i) << " ";  // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41
    }
    cout << endl;

    for(cll.moveInit(0, 2); !cll.end();)
    {
        cll.next();
        cout << cll.currentValue() << " ";  // 3 6 9 12 15 18 21 24 27 30 33 36 39 1 5 10 14 19 23 28 32 37 41 7 13 20 26 34 40 8 17 29 38 11 25 2 22 4 35 16 31
        cll.remove(cll.find(cll.currentValue()));
    }
    cout << endl;

    for(int i = 0; i < 3; i++)
    {
        cll.insert(i, i + 1);
    }
    cll.moveInit(0, 2);
    cll.next();
    while(!cll.end())
    {
        cout << cll.currentValue() << " ";  // 3 1 2
        cll.remove(cll.find(cll.currentValue()));
        cll.next();
    }
    cout << endl;
}

// 双向链表
void func10()
{
    cout << "func10:: DualLinkList " << endl;

    DualLinkList<int> dll;

    for(int i = 0; i < 5; i++)
    {
        dll.insert(0, i);
        dll.insert(i);
    }
    for(int i = 0; i < dll.length(); i++)
    {
        int e;
        dll.get(i, e);
        cout << e << " ";   // 4 3 2 1 0 0 1 2 3 4
    }
    cout << endl;

    dll.remove(1);
    for(dll.moveInit(0); !dll.end(); dll.next())
    {
        cout << dll.currentValue() << " ";  // 4 2 1 0 0 1 2 3 4
    }
    cout << endl;

    dll.clear();
    for(dll.moveInit(0); !dll.end(); dll.next())
    {
        cout << dll.currentValue() << " ";
    }

    for(int i = 0; i < 5; i++)
    {
        dll.insert(i);
        dll.insert(0, i);
        dll.insert(i, i);
    }
    for(dll.moveInit(0); !dll.end(); dll.next())
    {
        cout << dll.currentValue() << " ";  // 4 3 2 1 4 3 2 1 0 0 0 1 2 3 4
    }
    cout << endl;
    for(dll.moveInit(0, 2); !dll.end(); dll.next())
    {
        cout << dll.currentValue() << " ";  // 4 2 4 2 0 0 2 4
    }
    cout << endl;

    for(dll.moveInit(dll.length() - 1, 2); !dll.end(); dll.last())
    {
        cout << dll.currentValue() << " ";  // 4 2 4 2 0 0 2 4
    }
    cout << endl;
}

// 双向循环链表
void func11()
{
    cout << "func11:: DualCircleLinkList " << endl;

    DualCircleLinkList<int> dcll;

    for(int i = 0; i < 5; i++)
    {
        dcll.insert(i);
    }
    for(int i = 0; i < dcll.length(); i++)
    {
        int e;
        dcll.get(i, e);
        cout << e << "  ";  // 0  1  2  3  4
    }
    cout << endl;

    dcll.remove(0);
    for(int i = 0; i < dcll.length(); i++)
    {
        int e;
        dcll.get(i, e);
        cout << e << "  ";  // 1  2  3  4
    }
    cout << endl;
    dcll.set(0, 3);
    for(int i = 0; i < dcll.length(); i++)
    {
        int e;
        dcll.get(i, e);
        cout << e << "  ";  // 3  2  3  4
    }
    cout << endl;

    dcll.clear();
    cout << "length = " << dcll.length() << endl;   // length = 0

    for(int i = 0; i < 41; i++)
    {
        dcll.insert(i + 1);
    }
    for(int i = 0; i < dcll.length(); i++)
    {
        cout << dcll.get(i) << " "; // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41
    }
    cout << endl;
    int i = 0;
    for(dcll.moveInit(0, 2); !dcll.end() && i < dcll.length();)
    {
        dcll.next();
        cout << dcll.currentValue() << " "; // 3 6 9 12 15 18 21 24 27 30 33 36 39 1 5 10 14 19 23 28 32 37 41 7 13 20 26 34 40 8 17 29 38 11 25 2 22 4 35 16 31
        dcll.remove(dcll.find(dcll.currentValue()));
    }
    cout << endl;
}

void func12()
{
    cout << "func12: StaticStack " << endl;

    StaticStack<int, 9> ss;

    for(int i = 0; i < ss.capacity(); i++)
    {
        ss.push(i);
    }
    int size = ss.size();
    for(int i = 0; i < size; i++)
    {
        cout << ss.top() << " ";    // 8 7 6 5 4 3 2 1 0
        ss.pop();
    }
    cout << endl;

    ss.clear();
    for(int i = 0; i < ss.capacity(); i++)
    {
        ss.push(i + 1);
    }
    size = ss.size();
    for(int i = 0; i < size; i++)
    {
        cout << ss.top() << " ";    // 9 8 7 6 5 4 3 2 1
        ss.pop();
    }
    cout << endl;
}

void func13()
{
    cout << "func13: LinkStack " << endl;

    LinkStack<int> ls;

    for(int i = 0; i < 5; i++)
    {
        ls.push(i);
    }
    int size = ls.size();
    for(int i = 0 ; i < size; i++)
    {
        cout << ls.top() << " ";    // 4 3 2 1 0
        ls.pop();
    }
    cout << endl;

    ls.push(5);
    size = ls.size();
    for(int i = 0 ; i < size; i++)
    {
        cout << ls.top() << " ";
        ls.pop();
    }
    cout << endl;

    ls.push(10);
    ls.clear();
    size = ls.size();
    for(int i = 0 ; i < size; i++)
    {
        cout << ls.top() << " ";
    }
    cout << endl;

    bool Symbol_Math(const char*);
    const char* code = "a'{}s<d[(s\"<>\")] > 'f";
    cout << Symbol_Math(code) << endl;
}

void func14()
{
    cout << "func14: StaticQueue " << endl;

    StaticQueue<int, 10> sq;

    for(int i = 0; i < sq.capacity(); i++)
    {
        sq.add(i);
    }
    cout << "size = " << sq.size() << ", capacity = " << sq.capacity() << endl;
    for(int i = 0; i < sq.capacity(); i++)
    {
        cout << sq.front() << " ";
        sq.remove();
    }
    cout << endl;

    cout << "size = " << sq.size() << ", capacity = " << sq.capacity() << endl;
}
