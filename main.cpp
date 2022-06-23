#include <iostream>

#include "MyFunc.h"

using namespace std;

void func0000()
{
    func1();
}

int main()
{
    cout << "Hello World!" << endl;

    func0000();

    return 0;
}
