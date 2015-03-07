#include "traveler.h"

Traveler::Traveler(int num):numNode(num), upperbound(INFINITY)/*, graph(num)*/{}

pair<int, int> Traveler::calcCost(TreeNode* n)
{
    int num = n->graph.getNum();
    n->cost = n->cost + n->graph.adjustMatrix();
    pair<int, int> edge = n->graph.maxPartition();
    return edge;
}

int Traveler::buildTree(TreeNode* p, int count)
{
    //cout<<p->count<<endl;
    if (p->count == 0)
    {
        if (p->flag) cout<<"With edge:("<<p->edge.first+1<<","<<p->edge.second+1<<")"<<p->cost<<" "<<p->count<<endl;
        else cout<<"Without edge:("<<p->edge.first+1<<","<<p->edge.second+1<<")"<<p->cost<<" "<<p->count<<endl;
        upperbound = (upperbound>p->cost)?p->cost:upperbound;
        cout<<"upperbound:"<<upperbound<<" "<<p->count<<endl;
        return upperbound;
    }
    pair<int, int> edge = calcCost(p);
    if (upperbound < p->cost) 
    {
        cout<<p->edge.first+1<<","<<p->edge.second+1<<" "<<p->cost<<endl;
        return upperbound;}
    if (p->flag) cout<<"With edge:("<<p->edge.first+1<<","<<p->edge.second+1<<")"<<p->cost<<" "<<p->count<<endl;
    else cout<<"Without edge:("<<p->edge.first+1<<","<<p->edge.second+1<<")"<<p->cost<<" "<<p->count<<endl;
    int cost = 0;
    TreeNode* lc = new TreeNode(true, numNode, p->graph, edge, p->count-1);
    lc->graph.setInvailable(edge.second, edge.first);
    lc->graph.resetMatrix(edge.first, edge.second);
    int lcost = p->cost + lc->graph.adjustMatrix();
    lc->cost = lcost;
    p->leftChild = lc;
    lc->parent = p;
    int rcost = INFINITY;
    TreeNode* rc;
    if (p->count > 2)
    {
        rc = new TreeNode(false, numNode, p->graph, edge, p->count);
        //rc->graph.setInvailable(edge.second, edge.first);
        rc->graph.setInvailable(edge.first, edge.second);
        rcost = p->cost + rc->graph.adjustMatrix();
    }
    else rc = new TreeNode(false, numNode, p->graph, edge, p->count);
    p->rightChild = rc;
    rc->parent = p;
    rc->cost = rcost;
   // --count;
    /*cout<<"At level#"<<count+1<<" Cost of parent:"<<p->cost<<",Cost of left child:"<<lcost<<",Cost of right child:"<<rcost<<endl;
    cout<<"Weight matrix of solution set with edge("<<edge.first+1<<","<<edge.second+1<<"):"<<endl;
    lc->graph.printMatrix();
    cout<<"Weight matrix of solution set without edge("<<edge.first+1<<","<<edge.second+1<<"):"<<endl;
    rc->graph.printMatrix();//*/

    if (lcost <= rcost)
    {
        cost = buildTree(p->leftChild, p->count);
        if ((cost > rcost) && (p->count > 2))
        {
            cost = buildTree(p->rightChild, p->count);
        }
    }
    else if(p->count > 2)
    {
        cost = buildTree(p->rightChild, p->count);
        if (cost > lcost) cost = buildTree(p->leftChild, p->count);
    }
    return cost;
}

bool isSmaller(const TreeNode* p1, const TreeNode* p2)
{
    return p1->cost < p2->cost;
}

bool Traveler::searchPath(TreeNode* root/*, int count*/)
{
    /*if (p)
    {
        if (p->count == 0)
        {
            if (p->cost == upperbound)
            {
                cout<<p->cost<<" "<<p->edge.first+1<<","<<p->edge.second+1<<endl;
                TreeNode* s = p;
                while(s != NULL) 
                {
                    //cout<<s->edge.first+1<<" "<<s->edge.second+1<<endl;
                    if (s->flag)
                        path.push_back(s->edge);
                    s = s->parent;
                    //if (!s->flag && s!=NULL)
                    //    s = s->parent;
                }
                return true;
            }
            return false;
        }
        if (searchPath(p->leftChild/*, p->count - 1*x/))
            return true;
        else 
            searchPath(p->rightChild/*, p->count - 1*x/);
    }//*/
    stack<TreeNode *> st;
    st.push(root);
    TreeNode* p;
    while (!st.empty())
    {
        p = st.top();
        st.pop();
        if (p->count == 0)
        {
            if (p->cost == upperbound)
            {
                TreeNode* s = p;
                while(s != NULL) 
                {
                    //cout<<s->edge.first+1<<" "<<s->edge.second+1<<endl;
                    if (s->flag)
                        path.push_back(s->edge);
                    s = s->parent;
                    //if (!s->flag && s!=NULL)
                    //    s = s->parent;
                }
                break;
            }
        }
        if (p->leftChild && p->rightChild)
        {
            if (p->leftChild->cost < p->rightChild->cost)
            {
                st.push(p->rightChild);
                st.push(p->leftChild);
            }
            else
            { 
                st.push(p->leftChild);
                st.push(p->rightChild);
            }
        }
    }//*/
}

bool isFirstSmaller(const pair<int, int>& p1, const pair<int, int>& p2)
{
    return p1.first < p2.first;
}

bool isSecondSamller(const pair<int, int>& p1, const pair<int, int>& p2)
{
    return p1.second < p2.second;
}

bool isEqual(const pair<int, int>&p1, const pair<int, int>& p2)
{
    return (p1.first == p2.first && p1.second == p2.second);
}

void Traveler::printPath()
{
    for(int i = 0; i < path.size(); ++i)
        cout<<path[i].first+1<<","<<path[i].second+1<<" ";
    cout<<endl;//*/
    //sort(path.begin(), path.end(), isSecondSamller);
    stable_sort(path.begin(), path.end(), isFirstSmaller);
    //for(int i = 0; i < path.size(); ++i)
    //    cout<<path[i].first+1<<","<<path[i].second+1<<endl;
    //*///vector<pair<int, int> >::iterator end_unique = unique(path.begin(), path.end(), isEqual);
    //path.erase(end_unique, path.end());
    cout<<endl;
    /*for(int i = 0; i < path.size(); ++i)
        cout<<path[i].first+1<<","<<path[i].second+1<<endl;
    //*/int j = 0;
    cout<<path[j].first+1<<"->";
    for (int i = path.size(); i > 1; --i)
    {
        cout<<path[j].second + 1<<"->";
        j = path[j].second;
    }
    cout<<path[j].second+1<<endl;
}

void Traveler::travel()
{
    //ofstream ofile("m.txt",ios::out);
    Edge** matrix = new Edge*[numNode];
    int count = numNode;
    for (int i = 0; i < numNode; ++i)
        matrix[i] = new Edge[numNode];
    srand((unsigned int)time(0));
    int w = 0;
    for (int i = 0; i < numNode; ++i)
    {
        for (int j = 0; j < numNode; ++j)
        {
            int r = rand()%100 + 1;
            while (r == w)
                r = rand()%100 + 1;
            w = r;
            matrix[i][j].setWeight(w);
            //matrix[j][i].setWeight(w);
            //ofile<<w<<" ";
        }
        //ofile<<endl;
        matrix[i][i].setWeight(INFINITY);
    }//*/
    /*for(int i = 0; i < numNode; ++i)
    {
        for (int j = 0; j < numNode; ++j)
        {
            ofile<<matrix[i][j].getWeight()<<'\t';
        }
        ofile<<endl;
    }
    //*/
    /*ifstream infile("data.txt", ios::in);
    for (int i = 0; i < numNode; ++i)
    {
        for (int j = 0; j < numNode; ++j)
        {
            infile>>w;
            matrix[i][j].setWeight(w);
        }
    } 
    infile.close();//*/
    Graph g(numNode);
    g.initiallize(matrix);
    TreeNode* root = new TreeNode(false, numNode, g, pair<int, int>(0, 0), count);
    TreeNode* p = root;
    cout<<"origin weight matrix:"<<endl;
    p->graph.printMatrix();
    int c = buildTree(p, count);
    //int c = BestFirst(p, count);
    cout<<"minimum cost:"<<upperbound<<endl;
    searchPath(p/*, count*/);
    cout<<"minimum path is:"<<endl;
    printPath();
}
