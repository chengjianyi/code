#include "graph.h"

Edge::Edge():weight(0), deleted(false){}

const int& Edge::getWeight()
{
    return weight;
}

const bool& Edge::getDeleted()
{
    return deleted;
}

void Edge::setWeight(const int& w)
{
    weight = w;
}

void Edge::setDeleted(const bool& d)
{
    deleted = d;
}

/**------------------------------------------------------**/

Graph::Graph():numNode(0)
{
    matrix = NULL;
}

Graph::Graph(const int& num):numNode(num)
{
    matrix = new Edge*[num];
    for (int i = 0; i < num; ++i)
        matrix[i] = new Edge[num];
}

Graph::~Graph()
{
    for (int i = 0; i < numNode; ++i)
        delete matrix[i];
}

const int& Graph::getNum()
{
    return numNode;
}

void Graph::initiallize(Edge** m)
{
    for (int i = 0; i < numNode; ++i)
        for (int j = 0; j < numNode; ++j)
        {
            int w = m[i][j].getWeight();
            matrix[i][j].setWeight(w);
        }
}
void Graph::printMatrix()
{
    ofstream outfile("out.txt", ios::out|ios::app);
    cout.flags(ios::left);
    for (int i = 0; i < numNode; ++i)
    {
        bool flag = false;
        for (int j = 0; j < numNode; ++j)
            if (!matrix[i][j].getDeleted())
            {
                if (matrix[i][j].getWeight() == INFINITY)
                {
                    cout<<setw(2)<<"Inf"<<"("<<i+1<<','<<j+1<<")"<<" \t";
                    outfile<<setw(2)<<"Inf"<<"("<<i+1<<','<<j+1<<")"<<" \t";
                }
                else
                {
                    cout<<setw(2)<<matrix[i][j].getWeight()<<"("<<i+1<<','<<j+1<<")"<<" \t";
                    outfile<<setw(2)<<matrix[i][j].getWeight()<<"("<<i+1<<','<<j+1<<")"<<" \t";
                }
                flag = true;
            }
        if (flag) 
        {
            cout<<endl;
            outfile<<endl;
        }
    }
    outfile.close();
}

void Graph::resetMatrix(int x, int y)
{
    for (int i = 0; i < numNode; ++i)
    {
        matrix[x][i].setDeleted(true);
        matrix[i][y].setDeleted(true);
    }
}

void Graph::setNum(int num)
{
    numNode = num;
    matrix = new Edge*[num];
    for (int i = 0; i < num; ++i)
        matrix[i] = new Edge[num];
}

int Graph::adjustRow()
{
    int min = 0;
    int sum = 0;
    bool flaglist[numNode];
    for (int i = 0; i < numNode; ++i)
    {
        bool flag = true;
        for(int j = 0; j < numNode; ++j)
        {
            if (!matrix[i][j].getDeleted())
            {
                flag = false;
                break;
            }
        }
        flaglist[i] = flag;
    }
    for (int i = 0; i < numNode; ++i)
    {
        if (flaglist[i]) continue;
        min = INFINITY;
        for (int j = 0; j < numNode; ++j)
            if (!matrix[i][j].getDeleted())
                min = (min > matrix[i][j].getWeight())?matrix[i][j].getWeight():min;
        for (int j = 0; j < numNode; ++j)
            if (!matrix[i][j].getDeleted() && (matrix[i][j].getWeight() != INFINITY))
                matrix[i][j].setWeight(matrix[i][j].getWeight() - min);
        sum = sum + min;
    }
    return sum;
}

bool Graph::checkColumn()
{
    bool check = true;
    for (int i = 0; i < numNode; ++i)
    {
        bool flag = false;
        for (int j = 0; j < numNode; ++j)
            if (!matrix[j][i].getDeleted())
                if (matrix[j][i].getWeight() == 0)
                {
                    flag = true;
                    break;
                }
        if (!flag) return false;
    }
    return check;
}

int Graph::adjustCol()
{
    int min = 0;
    int sum = 0;
    bool flaglist[numNode];
    for (int i = 0; i < numNode; ++i)
    {
        bool flag = true;
        for(int j = 0; j < numNode; ++j)
        {
            if (!matrix[j][i].getDeleted())
            {
                flag = false;
                break;
            }
        }
        flaglist[i] = flag;
    }
    for (int i = 0; i < numNode; ++i)
    {
        if (flaglist[i]) continue;
        min = INFINITY;
        for (int j = 0; j < numNode; ++j)
            if (!matrix[j][i].getDeleted())
                min = (min > matrix[j][i].getWeight())?matrix[j][i].getWeight():min;
        for (int j = 0; j < numNode; ++j)
            if (!matrix[j][i].getDeleted() && (matrix[j][i].getWeight() != INFINITY))
                   matrix[j][i].setWeight(matrix[j][i].getWeight() - min);
        sum = sum + min;
    }
    return sum;
}

int Graph::adjustMatrix()
{
    int cost = 0;
    cost = adjustRow();
    if (!checkColumn())
        cost = cost + adjustCol();
    return cost;
}

pair<int, int> Graph::maxPartition()
{
    vector<pair<int, int> > vec;
    for (int i = 0; i < numNode; ++i)
    {
        for (int j = 0; j < numNode; ++j)
        {
            if ((matrix[i][j].getWeight() == 0)&&(!matrix[i][j].getDeleted()))
            {   
                vec.push_back(pair<int, int>(i,j));
            }
        }
    }
    int max = 0;
    pair<int, int> maxid(0, 0);
    int temp1, temp2;
    for (int i = 0; i < vec.size(); ++i)
    {
        int x = vec[i].first;
        int y = vec[i].second;
        int minX = INFINITY;
        int minY = INFINITY;
        for (int j = 0; j < numNode; ++j)
            if ((minX > matrix[x][j].getWeight()) && (j != y) && (!matrix[x][j].getDeleted())) minX = matrix[x][j].getWeight(); 
        for (int j = 0; j < numNode; ++j)
            if ((minY > matrix[j][y].getWeight()) && (j != x) && (!matrix[j][y].getDeleted())) minY = matrix[j][y].getWeight();
        if (max < (minX + minY))
        {
            max = minX + minY;
            maxid.first = x;
            maxid.second = y;
        }
    }
    return maxid;
}

void Graph::setInvailable(int x, int y)
{
    matrix[x][y].setWeight(INFINITY);
}

int Graph::getMatrixItem(int x, int y)
{
    return matrix[x][y].getWeight();
}

bool Graph::getItemDeleted(int x, int y)
{
    return matrix[x][y].getDeleted();
}

Graph& Graph::operator=(Graph& g)
{
    numNode = g.getNum();
    for (int i = 0; i < numNode; ++i)
        for (int j = 0; j < numNode; ++j)
        {
            matrix[i][j].setWeight(g.getMatrixItem(i, j));
            matrix[i][j].setDeleted(g.getItemDeleted(i, j));
        }
    return *this;
} 
