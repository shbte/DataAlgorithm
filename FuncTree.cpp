#include "FuncTree.h"

#include <iostream>

#include "GTree.h"
#include "Recursion.h"

using namespace std;
using namespace DemoData;

void funcTree001()
{
    cout << "Tree::GTree" << endl;

    GTree<char> gtc;
    GTreeNode<char>* parent;

    // 插入节点
    gtc.insert('A', NULL);

    parent = gtc.find('A');
    gtc.insert('B', parent);
    gtc.insert('C', parent);
    gtc.insert('D', parent);

    parent = gtc.find('B');
    gtc.insert('E', parent);
    gtc.insert('F', parent);

    parent = gtc.find('C');
    gtc.insert('G', parent);

    parent = gtc.find('D');
    gtc.insert('H', parent);
    gtc.insert('I', parent);
    gtc.insert('J', parent);

    parent = gtc.find('E');
    gtc.insert('K', parent);
    gtc.insert('L', parent);

    parent = gtc.find('H');
    gtc.insert('M', parent);

    // 叶子节点
    const char* degree = "KLFGMIJ";

    // 从尾到头输出树
    for(int i = 0; i < _strlen_(degree); i++)
    {
        TreeNode<char>* node = gtc.find(degree[i]);

        while(node)
        {
            cout << node->value << "->";

            node = node->parent;
        }
        cout << "NULL" << endl;
    }
}
