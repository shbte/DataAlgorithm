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

    MatrixGraph<char, int, 9> mg;
    mg.setVertex(0, 'A');
    mg.setVertex(1, 'B');
    mg.setVertex(4, 'C');
    mg.setVertex(3, 'D');
    mg.setVertex(2, 'E');
    mg.setVertex(6, 'F');
    mg.setVertex(5, 'G');
    mg.setVertex(7, 'H');
    mg.setVertex(8, 'I');
    mg.setEdge(0, 1, 1);
    mg.setEdge(0, 3, 1);
    mg.setEdge(0, 4, 1);
    mg.setEdge(1, 0, 1);
    mg.setEdge(1, 2, 1);
    mg.setEdge(1, 4, 1);
    mg.setEdge(2, 1, 1);
    mg.setEdge(2, 5, 1);
    mg.setEdge(3, 0, 1);
    mg.setEdge(3, 6, 1);
    mg.setEdge(4, 0, 1);
    mg.setEdge(4, 1, 1);
    mg.setEdge(4, 6, 1);
    mg.setEdge(5, 2, 1);
    mg.setEdge(6, 3, 1);
    mg.setEdge(6, 4, 1);
    mg.setEdge(6, 7, 1);
    mg.setEdge(7, 6, 1);
    mg.setEdge(7, 8, 1);
    mg.setEdge(8, 7, 1);

    cout << "vCount: " << mg.vCount() << endl;  // vCount: 9
    cout << "eCount: " << mg.eCount() << endl;  //eCount: 20

    SharedPointer<Array<int>> array = mg.BFS(0);
    cout << "Breadth First Search: ";
    for(int i = 0; i < array->length(); i++)
    {
        cout << (*array)[i] << " "; // Breadth First Search: 0 1 3 4 2 6 5 7 8
    }
    cout << endl;

    array = mg.DFS(0);
    cout << "Depth First Search: ";
    for(int i = 0; i < array->length(); i++)
    {
        cout << (*array)[i] << " "; // Depth First Search: 0 1 2 5 4 6 3 7 8
    }
    cout << endl;

    array = mg.DFS1(0);
    cout << "Depth First Search Recursion: ";
    for(int i = 0; i < array->length(); i++)
    {
        cout << (*array)[i] << " "; // Depth First Search Recursion: 0 1 2 5 4 6 3 7 8
    }
    cout << endl;
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
    g.setEdge(3, 1, 8);
    g.setEdge(3, 1, 9);

    for(int i = 0; i < g.vCount(); i++)
    {
        cout << i << " : " << g.getVertex(i) << " ";    // 0 : A 1 : B 2 : C 3 : D
    }
    cout << endl;

    cout << "W(0, 1) : " << g.getEdge(0, 1) << endl;    // W(0, 1) : 5
    cout << "W(0, 3) : " << g.getEdge(0, 3) << endl;    // W(0, 3) : 5
    cout << "W(1, 2) : " << g.getEdge(1, 2) << endl;    // W(1, 2) : 8
    cout << "W(2, 3) : " << g.getEdge(2, 3) << endl;    // W(2, 3) : 2
    cout << "W(3, 1) : " << g.getEdge(3, 1) << endl;    // W(3, 1) : 9

    cout << "vCount: " << g.vCount() << endl;   // vCount: 4
    cout << "eCount: " << g.eCount() << endl;   // eCount: 5
    cout << "ID(1): " << g.ID(1) << endl;       // ID(1): 2
    cout << "OD(1): " << g.OD(1) << endl;       // OD(1): 1
    cout << "TD(1): " << g.TD(1) << endl;       // TD(1): 3

    ListGraph<char, int> mg;
    mg.addVertex('A');
    mg.addVertex('B');
    mg.addVertex('E');
    mg.addVertex('D');
    mg.addVertex('C');
    mg.addVertex('G');
    mg.addVertex('F');
    mg.addVertex('H');
    mg.addVertex('I');
    mg.setEdge(0, 1, 1);
    mg.setEdge(0, 3, 1);
    mg.setEdge(0, 4, 1);
    mg.setEdge(1, 0, 1);
    mg.setEdge(1, 2, 1);
    mg.setEdge(1, 4, 1);
    mg.setEdge(2, 1, 1);
    mg.setEdge(2, 5, 1);
    mg.setEdge(3, 0, 1);
    mg.setEdge(3, 6, 1);
    mg.setEdge(4, 0, 1);
    mg.setEdge(4, 1, 1);
    mg.setEdge(4, 6, 1);
    mg.setEdge(5, 2, 1);
    mg.setEdge(6, 3, 1);
    mg.setEdge(6, 4, 1);
    mg.setEdge(6, 7, 1);
    mg.setEdge(7, 6, 1);
    mg.setEdge(7, 8, 1);
    mg.setEdge(8, 7, 1);

    cout << "vCount: " << mg.vCount() << endl;  // vCount: 9
    cout << "eCount: " << mg.eCount() << endl;  // eCount: 20

    cout << "Breadth First Search: ";
    SharedPointer<Array<int>> array = mg.BFS(1);
    for(int i = 0; i < array->length(); i++)
    {
        cout << (*array)[i] << " "; // Breadth First Search: 1 0 2 4 3 5 6 7 8
    }
    cout << endl;

    array = mg.DFS(1);
    cout << "Depth First Search: ";
    for(int i = 0; i < array->length(); i++)
    {
        cout << (*array)[i] << " "; // epth First Search: 1 0 3 6 4 7 8 2 5
    }
    cout << endl;

    array = mg.DFS1(1);
    cout << "Depth First Search Recursion: ";
    for(int i = 0; i < array->length(); i++)
    {
        cout << (*array)[i] << " "; // Depth First Search Recursion: 1 0 3 6 4 7 8 2 5
    }
    cout << endl;
}
