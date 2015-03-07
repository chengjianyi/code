#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;

class LCS{
public:
    string LCS_Recursion(string s1, string s2);
    void printPath(int**p, string s, int i, int j);
    void LCS_DP(string s1, string s2);
    pair<int, int> max(int a, int b, int c, int d, int e, int f/*i, int g*/);
    void printPath(int*** p, string s, int i, int j, int k);
    void LCS_DP(string s1, string s2, string s3);
};
