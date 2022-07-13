#include "FuncTree.h"

#include <iostream>

#include "GTree.h"
#include "Recursion.h"
#include "SharedPointer.h"
#include "BTree.h"

using namespace std;
using namespace DemoData;

void funcTree001()
{
    cout << "Tree::GTree" << endl;

    GTree<char> gtc;
    GTreeNode<char>* parent;

    GTreeNode<char> root;
    root.value = 'A';
    root.parent = NULL;

    // 插入节点
    //gtc.insert('A', NULL);
    gtc.insert(&root);

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

    // 清除树节点
    //gtc.clear();

    // 叶子节点
    const char* degree = "KLFGMIJ";

    // 从尾到头输出树
    for(int i = 0; i < _strlen_(degree); i++)
    {
        TreeNode<char>* node = gtc.find(degree[i]);

        while(node)
        {
            /*
             K->E->B->A->NULL
             L->E->B->A->NULL
             F->B->A->NULL
             G->C->A->NULL
             M->H->D->A->NULL
             I->D->A->NULL
             J->D->A->NULL
            */
            cout << node->value << "->";

            node = node->parent;
        }
        cout << "NULL" << endl;
    }

    for(gtc.begin(); !gtc.end(); gtc.next())
    {
        cout << gtc.current()->value << " ";    // A B C D E F G H I J K L M
    }
    cout << endl;
    for(gtc.begin(); !gtc.end(); gtc.next())
    {
        cout << gtc.current()->value << " ";    // A B C D E F G H I J K L M
    }
    cout << endl;

    // 获取树的度数
    cout << gtc.degree() << endl;   // 3
    // 获取树的节点数
    cout << gtc.count() << endl;    // 13
    // 获取树的最大高度
    cout << gtc.height() << endl;   // 4

    // 清除单个树节点
    GTreeNode<char>* renode = gtc.find('D');
    SharedPointer<Tree<char>> spt = gtc.remove(renode);

    // 从尾到头输出树
    for(int i = 0; i < _strlen_(degree); i++)
    {
        TreeNode<char>* node = spt->find(degree[i]);

        while(node)
        {
            /*
             NULL
             NULL
             NULL
             NULL
             M->H->D->NULL
             I->D->NULL
             J->D->NULL
            */
            cout << node->value << "->";

            node = node->parent;
        }
        cout << "NULL" << endl;
    }

    // 获取树的度数
    cout << gtc.degree() << endl;   // 2
    // 获取树的节点数
    cout << gtc.count() << endl;    // 8
    // 获取树的最大高度
    cout << gtc.height() << endl;   // 4

    // 获取树的度数
    cout << spt->degree() << endl;  // 3
    // 获取树的节点数
    cout << spt->count() << endl;   // 5
    // 获取树的最大高度
    cout << spt->height() << endl;  // 3

    for(spt->begin(); !spt->end(); spt->next())
    {
        cout << spt->current()->value << " ";    // D H I J M
    }
    cout << endl;
}

void funcTree002()
{
    cout << "funcTree002: BTree" << endl;

    BTree<int> bti;

    BTreeNode<int> root;
    root.value = 1;

    bti.insert(&root);

    bti.insert(2, &root);
    bti.insert(3, &root);

    BTreeNode<int>* parent;
    parent = bti.find(2);
    bti.insert(4, parent);
    bti.insert(5, parent);

    parent = bti.find(3);
    bti.insert(6, parent);
    bti.insert(7, parent);

    parent = bti.find(4);
    bti.insert(8, parent);
    bti.insert(9, parent, RIGHT);

    parent = bti.find(5);
    bti.insert(10, parent);

    parent = bti.find(6);
    bti.insert(11, parent, LEFT);

    // 手动指定尾节点元素值集合
    int a[] = {8, 9, 10, 11, 7};

    // 输出二叉树(按叶子节点到根节点的顺序输出)
    for(int i = 0; i < 5; i++)
    {
        TreeNode<int>* node = bti.find(a[i]);

        while(node)
        {
            cout << node->value << " ";

            // 输出完毕后, 移动节点
            node = node->parent;
        }
        cout << endl;
    }
}
