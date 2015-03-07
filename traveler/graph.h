#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#define INFINITY 99999

using namespace std;

class Edge
{
private:
    int weight;
    bool deleted;
public:
    Edge();
    const int& getWeight();
    const bool& getDeleted();
    void setWeight(const int& w);
    void setDeleted(const bool& d);
};

class Graph
{
private:
    int numNode;
    Edge** matrix;
public:
    Graph();
    Graph(const int& num);
    ~Graph();
    const int& getNum();
    void initiallize(Edge** m);
    void printMatrix();
    void resetMatrix(int x, int y);
    void setNum(int num);
    int adjustRow();
    bool checkColumn();
    int adjustCol();
    int adjustMatrix();
    void setInvailable(int x, int y);
    pair<int, int> maxPartition();
    int getMatrixItem(int x, int y);
    bool getItemDeleted(int x, int y);
    Graph& operator=(Graph& g);
};
