#include <iostream>

#include "MyFunc.h"

using namespace std;

void func0000()
{
    func1();

    cout << endl;
    func2();

    cout << endl;
    func3();

    cout << endl;
    func4();

    cout << endl;
    func5();
}

int main()
{
    cout << "Hello World!" << endl;

    func0000();

    return 0;
}
