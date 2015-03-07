#include "tree.h"

TreeNode::TreeNode(bool f, int num, Graph& g, pair<int, int> e, int c)
{
    flag = f;
    edge = e;
    graph.setNum(num);
    count = c;
    graph = g;
    parent = NULL;
    leftChild = NULL;
    rightChild = NULL;
}

