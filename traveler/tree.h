#include <iostream>
#include "graph.h"

using namespace std;

class TreeNode
{
public:
    bool flag;
    pair<int, int> edge;
    int cost;
    int count;
    Graph graph;
    TreeNode* parent;
    TreeNode* leftChild;
    TreeNode* rightChild;
    TreeNode(bool f, int num, Graph& g, pair<int, int> e, int c);
};

