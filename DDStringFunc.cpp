#include <iostream>

#include "DDStringFunc.h"
#include "DDString.h"
#include "Exception.h"

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
