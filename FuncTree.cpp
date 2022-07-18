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
            /*
                8 4 2 1
                9 4 2 1
                10 5 2 1
                11 6 3 1
                7 3 1
             */
            cout << node->value << " ";

            // 输出完毕后, 移动节点
            node = node->parent;
        }
        cout << endl;
    }
    cout << "bti.degree = " << bti.degree() << endl;    // bti.degree = 2
    cout << "bti.count = " << bti.count() << endl;      // bti.count = 11
    cout << "bti.heigth = " << bti.height() << endl;    // bti.heigth = 4

    // 先序遍历
    SharedPointer<Array<int>> pre = bti.traversal(PreOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " ";     // 1 2 4 8 9 5 10 3 6 11 7
    }
    cout << endl;
    // 中序遍历
    SharedPointer<Array<int>> in = bti.traversal(InOrder);
    for(int i = 0; i < in->length(); i++)
    {
        cout << in->array()[i] << " ";      // 8 4 9 2 10 5 1 11 6 3 7
    }
    cout << endl;
    // 后续遍历
    SharedPointer<Array<int>> post = bti.traversal(PostOrder);
    for(int i = 0; i < post->length(); i++)
    {
        cout << post->array()[i] << " ";    // 8 9 4 10 5 2 11 6 7 3 1
    }
    cout << endl;

    // 层次遍历
    for(bti.begin(); !bti.end(); bti.next())
    {
        cout << bti.current()->value << " ";    // 1 2 3 4 5 6 7 8 9 10 11
    }
    cout << endl;

    BTreeNode<int>* rmnode = bti.find(3);
    SharedPointer<Tree<int>> spti = bti.remove(rmnode);

    // 输出二叉树(按叶子节点到根节点的顺序输出)
    for(int i = 0; i < 5; i++)
    {
        TreeNode<int>* node = bti.find(a[i]);

        while(node)
        {
            /*
                8 4 2 1
                9 4 2 1
                10 5 2 1
             */
            cout << node->value << " ";

            // 输出完毕后, 移动节点
            node = node->parent;
        }
        cout << endl;
    }
    cout << "bti.degree = " << bti.degree() << endl;    // bti.degree = 2
    cout << "bti.count = " << bti.count() << endl;      // bti.count = 7
    cout << "bti.heigth = " << bti.height() << endl;    // bti.heigth = 4

    // 先序遍历
    pre = bti.traversal(PreOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " ";     // 1 2 4 8 9 5 10
    }
    cout << endl;
    // 中序遍历
    in = bti.traversal(InOrder);
    for(int i = 0; i < in->length(); i++)
    {
        cout << in->array()[i] << " ";      // 8 4 9 2 10 5 1
    }
    cout << endl;
    // 后续遍历
    post = bti.traversal(PostOrder);
    for(int i = 0; i < post->length(); i++)
    {
        cout << post->array()[i] << " ";    // 8 9 4 10 5 2 1
    }
    cout << endl;

    // 层次遍历
    for(bti.begin(); !bti.end(); bti.next())
    {
        cout << bti.current()->value << " ";    // 1 2 4 5 8 9 10
    }
    cout << endl;

    // 输出二叉树(按叶子节点到根节点的顺序输出)
    for(int i = 0; i < 5; i++)
    {
        TreeNode<int>* node = spti->find(a[i]);

        while(node)
        {
            /*
                11 6 3
                7 3
             */
            cout << node->value << " ";

            // 输出完毕后, 移动节点
            node = node->parent;
        }
        cout << endl;
    }
    cout << "spti->degree = " << spti->degree() << endl;  // spti->degree = 2
    cout << "spti->count = " << spti->count() << endl;    // spti->count = 4
    cout << "spti->heigth = " << spti->height() << endl;  // spti->heigth = 3

    for(spti->begin(); !spti->end(); spti->next())
    {
        cout << spti->current()->value << " ";  // 3 6 7 11
    }
    cout << endl;

    bti.clear();
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
    cout << "bti.degree = " << bti.degree() << endl;    // bti.degree = 0
    cout << "bti.count = " << bti.count() << endl;      // bti.count = 0
    cout << "bti.heigth = " << bti.height() << endl;    // bti.heigth = 0

    // 先序遍历
    pre = bti.traversal(PreOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " ";     //
    }
    cout << endl;
    // 中序遍历
    in = bti.traversal(InOrder);
    for(int i = 0; i < in->length(); i++)
    {
        cout << in->array()[i] << " ";      //
    }
    cout << endl;
    // 后续遍历
    post = bti.traversal(PostOrder);
    for(int i = 0; i < post->length(); i++)
    {
        cout << post->array()[i] << " ";    //
    }
    cout << endl;

    for(bti.begin(); !bti.end(); bti.next())
    {
        cout << bti.current()->value << " ";    //
    }
    cout << endl;


    cout << "BTree:: clone" << endl;

    BTree<int> oldBti;
    BTreeNode<int> oldRoot;
    BTreeNode<int>* oldParent;

    oldRoot.value = 1;
    oldBti.insert(&oldRoot);

    oldParent = oldBti.find(1);
    oldBti.insert(3, oldParent, RIGHT);
    oldBti.insert(2, oldParent, LEFT);

    oldParent = oldBti.find(2);
    oldBti.insert(5, oldParent, RIGHT);
    oldBti.insert(4, oldParent);

    oldParent = oldBti.find(3);
    oldBti.insert(6, oldParent);
    oldBti.insert(7, oldParent, RIGHT);

    oldParent = oldBti.find(4);
    oldBti.insert(8, oldParent, LEFT);
    oldBti.insert(9, oldParent, RIGHT);

    oldParent = oldBti.find(5);
    oldBti.insert(10, oldParent);

    // 先序输出原树
    cout << "oldBTree::";
    pre = oldBti.traversal(PreOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " "; // oldBTree::1 2 4 8 9 5 10 3 6 7
    }
    cout << endl;

    // 克隆树
    SharedPointer<BTree<int>> cloneBti = oldBti.clone();

    // 先序输出克隆树
    cout << "cloneBti::";
    pre = cloneBti->traversal(PreOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " "; // cloneBti::1 2 4 8 9 5 10 3 6 7
    }
    cout << endl;

    // 原树和克隆树的比较
    cout << (oldBti == *cloneBti) << endl;  // 1
    cout << (oldBti != *cloneBti) << endl;  // 0

    BTree<int> tempBti;
    BTreeNode<int> tempRoot;
    BTreeNode<int>* tempParent;

    tempRoot.value = 0;

    tempBti.insert(&tempRoot);

    tempParent = tempBti.find(0);
    tempBti.insert(6, tempParent);
    tempBti.insert(2, tempParent);

    tempParent = tempBti.find(2);
    tempBti.insert(7, tempParent);
    tempBti.insert(8, tempParent);

    // 先序输出过度树
    cout << "tempBti::";
    pre = tempBti.traversal(PreOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " "; // tempBti::0 6 2 7 8
    }
    cout << endl;

    SharedPointer<BTree<int>> addBti = oldBti.add(tempBti);

    // 先序输出过度树
    cout << "addBti::";
    pre = addBti->traversal(PreOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " "; // addBti::1 8 4 8 9 5 10 5 13 15
    }
    cout << endl;

    // 移除原树中值为3的子树
    oldBti.remove(3);
    cout << "oldBti.remove(3)" << endl; // oldBti.remove(3)

    // 先序输出原树
    cout << "oldBTree::";
    pre = oldBti.traversal(PreOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " "; // oldBTree::1 2 4 8 9 5 10
    }
    cout << endl;
    // 先序输出克隆树
    cout << "cloneBti::";
    pre = cloneBti->traversal(PreOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " "; // cloneBti::1 2 4 8 9 5 10 3 6 7
    }
    cout << endl;

    // 原树和克隆树的比较
    cout << (oldBti == *cloneBti) << endl;  // 0
    cout << (oldBti != *cloneBti) << endl;  // 1

    // 层次遍历
    cout << "LevelOrderTravelsal::";
    pre = cloneBti->traversal(LevelOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " "; // LevelOrderTravelsal::1 2 3 4 5 6 7 8 9 10
    }
    cout << endl;

    // 将树转换为线性结构
    BTreeNode<int>* head = cloneBti->thread(LevelOrder);
    BTreeNode<int>* tail = head;

    // 从头输出链表
    cout << "Thread::head = ";
    while(head)
    {
        tail = head;
        cout << head->value << " "; // Thread::head = 1 2 3 4 5 6 7 8 9 10
        head = head->m_right;
    }
    cout << endl;

    // 从尾输出链表
    cout << "Thread::tail = ";
    while(tail)
    {
        cout << tail->value << " "; // Thread::tail = 10 9 8 7 6 5 4 3 2 1
        tail = tail->m_left;
    }
    cout << endl;

    // 将树转换为线性结构后, 树已被清空, 此时输出空树
    cout << "LevelOrderTravelsal::";
    pre = cloneBti->traversal(LevelOrder);
    for(int i = 0; i < pre->length(); i++)
    {
        cout << pre->array()[i] << " "; // LevelOrderTravelsal::
    }
    cout << endl;
}

// 创建树函数
template <typename T>
BTreeNode<T>* createTree()
{
    BTreeNode<T>* ret;

    static BTreeNode<T> btn[9];

    for(int i = 0; i < 9; i++)
    {
        btn[i].parent = NULL;
        btn[i].value = i;
        btn[i].m_left = NULL;
        btn[i].m_right = NULL;
    }

    btn[0].m_left = &btn[1];
    btn[0].m_right = &btn[2];

    btn[1].parent = &btn[0];
    btn[1].m_left = &btn[3];

    btn[2].parent = &btn[0];
    btn[2].m_left = &btn[4];
    btn[2].m_right = &btn[5];

    btn[3].parent = &btn[1];
    btn[3].m_right = &btn[6];

    btn[4].parent = &btn[2];
    btn[4].m_left = &btn[7];

    btn[5].parent = &btn[2];
    btn[5].m_left = &btn[8];

    btn[6].parent = &btn[3];
    btn[7].parent = &btn[4];
    btn[8].parent = &btn[5];

    ret = btn;

    return ret;
}
// 中序遍历输出树节点函数
template <typename T>
void printTree(BTreeNode<T>* node)
{
    if(node != NULL)
    {
        printTree(node->m_left);
        cout << node->value << " ";
        printTree(node->m_right);
    }
}
// 删除度数为1的节点, 树节点存在父节点指针
template <typename T>
BTreeNode<T>* delOdd1(BTreeNode<T>* node)
{
    BTreeNode<T>* ret = NULL;

    // 判断节点是否为空
    if(node != NULL)
    {
        // 获取该节点的度数
        int degree = (!!node->m_left) + (!!node->m_right);

        // 节点度数为0时, 直接返回自节点
        if(degree == 0)
        {
            // 度数为0时, 返回自节点
            ret = node;
        }
        // 节点度数为1时, 删除节点
        else if(degree == 1)
        {
            // 获取父节点
            BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
            // 获取子节点
            BTreeNode<T>* child = (!!node->m_left) ? node->m_left : node->m_right;

            // 父节点的子节点更新
            if(parent != NULL)
            {
                ((parent->m_left == node) ? parent->m_left : parent->m_right) = child;
            }

            // 子节点的父节点更新
            child->parent = parent;

            // 删除度数为1的节点
            if(node->flag())
            {
                delete node;
            }

            // 返回度数为0/2的节点
            ret = delOdd1(child);
        }
        // 节点度数为2时, 递归删除子节点中度数为1的节点
        else if(degree == 2)
        {
            // 删除左子节点中度数为1的节点
            delOdd1(node->m_left);
            // 删除右子节点中度数为1的节点
            delOdd1(node->m_right);

            // 度数为2时, 返回自节点
            ret = node;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid...");
        }
    }

    return ret;
}
// 删除度数为1的节点, 树节点不存在父指针
template <typename T>
void delOdd2(BTreeNode<T>*& node)
{
    // 判断节点是否为空
    if(node != NULL)
    {
        // 节点度数为1时, 删除节点
        if((!!node->m_left + !!node->m_right) == 1)
        {
            // 获取子节点
            BTreeNode<T>* child = ((node->m_left != NULL) ? node->m_left : node->m_right);

            // 删除子节点
            if(node->flag())
            {
                delete node;
            }

            // 节点赋值
            node = child;

            delOdd2(node);
        }
        // 节点度数为0/2时, 递归删除子节点中度数为1的节点
        else
        {
            delOdd2(node->m_left);
            delOdd2(node->m_right);
        }
    }
}
// 递归线性化树节点 => 中序遍历时线索化, pre本意是前驱节点, 但是一开始却是最前驱节点(左节点: NULL)
template <typename T>
void inOrderThread1(BTreeNode<T>* node, BTreeNode<T>*& pre)
{
    // 判断节点是否为空
    if(node != NULL)
    {
        // 左子树节点线性化
        inOrderThread1(node->m_left, pre);

        // 将左节点和父节点线性化
        node->m_left = pre;
        if(pre != NULL)
        {
            pre->m_right = node;
        }

        // 前节点后移
        pre = node;

        // 将右节点和父节点线性化
        inOrderThread1(node->m_right, pre);
    }
}
template <typename T>
void inOrderThread2(BTreeNode<T>* node, BTreeNode<T>*& head, BTreeNode<T>*& tail)
{
    if(node != NULL)
    {
        BTreeNode<T>* h = NULL;
        BTreeNode<T>* t = NULL;

        inOrderThread2(node->m_left, h, t);

        node->m_left = t;
        if(t != NULL)
        {
            t->m_right = node;
        }

        // 记录头节点地址, 子树线性化后的头节点地址
        head = (h != NULL) ? h : node;

        // 左子树线性化完毕, 右子树线性化开始, 头尾节点重赋空
        h = NULL;
        t = NULL;

        inOrderThread2(node->m_right, h, t);

        node->m_right = h;
        if(h != NULL)
        {
            h->m_left = node;
        }

        // 记录尾节点地址, 子树线性化后的尾节点地址
        tail = (t != NULL) ? t : node;
    }
}
template <typename T>
BTreeNode<T>* inOrderThread(BTreeNode<T>* node)
{
    /*
    BTreeNode<T>* ret = NULL;
    BTreeNode<T>* pre = NULL;

    // 线索化树节点
    inOrderThread1(node, pre);

    // 获取头节点
    while(node != NULL)
    {
        ret = node;
        node = node->m_left;
    }

    return ret;
    */

    BTreeNode<T>* head = NULL;
    BTreeNode<T>* tail = NULL;

    // 线性化树节点
    inOrderThread2(node, head, tail);

    return head;
}
void funcTree003()
{
    cout << "funcTree003::" << endl;

    // 创建树
    BTreeNode<int>* root = createTree<int>();

    // 输出树节点值
    printTree(root);    // 3 6 1 0 7 4 2 8 5
    cout << endl;

    // 将度数为1的树节点删除
    BTreeNode<int>* root1 = delOdd1(root);

    // 输出树节点值
    printTree(root1);    // 6 0 7 2 8
    cout << endl;

    // 将度数为1的树节点删除
    delOdd2(root);

    // 输出树节点值
    printTree(root);    // 6 0 7 2 8
    cout << endl;

    // 线索化树节点
    BTreeNode<int>* link = inOrderThread(root);
    BTreeNode<int>* tail;

    // 输出线性结构节点值
    while(link != NULL)
    {
        tail = link;
        cout << link->value << " "; // 6 0 7 2 8
        link = link->m_right;
    }
    cout << endl;
    // 输出线性结构节点值
    while(tail != NULL)
    {
        cout << tail->value << " "; // 8 2 7 0 6
        tail = tail->m_left;
    }
    cout << endl;
}
