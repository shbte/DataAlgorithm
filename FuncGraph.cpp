#include "FuncGraph.h"

#include <iostream>

#include "MatrixGraph.h"
#include "ListGraph.h"

using namespace std;
using namespace DemoData;

void funcGraph001()
{
    cout << "funcGraph001:: MatrixGraph" << endl;

    MatrixGraph<int, int, 3> mgi;

    mgi.setEdge(0, 1, 1);
    mgi.setEdge(1, 0, 2);
    mgi.setEdge(1, 2, 3);

    cout << "vCount: " << mgi.vCount() << endl; // vCount: 3
    cout << "eCOunt: " << mgi.eCount() << endl; // eCOunt: 3
    cout << "ID(1): " << mgi.ID(1) << endl;     // ID(1): 1
    cout << "OD(1): " << mgi.OD(1) << endl;     // OD(1): 2
    cout << "TD(1): " << mgi.TD(1) << endl;     // TD(1): 3

    cout << "W(0, 1): " << mgi.getEdge(0, 1) << endl;   // W(0, 1): 1
    cout << "W(1, 0): " << mgi.getEdge(1, 0) << endl;   // W(1, 0): 2
    cout << "W(1, 2): " << mgi.getEdge(1, 2) << endl;   // W(1, 2): 3

    SharedPointer<Array<int>> aj = mgi.getAdjacent(1);

    for(int i = 0; i < aj->length(); i++)
    {
        cout << (*aj)[i] << " ";    // 0 2
    }
    cout << endl;

    cout << "Delete Edge: " << endl;

    mgi.removeEdge(0, 1);
    cout << "eCount: " << mgi.eCount() << endl; // eCount: 2

    mgi.setVertex(0, 100);
    cout << "V(0): " << mgi.getVertex(0) << endl;   // V(0): 100

    //cout << "W(0, 1): " << mgi.getEdge(0, 1) << endl;   // DemoData::InvalidParameterException
}

void funcGraph002()
{
    cout << "funcGraph002:: ListGrap" << endl;

    ListGraph<char, int> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.setEdge(0, 1, 5);
    g.setEdge(0, 3, 5);
    g.setEdge(1, 2, 8);
    g.setEdge(2, 3, 2);
    g.setEdge(3, 1, 9);

    for(int i = 0; i < g.vCount(); i++)
    {
        cout << i << " : " << g.getVertex(i) << " ";
    }
    cout << endl;

    cout << "W(0, 1) : " << g.getEdge(0, 1) << endl;
    cout << "W(0, 3) : " << g.getEdge(0, 3) << endl;
    cout << "W(1, 2) : " << g.getEdge(1, 2) << endl;
    cout << "W(2, 3) : " << g.getEdge(2, 3) << endl;
    cout << "W(3, 1) : " << g.getEdge(3, 1) << endl;

    cout << "vCount: " << g.vCount() << endl;
    cout << "eCount: " << g.eCount() << endl;
    cout << "ID(1): " << g.ID(1) << endl;
    cout << "OD(1): " << g.OD(1) << endl;
    cout << "TD(1): " << g.TD(1) << endl;
}
