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

    mgi.setEdgeWeight(0, 1, 1);
    mgi.setEdgeWeight(1, 0, 2);
    mgi.setEdgeWeight(1, 2, 3);

    cout << "vCount: " << mgi.vCount() << endl; // vCount: 3
    cout << "eCOunt: " << mgi.eCount() << endl; // eCOunt: 3
    cout << "ID(1): " << mgi.ID(1) << endl;     // ID(1): 1
    cout << "OD(1): " << mgi.OD(1) << endl;     // OD(1): 2
    cout << "TD(1): " << mgi.TD(1) << endl;     // TD(1): 3

    cout << "W(0, 1): " << mgi.getEdgeWeight(0, 1) << endl;   // W(0, 1): 1
    cout << "W(1, 0): " << mgi.getEdgeWeight(1, 0) << endl;   // W(1, 0): 2
    cout << "W(1, 2): " << mgi.getEdgeWeight(1, 2) << endl;   // W(1, 2): 3

    cout << "isUndirected: " << mgi.isUndirected() << endl; // isUndirected: 0

    SharedPointer<Array<int>> aj = mgi.getAdjacent(1);

    for(int i = 0; i < aj->length(); i++)
    {
        cout << (*aj)[i] << " ";    // 0 2
    }
    cout << endl;

    cout << "Delete Edge: " << endl;

    mgi.removeEdgeWeight(0, 1);
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
    mg.setEdgeWeight(0, 1, 1);
    mg.setEdgeWeight(0, 3, 1);
    mg.setEdgeWeight(0, 4, 1);
    mg.setEdgeWeight(1, 0, 1);
    mg.setEdgeWeight(1, 2, 1);
    mg.setEdgeWeight(1, 4, 1);
    mg.setEdgeWeight(2, 1, 1);
    mg.setEdgeWeight(2, 5, 1);
    mg.setEdgeWeight(3, 0, 1);
    mg.setEdgeWeight(3, 6, 1);
    mg.setEdgeWeight(4, 0, 1);
    mg.setEdgeWeight(4, 1, 1);
    mg.setEdgeWeight(4, 6, 1);
    mg.setEdgeWeight(5, 2, 1);
    mg.setEdgeWeight(6, 3, 1);
    mg.setEdgeWeight(6, 4, 1);
    mg.setEdgeWeight(6, 7, 1);
    mg.setEdgeWeight(7, 6, 1);
    mg.setEdgeWeight(7, 8, 1);
    mg.setEdgeWeight(8, 7, 1);

    cout << "vCount: " << mg.vCount() << endl;  // vCount: 9
    cout << "eCount: " << mg.eCount() << endl;  //eCount: 20

    cout << "isUndirected: " << mg.isUndirected() << endl;  // isUndirected: 1

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

    cout << "Prim:" << endl;    // Prim:
    MatrixGraph<int, int, 4> mgp1;
    mgp1.setVertex(0, 0);
    mgp1.setVertex(1, 1);
    mgp1.setVertex(2, 2);
    mgp1.setVertex(3, 3);
    mgp1.setEdgeWeight(0, 1, 1);
    mgp1.setEdgeWeight(1, 0, 1);
    mgp1.setEdgeWeight(0, 2, 3);
    mgp1.setEdgeWeight(2, 0, 3);
    mgp1.setEdgeWeight(1, 2, 1);
    mgp1.setEdgeWeight(2, 1, 1);
    mgp1.setEdgeWeight(1, 3, 4);
    mgp1.setEdgeWeight(3, 1, 4);
    mgp1.setEdgeWeight(2, 3, 1);
    mgp1.setEdgeWeight(3, 2, 1);

    cout << "mgp1.isUndirected: " << mgp1.isUndirected() << endl;   // mgp1.isUndirected: 1

    SharedPointer<Array<Edge<int>>> edges = mgp1.Prim();
    int weight = 0;
    for(int i = 0; i < edges->length(); i++)
    {
        cout << "(" << (*edges)[i].b << ", " << (*edges)[i].e << ", " << (*edges)[i].w << ")" << " ";   // (0, 1, 1) (1, 2, 1) (2, 3, 1)
        weight += (*edges)[i].w;
    }
    cout << endl;
    cout << "AllWeight: " << weight << endl;    // AllWeight: 3

    edges = mgp1.Kruskal();
    weight = 0;
    for(int i = 0; i < edges->length(); i++)
    {
        cout << "(" << (*edges)[i].b << ", " << (*edges)[i].e << ", " << (*edges)[i].w << ")" << " ";   // (0, 1, 1) (1, 2, 1) (2, 3, 1)
        weight += (*edges)[i].w;
    }
    cout << endl;
    cout << "AllWeight: " << weight << endl;    // AllWeight: 3

    MatrixGraph<const char*, int, 9> mgp2;
    mgp2.setVertex(0, "V0");
    mgp2.setVertex(1, "V1");
    mgp2.setVertex(2, "V2");
    mgp2.setVertex(3, "V3");
    mgp2.setVertex(4, "V4");
    mgp2.setVertex(5, "V5");
    mgp2.setVertex(6, "V6");
    mgp2.setVertex(7, "V7");
    mgp2.setVertex(8, "V8");
    mgp2.setEdgeWeight(0, 1, 10);
    mgp2.setEdgeWeight(1, 0, 10);
    mgp2.setEdgeWeight(0, 5, 11);
    mgp2.setEdgeWeight(5, 0, 11);
    mgp2.setEdgeWeight(1, 2, 18);
    mgp2.setEdgeWeight(2, 1, 18);
    mgp2.setEdgeWeight(1, 6, 16);
    mgp2.setEdgeWeight(6, 1, 16);
    mgp2.setEdgeWeight(1, 8, 12);
    mgp2.setEdgeWeight(8, 1, 12);
    mgp2.setEdgeWeight(2, 3, 22);
    mgp2.setEdgeWeight(3, 2, 22);
    mgp2.setEdgeWeight(2, 8, 8);
    mgp2.setEdgeWeight(8, 2, 8);
    mgp2.setEdgeWeight(3, 4, 20);
    mgp2.setEdgeWeight(4, 3, 20);
    mgp2.setEdgeWeight(3, 6, 24);
    mgp2.setEdgeWeight(6, 3, 24);
    mgp2.setEdgeWeight(3, 7, 16);
    mgp2.setEdgeWeight(7, 3, 16);
    mgp2.setEdgeWeight(3, 8, 21);
    mgp2.setEdgeWeight(8, 3, 21);
    mgp2.setEdgeWeight(4, 5, 26);
    mgp2.setEdgeWeight(5, 4, 26);
    mgp2.setEdgeWeight(4, 7, 7);
    mgp2.setEdgeWeight(7, 4, 7);
    mgp2.setEdgeWeight(5, 6, 17);
    mgp2.setEdgeWeight(6, 5, 17);
    mgp2.setEdgeWeight(6, 7, 19);
    mgp2.setEdgeWeight(7, 6, 19);

    cout << "mgp2.isUndirected: " << mgp2.isUndirected() << endl;   // mgp2.isUndirected: 1

    edges = mgp2.Prim(true);
    weight = 0;
    for(int i = 0; i < edges->length(); i++)
    {
        cout << "(" << (*edges)[i].b << ", " << (*edges)[i].e << ", " << (*edges)[i].w << ")" << " ";   // (0, 1, 10) (0, 5, 11) (1, 8, 12) (8, 2, 8) (1, 6, 16) (6, 7, 19) (7, 4, 7) (7, 3, 16)
        weight += (*edges)[i].w;
    }
    cout << endl;
    cout << "AllWeight: " << weight << endl;    // AllWeight: 99

    edges = mgp2.Kruskal(true);
    weight = 0;
    for(int i = 0; i < edges->length(); i++)
    {
        cout << "(" << (*edges)[i].b << ", " << (*edges)[i].e << ", " << (*edges)[i].w << ")" << " ";   // (4, 7, 7) (2, 8, 8) (0, 1, 10) (0, 5, 11) (1, 8, 12) (1, 6, 16) (3, 7, 16) (6, 7, 19)
        weight += (*edges)[i].w;
    }
    cout << endl;
    cout << "AllWeight: " << weight << endl;    // AllWeight: 99
}

void funcGraph002()
{
    cout << "funcGraph002:: ListGrap" << endl;

    ListGraph<char, int> g;

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.setEdgeWeight(0, 1, 5);
    g.setEdgeWeight(0, 3, 5);
    g.setEdgeWeight(1, 2, 8);
    g.setEdgeWeight(2, 3, 2);
    g.setEdgeWeight(3, 1, 8);
    g.setEdgeWeight(3, 1, 9);

    for(int i = 0; i < g.vCount(); i++)
    {
        cout << i << " : " << g.getVertex(i) << " ";    // 0 : A 1 : B 2 : C 3 : D
    }
    cout << endl;

    cout << "W(0, 1) : " << g.getEdgeWeight(0, 1) << endl;    // W(0, 1) : 5
    cout << "W(0, 3) : " << g.getEdgeWeight(0, 3) << endl;    // W(0, 3) : 5
    cout << "W(1, 2) : " << g.getEdgeWeight(1, 2) << endl;    // W(1, 2) : 8
    cout << "W(2, 3) : " << g.getEdgeWeight(2, 3) << endl;    // W(2, 3) : 2
    cout << "W(3, 1) : " << g.getEdgeWeight(3, 1) << endl;    // W(3, 1) : 9

    cout << "vCount: " << g.vCount() << endl;   // vCount: 4
    cout << "eCount: " << g.eCount() << endl;   // eCount: 5
    cout << "ID(1): " << g.ID(1) << endl;       // ID(1): 2
    cout << "OD(1): " << g.OD(1) << endl;       // OD(1): 1
    cout << "TD(1): " << g.TD(1) << endl;       // TD(1): 3

    cout << "isUndirected: " << g.isUndirected() << endl;   // isUndirected: 0

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
    mg.setEdgeWeight(0, 1, 1);
    mg.setEdgeWeight(0, 3, 1);
    mg.setEdgeWeight(0, 4, 1);
    mg.setEdgeWeight(1, 0, 1);
    mg.setEdgeWeight(1, 2, 1);
    mg.setEdgeWeight(1, 4, 1);
    mg.setEdgeWeight(2, 1, 1);
    mg.setEdgeWeight(2, 5, 1);
    mg.setEdgeWeight(3, 0, 1);
    mg.setEdgeWeight(3, 6, 1);
    mg.setEdgeWeight(4, 0, 1);
    mg.setEdgeWeight(4, 1, 1);
    mg.setEdgeWeight(4, 6, 1);
    mg.setEdgeWeight(5, 2, 1);
    mg.setEdgeWeight(6, 3, 1);
    mg.setEdgeWeight(6, 4, 1);
    mg.setEdgeWeight(6, 7, 1);
    mg.setEdgeWeight(7, 6, 1);
    mg.setEdgeWeight(7, 8, 1);
    mg.setEdgeWeight(8, 7, 1);

    cout << "vCount: " << mg.vCount() << endl;  // vCount: 9
    cout << "eCount: " << mg.eCount() << endl;  // eCount: 20

    cout << "isUndirected: " << mg.isUndirected() << endl;  // isUndirected: 1

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

    cout << "Prim:" << endl;    // mgp1.isUndirected: 1
    ListGraph<int, int> mgp1;
    mgp1.addVertex(0);
    mgp1.addVertex(1);
    mgp1.addVertex(2);
    mgp1.addVertex(3);
    mgp1.setEdgeWeight(0, 1, 1);
    mgp1.setEdgeWeight(1, 0, 1);
    mgp1.setEdgeWeight(0, 2, 3);
    mgp1.setEdgeWeight(2, 0, 3);
    mgp1.setEdgeWeight(1, 2, 1);
    mgp1.setEdgeWeight(2, 1, 1);
    mgp1.setEdgeWeight(1, 3, 4);
    mgp1.setEdgeWeight(3, 1, 4);
    mgp1.setEdgeWeight(2, 3, 1);
    mgp1.setEdgeWeight(3, 2, 1);

    cout << "mgp1.isUndirected: " << mgp1.isUndirected() << endl;   // mgp1.isUndirected: 1

    SharedPointer<Array<Edge<int>>> edges = mgp1.Prim();
    int weight = 0;
    for(int i = 0; i < edges->length(); i++)
    {
        cout << "(" << (*edges)[i].b << ", " << (*edges)[i].e << ", " << (*edges)[i].w << ")" << " ";   // (0, 1, 1) (1, 2, 1) (2, 3, 1)
        weight += (*edges)[i].w;
    }
    cout << endl;
    cout << "AllWeight: " << weight << endl;    // AllWeight: 3

    edges = mgp1.Kruskal();
    weight = 0;
    for(int i = 0; i < edges->length(); i++)
    {
        cout << "(" << (*edges)[i].b << ", " << (*edges)[i].e << ", " << (*edges)[i].w << ")" << " ";   // (0, 1, 1) (1, 2, 1) (2, 3, 1)
        weight += (*edges)[i].w;
    }
    cout << endl;
    cout << "AllWeight: " << weight << endl;    // AllWeight: 3

    ListGraph<const char*, int> mgp2;
    mgp2.addVertex("V0");
    mgp2.addVertex("V1");
    mgp2.addVertex("V2");
    mgp2.addVertex("V3");
    mgp2.addVertex("V4");
    mgp2.addVertex("V5");
    mgp2.addVertex("V6");
    mgp2.addVertex("V7");
    mgp2.addVertex("V8");
    mgp2.setEdgeWeight(0, 1, 10);
    mgp2.setEdgeWeight(1, 0, 10);
    mgp2.setEdgeWeight(0, 5, 11);
    mgp2.setEdgeWeight(5, 0, 11);
    mgp2.setEdgeWeight(1, 2, 18);
    mgp2.setEdgeWeight(2, 1, 18);
    mgp2.setEdgeWeight(1, 6, 16);
    mgp2.setEdgeWeight(6, 1, 16);
    mgp2.setEdgeWeight(1, 8, 12);
    mgp2.setEdgeWeight(8, 1, 12);
    mgp2.setEdgeWeight(2, 3, 22);
    mgp2.setEdgeWeight(3, 2, 22);
    mgp2.setEdgeWeight(2, 8, 8);
    mgp2.setEdgeWeight(8, 2, 8);
    mgp2.setEdgeWeight(3, 4, 20);
    mgp2.setEdgeWeight(4, 3, 20);
    mgp2.setEdgeWeight(3, 6, 24);
    mgp2.setEdgeWeight(6, 3, 24);
    mgp2.setEdgeWeight(3, 7, 16);
    mgp2.setEdgeWeight(7, 3, 16);
    mgp2.setEdgeWeight(3, 8, 21);
    mgp2.setEdgeWeight(8, 3, 21);
    mgp2.setEdgeWeight(4, 5, 26);
    mgp2.setEdgeWeight(5, 4, 26);
    mgp2.setEdgeWeight(4, 7, 7);
    mgp2.setEdgeWeight(7, 4, 7);
    mgp2.setEdgeWeight(5, 6, 17);
    mgp2.setEdgeWeight(6, 5, 17);
    mgp2.setEdgeWeight(6, 7, 19);
    mgp2.setEdgeWeight(7, 6, 19);

    cout << "mgp2.isUndirected: " << mgp2.isUndirected() << endl;   // mgp2.isUndirected: 1

    edges = mgp2.Prim(false);
    weight = 0;
    for(int i = 0; i < edges->length(); i++)
    {
        cout << "(" << (*edges)[i].b << ", " << (*edges)[i].e << ", " << (*edges)[i].w << ")" << " ";   // (0, 5, 11) (5, 4, 26) (4, 3, 20) (3, 6, 24) (3, 2, 22) (3, 8, 21) (6, 7, 19) (2, 1, 18)
        weight += (*edges)[i].w;
    }
    cout << endl;
    cout << "AllWeight: " << weight << endl;    // AllWeight: 161

    edges = mgp2.Kruskal(false);
    weight = 0;
    for(int i = 0; i < edges->length(); i++)
    {
        cout << "(" << (*edges)[i].b << ", " << (*edges)[i].e << ", " << (*edges)[i].w << ")" << " ";   // (4, 5, 26) (3, 6, 24) (2, 3, 22) (3, 8, 21) (3, 4, 20) (6, 7, 19) (1, 2, 18) (0, 5, 11)
        weight += (*edges)[i].w;
    }
    cout << endl;
    cout << "AllWeight: " << weight << endl;    // AllWeight: 161
}

void funcGraph003()
{
    cout << "funcGraph003: MatrixGraph => Dijkstra" << endl;    // funcGraph003: MatrixGraph => Dijkstra

    MatrixGraph<int, int, 4> mg1;
    mg1.setVertex(0, 0);
    mg1.setVertex(1, 1);
    mg1.setVertex(2, 2);
    mg1.setVertex(3, 3);
    mg1.setEdgeWeight(0, 1, 1);
    mg1.setEdgeWeight(0, 2, 3);
    mg1.setEdgeWeight(1, 2, 1);
    mg1.setEdgeWeight(2, 3, 1);
    mg1.setEdgeWeight(1, 3, 4);

    cout << "mg1.vCount: " << mg1.vCount() << endl; // mg1.vCount: 4
    cout << "mg1.eCount: " << mg1.eCount() << endl; // mg1.eCount: 5

    SharedPointer<Array<int>> path = mg1.Dijkstra(0, 3);

    for(int i = 0; i < path->length(); i++)
    {
        cout << (*path)[i] << " ";  // 0 1 2 3
    }
    cout << endl;

    MatrixGraph<int, int, 5> mg2;
    mg2.setVertex(0, 0);
    mg2.setVertex(1, 1);
    mg2.setVertex(2, 2);
    mg2.setVertex(3, 3);
    mg2.setVertex(4, 4);
    mg2.setEdgeWeight(0, 1, 10);
    mg2.setEdgeWeight(0, 3, 30);
    mg2.setEdgeWeight(0, 4, 100);
    mg2.setEdgeWeight(1, 2, 50);
    mg2.setEdgeWeight(2, 4, 10);
    mg2.setEdgeWeight(3, 2, 20);
    mg2.setEdgeWeight(3, 4, 60);

    cout << "mg2.vCount: " << mg2.vCount() << endl; // mg2.vCount: 5
    cout << "mg2.eCount: " << mg2.eCount() << endl; // mg2.eCount: 7

    path = mg2.Dijkstra(0, 4);

    for(int i = 0; i < path->length(); i++)
    {
        cout << (*path)[i] << " ";  // 0 3 2 4
    }
    cout << endl;

    cout << "funcGraph003: ListGraph => Dijkstra" << endl;  // funcGraph003: ListGraph => Dijkstra

    ListGraph<int, int> lg1;
    lg1.addVertex(0);
    lg1.addVertex(1);
    lg1.addVertex(2);
    lg1.addVertex(3);
    lg1.setEdgeWeight(0, 1, 1);
    lg1.setEdgeWeight(0, 2, 3);
    lg1.setEdgeWeight(1, 2, 1);
    lg1.setEdgeWeight(2, 3, 1);
    lg1.setEdgeWeight(1, 3, 4);

    cout << "lg1.vCount: " << lg1.vCount() << endl; // lg1.vCount: 4
    cout << "lg1.eCount: " << lg1.eCount() << endl; // lg1.eCount: 5

    path = lg1.Dijkstra(0, 3);

    for(int i = 0; i < path->length(); i++)
    {
        cout << (*path)[i] << " ";  // 0 1 2 3
    }
    cout << endl;

    ListGraph<int, int> lg2;
    lg2.addVertex(0);
    lg2.addVertex(1);
    lg2.addVertex(2);
    lg2.addVertex(3);
    lg2.addVertex(4);
    lg2.setEdgeWeight(0, 1, 10);
    lg2.setEdgeWeight(0, 3, 30);
    lg2.setEdgeWeight(0, 4, 100);
    lg2.setEdgeWeight(1, 2, 50);
    lg2.setEdgeWeight(2, 4, 10);
    lg2.setEdgeWeight(3, 2, 20);
    lg2.setEdgeWeight(3, 4, 60);

    cout << "lg2.vCount: " << lg2.vCount() << endl; // lg2.vCount: 5
    cout << "lg2.eCount: " << lg2.eCount() << endl; // lg2.eCount: 7

    path = lg2.Dijkstra(0, 4);

    for(int i = 0; i < path->length(); i++)
    {
        cout << (*path)[i] << " ";  // 0 3 2 4
    }
    cout << endl;

    cout << "funcGraph003: MatrixGraph => Floyd" << endl;

    MatrixGraph<int, int, 3> mg3;
    mg3.setVertex(0, 0);
    mg3.setVertex(1, 1);
    mg3.setVertex(2, 2);
    mg3.setEdgeWeight(0, 1, 4);
    mg3.setEdgeWeight(0, 2, 11);
    mg3.setEdgeWeight(1, 0, 6);
    mg3.setEdgeWeight(1, 2, 2);
    mg3.setEdgeWeight(2, 0, 3);

    cout << "mg3.vCount: " << mg3.vCount() << endl;
    cout << "mg3.eCount: " << mg3.eCount() << endl;

    int i = 1;
    int j = 1;
    path = mg3.Floyd(i, j);
    cout << "Vex<" << i << ", " << j << "> = ";
    for(int k = 0; k < path->length(); k++)
    {
        cout << (*path)[k] << " ";
    }
    cout << endl;
}

// 创建图函数
Graph<int, int>* create_graph(int* a, int len)
{
    ListGraph<int, int>* ret = new ListGraph<int, int>();

    if(ret != NULL)
    {
        // 生成顶点
        for(int i = 0; i < len; i++)
        {
            ret->addVertex(a[i]);
        }
        // 生成边
        for(int i = 0; i < len; i++)
        {
            for(int j = (i + 1); j < len; j++)
            {
                // 最长不下降序列, 数值不下降
                if(a[i] <= a[j])
                {
                    ret->setEdgeWeight(i, j, 1);
                }
            }
        }

        cout << "Graph: ";
        for(int i = 0; i < ret->vCount(); i++)
        {
            cout << ret->getVertex(i) << " ";
        }
        cout << endl;
        cout << "vCount: " << ret->vCount() << endl;
        cout << "eCount: " << ret->eCount() << endl;

        return ret;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memoty to create ret object(ListGraph<int, int>)...");
    }
}
// 初始化数组函数
void init_array(Array<int>& count, Array<LinkList<int>*>& path, Array<bool>& mark)
{
    for(int i = 0; i < count.length(); i++)
    {
        count[i] = 0;
        path[i] = NULL;
        mark[i] = false;
    }
}
// 最长不下降序列递归函数 => 以顶点index为起始的图g的最长不下降序列, 返回值为最长序列的顶点个数
int search_max_path(Graph<int, int>& g, int index, Array<int>& count, Array<LinkList<int>*>& path, Array<bool>& mark)
{
    int ret = 0;

    int maxCount = 0;
    LinkList<int>* maxIndex = new LinkList<int>();

    SharedPointer<Array<int>> aj = g.getAdjacent(index);

    // 循环遍历顶点index的邻接顶点
    for(int i = 0; i < aj->length(); i++)
    {
        int num = 0;
        int ajIndex = (*aj)[i];

        if(!mark[ajIndex])
        {
            num = search_max_path(g, ajIndex, count, path, mark);
        }
        else
        {
            // 获取以顶点ajIndex为起始的序列的顶点数
            num = count[ajIndex];
        }

        // 获取最长序列所在的邻接顶点下标(maxIndex)和顶点数(maxCount)
        if(maxCount == num)
        {
            maxIndex->insert(ajIndex);
        }

        if(maxCount < num)
        {
            maxIndex->clear();

            maxIndex->insert(ajIndex);
            maxCount = num;
        }
    }

    // 邻接顶点的最长序列数 + 加上自顶点
    maxCount++;

    // 更新相关数组
    count[index] = maxCount;
    path[index] = maxIndex;
    mark[index] = true;

    ret = maxCount;

    return ret;
}
void search_max_path(Graph<int, int>& g, Array<int>& count, Array<LinkList<int>*>& path, Array<bool>& mark)
{
    // 遍历图, 分别以顶点i为起始顶点
    for(int i = 0; i < count.length(); i++)
    {
        if(!mark[i])
        {
            search_max_path(g, i, count, path, mark);
        }
    }
}
// 递归输出函数
void print_max_path(Graph<int, int>& g, int index, Array<LinkList<int>*>& path, LinkList<int>& cp)
{
    // 加入顶点下标
    cp.insert(index);

    // 判断是否到达尾元素 => 尾元素的path[index]为空
    if(path[index]->length() > 0)
    {
        for(path[index]->moveInit(0); !path[index]->end(); path[index]->next())
        {
            print_max_path(g, path[index]->currentValue(), path, cp);
        }
    }
    else
    {
        cout << "Element: ";
        for(int i = 0; i < cp.length(); i++)
        {
            cout << g.getVertex(cp.get(i)) << " ";
        }
        cout << endl;
    }

    // 向上移除链表尾元素
    cp.remove(cp.length() - 1);
}
// 输出函数 => 打印图的指定顶点值
void print_max_path(Graph<int, int>& g, Array<int>& count, Array<LinkList<int>*>& path)
{
    int maxCount = -1;

    LinkList<int> cp;

    // 获取最长不下降序列的顶点数、起始顶点下标
    for(int i = 0; i < count.length(); i++)
    {
        if(maxCount < count[i])
        {
            maxCount = count[i];
        }
    }

    cout << "maxCount: " << maxCount << endl;

    for(int i = 0; i < count.length(); i++)
    {
        if(count[i] == maxCount)
        {
            print_max_path(g, i, path, cp);
        }
    }
}
void solutin(int* a, int len)
{
    // 最长序列最长顶点数数组 => 以顶点i为起始顶点的最长序列数为count[i]
    DynamicArray<int> count(len);
    // 最长序列下一顶点数组 => 以顶点i为起始顶点的最长序列中, 下一顶点为path[i]
    DynamicArray<LinkList<int>*> path(len);
    // 最长序列标记数组 => 顶点i在最长序列中时mark[i]为true, 顶点i不在最长序列中时mark[i]为false
    DynamicArray<bool> mark(len);

    SharedPointer<Graph<int, int>> g;

    g = create_graph(a, len);

    init_array(count, path, mark);

    search_max_path(*g, count, path, mark);

    print_max_path(*g, count, path);
}
void funcGraph004()
{
    cout << "funcGraph004:" << endl;

    int a[] = {6, 5, 4, 5, 5};
    int len = sizeof(a) / sizeof(a[0]);

    solutin(a, len);
}
