#include "SortFunc.h"
#include "Sort.h"

using namespace DemoData;

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
}
