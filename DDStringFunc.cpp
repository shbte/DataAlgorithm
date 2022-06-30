#include <iostream>

#include "DDStringFunc.h"
#include "DDString.h"

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
