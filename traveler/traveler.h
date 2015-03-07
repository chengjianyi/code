#include <iostream>
#include "tree.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <stack>

using namespace std;

class Path{
public:
    //vector<pair<int, int> > edges;
    TreeNode* n;
    //int cost;
};//*/

class Traveler
{
private:
    const int numNode;
    vector<pair<int, int> > path;
    vector<TreeNode*> pathVec;
    int upperbound;
public:
    Traveler(int num);
    pair<int, int> calcCost(TreeNode* n);
    int buildTree(TreeNode* p, int count);
    int BestFirst(TreeNode* p, int count);
    bool searchPath(TreeNode* p/*, int count*/);
    void printPath();
    void travel();
};
