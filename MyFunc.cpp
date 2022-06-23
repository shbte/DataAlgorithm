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
    SmartPointer<Base> spb = new Base();
    SmartPointer<Base> nspb;

    cout << "spb = " << spb.get()  << endl;     // spb = 0x19c490f6b50
    cout << "nspb = " << nspb.get()  << endl;   // nspb = 0

    nspb = spb;

    cout << "spb.isNULL = " << spb.isNULL() << ", this = " << spb.get() << endl;    // spb.isNULL = 1, this = 0
    cout << "nspb.isNULL = " << nspb.isNULL() << ", this = " << nspb.get() << endl; // nspb.isNULL = 0, this = 0x19c490f6b50
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
    cout << "func6:: List " << endl;

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
