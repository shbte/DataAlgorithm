#include <ctime>

#include "SortFunc.h"
#include "DynamicArray.h"
#include "Sort.h"
#include "StaticArray.h"

using namespace DemoData;

struct SortBase : public Object
{
    int id;
    int data1[1000];
    double data2[500];

    bool operator > (const SortBase& obj)
    {
        return id > obj.id;
    }
    bool operator <(const SortBase& obj)
    {
        return id < obj.id;
    }
};
struct SortBaseProxy : public SortBase
{
    SortBase* psb;

    SortBaseProxy& operator =(SortBase& obj)
    {
        psb = &obj;
        return *this;
    }

    SortBase& sortBase() const
    {
        return *psb;
    }

    bool operator >(const SortBaseProxy& obj)
    {
        return (this->sortBase() > obj.sortBase());
    }
    bool operator <(const SortBaseProxy& obj)
    {
        return (this->sortBase() < obj.sortBase());
    }
};
SortBase sb[1000];
SortBaseProxy sbp[1000];
void funcSort001()
{
    cout << "funcSort001: " << endl;

    cout << "Sort::Select" << endl;

    int as[] = {4, 6, 1, 2, 12, 11, 8, 3, 10, 5, 9, 0, 7};
    int size = sizeof(as) / sizeof(as[0]);

    // 打印数组元素
    Sort::print_array(as, size);    // 4 6 1 2 12 11 8 3 10 5 9 0 7

    // 选择排序, 默认(升序)
    Sort::Select(as, size);
    Sort::print_array(as, size);    // 0 1 2 3 4 5 6 7 8 9 10 11 12
    // 选择排序, false: 降序
    Sort::Select(as, size, false);
    Sort::print_array(as, size);    // 12 11 10 9 8 7 6 5 4 3 2 1 0
    // 选择排序, true: 升序
    Sort::Select(as, size, true);
    Sort::print_array(as, size);    // 0 1 2 3 4 5 6 7 8 9 10 11 12

    cout << "Sort::Insert" << endl;

    int ai[] = {4, 6, 1, 2, 12, 11, 8, 3, 10, 5, 9, 0, 7};
    size = sizeof(ai) / sizeof(ai[0]);

    // 打印数组元素
    Sort::print_array(ai, size);    // 4 6 1 2 12 11 8 3 10 5 9 0 7

    // 插入排序, 默认(升序)
    Sort::Insert(ai, size);
    Sort::print_array(ai, size);    // 0 1 2 3 4 5 6 7 8 9 10 11 12
    // 插入排序, false: 降序
    Sort::Insert(ai, size, false);
    Sort::print_array(ai, size);    // 12 11 10 9 8 7 6 5 4 3 2 1 0
    // 插入排序, true: 升序
    Sort::Insert(ai, size, true);
    Sort::print_array(ai, size);    // 0 1 2 3 4 5 6 7 8 9 10 11 12

    cout << "Sort::Bubble" << endl;

    int ab[] = {4, 6, 1, 2, 12, 11, 8, 3, 10, 5, 9, 0, 7};
    size = sizeof(ab) / sizeof(ab[0]);

    // 打印数组元素
    Sort::print_array(ab, size);    // 4 6 1 2 12 11 8 3 10 5 9 0 7

    // 冒泡排序, 默认(升序)
    Sort::Bubble(ab, size);
    Sort::print_array(ab, size);    // 0 1 2 3 4 5 6 7 8 9 10 11 12
    // 冒泡排序, false: 降序
    Sort::Bubble(ab, size, false);
    Sort::print_array(ab, size);    // 12 11 10 9 8 7 6 5 4 3 2 1 0
    // 冒泡排序, true: 升序
    Sort::Bubble(ab, size, true);
    Sort::print_array(ab, size);    // 0 1 2 3 4 5 6 7 8 9 10 11 12

    cout << "Sort::Shell" << endl;

    int ash[] = {4, 6, 1, 2, 12, 11, 8, 3, 10, 5, 9, 0, 7};
    //int ash[] = {21, 25, 49, 25, 16, 8};
    size = sizeof(ash) / sizeof(ash[0]);

    Sort::print_array(ash, size);   // 4 6 1 2 12 11 8 3 10 5 9 0 7

    // 希尔排序, 默认(升序)
    Sort::Shell(ash, size);
    Sort::print_array(ash, size);   // 0 1 2 3 4 5 6 7 8 9 10 11 12
    // 希尔排序, false(降序)
    Sort::Shell(ash, size, false);
    Sort::print_array(ash, size);   // 12 11 10 9 8 7 6 5 4 3 2 1 0
    // 希尔排序, true(升序)
    Sort::Shell(ash, size, true);
    Sort::print_array(ash, size);   // 0 1 2 3 4 5 6 7 8 9 10 11 12

    cout << "Sort::Merge" << endl;

    int am[] = {4, 6, 1, 2, 12, 11, 8, 3, 10, 5, 9, 0, 7};
    //int am[] = {52, 23, 80, 36, 68, 14};
    size = sizeof(am) / sizeof(am[0]);

    // 打印数组元素
    Sort::print_array(am, size);    // 4 6 1 2 12 11 8 3 10 5 9 0 7

    // 归并排序, 默认(升序)
    Sort::Merge(am, size);
    Sort::print_array(am, size);    // 0 1 2 3 4 5 6 7 8 9 10 11 12
    // 归并排序, false(降序)
    Sort::Merge(am, size, false);
    Sort::print_array(am, size);    // 12 11 10 9 8 7 6 5 4 3 2 1 0
    // 归并排序, true(升序)
    Sort::Merge(am, size, true);
    Sort::print_array(am, size);    // 0 1 2 3 4 5 6 7 8 9 10 11 12

    cout << "Sort::Quick" << endl;

    int aq[] = {4, 6, 1, 2, 12, 11, 8, 3, 10, 5, 9, 0, 7};
    size = sizeof(aq) / sizeof(aq[0]);

    // 打印数组元素
    Sort::print_array(aq, size);    // 4 6 1 2 12 11 8 3 10 5 9 0 7

    // 快速排序, 默认(升序)
    Sort::Quick(aq, size);
    Sort::print_array(aq, size);    // 0 1 2 3 4 5 6 7 8 9 10 11 12
    // 快速排序, false(降序)
    Sort::Quick(aq, size, false);
    Sort::print_array(aq, size);    // 12 11 10 9 8 7 6 5 4 3 2 1 0
    // 快速排序, true(升序)
    Sort::Quick(aq, size, true);
    Sort::print_array(aq, size);    // 0 1 2 3 4 5 6 7 8 9 10 11 12

    cout << "Sort::DynamicArray" << endl;

    // 动态数组, 初始化时指定内存空间大小(后续可使用resize重置大小)
    DynamicArray<double> da(10);
    size = da.length();

    // 赋值动态数组
    for(int i = 0 ; i < size; i++)
    {
        da[i] = i + 0.1 * i;
    }

    // 打印数组元素
    Sort::print_array(da.array(), size);    // 0 1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8 9.9

    // 选择排序, 降序
    Sort::Select(da.array(), size, false);
    Sort::print_array(da.array(), size);    // 9.9 8.8 7.7 6.6 5.5 4.4 3.3 2.2 1.1 0
    // 插入排序, 升序
    Sort::Insert(da.array(), size);
    Sort::print_array(da.array(), size);    // 0 1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8 9.9
    // 冒泡排序, 降序
    Sort::Bubble(da.array(), size, false);
    Sort::print_array(da.array(), size);    // 9.9 8.8 7.7 6.6 5.5 4.4 3.3 2.2 1.1 0
    // 希尔排序, 升序
    Sort::Shell(da.array(), size);
    Sort::print_array(da.array(), size);    // 0 1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8 9.9
    // 归并排序, 降序
    Sort::Merge(da.array(), size, false);
    Sort::print_array(da.array(), size);    // 9.9 8.8 7.7 6.6 5.5 4.4 3.3 2.2 1.1 0
    // 快速排序, 升序
    Sort::Quick(da.array(), size);
    Sort::print_array(da.array(), size);    // 0 1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8 9.9

    cout << "Sort::StaticArray" << endl;

    // 静态数组, 初始化时指定内存空间大小(后续不可变)
    StaticArray<double, 10> sa;
    size = sa.length();

    for(int i = 0; i < size; i++)
    {
        sa[i] = i + 0.2 * i;
    }

    // 打印数组元素
    Sort::print_array(sa.array(), size);    // 0 1.2 2.4 3.6 4.8 6 7.2 8.4 9.6 10.8

    // 选择排序, 降序
    Sort::Select(sa.array(), size, false);
    Sort::print_array(sa.array(), size);    // 10.8 9.6 8.4 7.2 6 4.8 3.6 2.4 1.2 0
    // 插入排序, 升序
    Sort::Insert(sa.array(), size);
    Sort::print_array(sa.array(), size);    // 0 1.2 2.4 3.6 4.8 6 7.2 8.4 9.6 10.8
    // 冒泡排序, 降序
    Sort::Bubble(sa.array(), size, false);
    Sort::print_array(sa.array(), size);    // 10.8 9.6 8.4 7.2 6 4.8 3.6 2.4 1.2 0
    // 希尔排序, 升序
    Sort::Shell(sa.array(), size);
    Sort::print_array(sa.array(), size);    // 0 1.2 2.4 3.6 4.8 6 7.2 8.4 9.6 10.8
    // 归并排序, 降序
    Sort::Merge(sa.array(), size, false);
    Sort::print_array(sa.array(), size);    // 10.8 9.6 8.4 7.2 6 4.8 3.6 2.4 1.2 0
    // 快速排序, 升序
    Sort::Quick(sa.array(), size);
    Sort::print_array(sa.array(), size);    // 0 1.2 2.4 3.6 4.8 6 7.2 8.4 9.6 10.8

    cout << "Sort::SortBase" << endl;

    for(int i = 0; i < 1000; i++)
    {
        sb[i].id = i;
        sbp[i] = sb[i];

        //cout << sbp[i].sortBase().id << endl;
    }

    clock_t begin = clock();

    Sort::Bubble(sbp, 1000, false);

    clock_t end = clock();
    cout << "time : " << (end - begin) << endl;

    /*
    for(int i = 0; i < 1000; i++)
    {
        cout << sb[i].id << " ";
        cout << sbp[i].psb->id << " ";
    }
    cout << endl;
    */
}
