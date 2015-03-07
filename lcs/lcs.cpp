#include "lcs.h"

string LCS::LCS_Recursion(string s1, string s2)
{
    if (s1.size() == 0 || s2.size() == 0) return ""; 
    if (s1[s1.size() - 1] == s2[s2.size() - 1])
        return (LCS_Recursion(s1.substr(0, s1.size() - 1), s2.substr(0, s2.size() - 1)) + s1[s1.size() - 1]);
    else
    {
        string str1 = LCS_Recursion(s1.substr(0, s1.size() - 1), s2);
	    string str2 = LCS_Recursion(s1, s2.substr(0, s2.size() - 1));
       	return (str1.size()>str2.size())?str1:str2;
    }
}

void LCS::LCS_DP(string s1, string s2)
{
    int m = s1.size();
    int n = s2.size();
    int** maxLen = new int*[m+1];
    int** path = new int*[m+1];
    for (int i = 0; i < m+1; ++i)
    {
        maxLen[i] = new int[n+1];
        path[i] = new int[n+1];
    }
    for (int i = 0; i < m+1; ++i)
        maxLen[i][0] = 0;
    for (int j = 0; j < n+1; ++j)
        maxLen[0][j] = 0;
    for (int i = 1; i < m+1; ++i)
    {
        for (int j = 1; j < n+1; ++j)
        {
            if (s1[i-1] == s2[j-1])
            {
                maxLen[i][j] = maxLen[i-1][j-1] + 1;
                path[i][j] = 1;
            }
            else
            {
                maxLen[i][j] = (maxLen[i-1][j]>maxLen[i][j-1])?maxLen[i-1][j]:maxLen[i][j-1];
                if (maxLen[i-1][j] > maxLen[i][j-1]) path[i][j] = 2;
                else path[i][j] = 3;
            }
        }
    }
    printPath(path, s1, m, n);
    cout<<endl;
    for (int i = 0; i < m+1; ++i)
    {
        delete[] maxLen[i];
        delete[] path[i];
    }
    delete[] maxLen;
    delete[] path;
}

void LCS::printPath(int**p, string s, int i, int j)
{
    if (i == 0 || j == 0) return;
    if (p[i][j] == 1)
    {
        printPath(p, s, i-1, j-1);
        cout<<s[i-1];
    }
    else if (p[i][j] == 2)
        printPath(p, s, i - 1, j);
    else printPath(p, s, i, j - 1);
}

void LCS::LCS_DP(string s1, string s2, string s3)
{
    int l = s1.size();
    int m = s2.size();
    int n = s3.size();
    int*** maxLen = new int**[l+1];
    int*** path = new int**[l+1];
    for (int i = 0; i < l + 1; ++i)
    {
        maxLen[i] = new int*[m+1];
        path[i] = new int*[m+1];
        for (int j = 0; j < m + 1; ++j)
        {
            maxLen[i][j] = new int[n+1];
            path[i][j] = new int[n+1];
        }
    }
    for (int i = 0; i < l + 1; ++i)
        for (int j = 0; j < m + 1; ++j)
            maxLen[i][j][0] = 0;
    for (int j = 0; j < m + 1; ++j)
        for (int k = 0; k < n + 1; ++k)
            maxLen[0][j][k] = 0;
    for (int k = 0; k < n + 1; ++k)
        for (int i = 0; i < l + 1; ++i)
            maxLen[i][0][k] = 0;
    for (int i = 1; i < l + 1; ++i)
    {
        for (int j = 1; j < m + 1; ++j)
        {
            for (int k = 1; k < n + 1; ++k)
            {
                if (s1[i-1] == s2[j-1] && s1[i-1] == s3[k-1])
                {
                    maxLen[i][j][k] = maxLen[i-1][j-1][k-1] + 1;
                    path[i][j][k] = 1;
                }
                else if (s1[i-1] == s2[j-1] && s1[i-1] != s3[k-1])
                {
                    maxLen[i][j][k] = (maxLen[i-1][j-1][k]>maxLen[i][j][k-1])?maxLen[i-1][j-1][k]:maxLen[i][j][k-1];
                    if (maxLen[i-1][j-1][k] > maxLen[i][j][k-1]) path[i][j][k] = 2;
                    else path[i][j][k] = 3;
                }
                else if (s1[i-1] != s2[j-1] && s1[i-1] == s3[k-1])
                {
                    maxLen[i][j][k] = (maxLen[i-1][j][k-1]>maxLen[i][j-1][k])?maxLen[i-1][j][k-1]:maxLen[i][j-1][k];
                    if (maxLen[i-1][j][k-1] > maxLen[i][j-1][k]) path[i][j][k] = 4;
                    else path[i][j][k] = 5;
                }
                else if (s1[i-1] != s2[j-1] && s2[j-1] == s3[k-1])
                {
                    maxLen[i][j][k] = (maxLen[i][j-1][k-1]>maxLen[i-1][j][k])?maxLen[i][j-1][k-1]:maxLen[i-1][j][k];
                    if (maxLen[i][j-1][k-1] > maxLen[i-1][j][k]) path[i][j][k] = 6;
                    else path[i][j][k] = 7;
                }
                else
                {
                    maxLen[i][j][k] = max(maxLen[i-1][j][k], maxLen[i][j-1][k], maxLen[i][j][k-1], maxLen[i-1][j-1][k], maxLen[i-1][j][k-1], maxLen[i][j-1][k-1]).first;
                    path[i][j][k] = max(maxLen[i-1][j][k], maxLen[i][j-1][k], maxLen[i][j][k-1], maxLen[i-1][j-1][k], maxLen[i-1][j][k-1], maxLen[i][j-1][k-1]).second;
                }
            }
        }
    }
    printPath(path, s1, l, m, n);
    cout<<endl;
    for (int i = 0; i < l+1; ++i)
    {
        for (int j = 0; j < m+1; ++j)
        {
            delete[] maxLen[i][j];
            delete[] path[i][j];
        }
        delete[] maxLen[i];
        delete[] path[i];
    }
} 

void LCS::printPath(int***p, string s, int i, int j, int k)
{
    if (i == 0 || j == 0 || k == 0) return;
    switch(p[i][j][k])
    {
        case 1:
            printPath(p, s, i-1, j-1, k-1);
            cout<<s[i-1];
            break;
        case 2:
            printPath(p, s, i-1, j-1, k);
            break;
        case 3:
            printPath(p, s, i, j, k-1);
            break;
        case 4:
            printPath(p, s, i-1, j, k-1);
            break;
        case 5:
            printPath(p, s, i, j-1, k);
            break;
        case 6:
            printPath(p, s, i, j-1, k-1);
            break;
        case 7:
            printPath(p, s, i-1, j, k);
            break;
        case 8:
            printPath(p, s, i-1, j, k);
            break;
        case 9:
            printPath(p, s, i, j-1, k);
            break;
        case 10:
            printPath(p, s, i, j, k-1);
            break;
        case 11:
            printPath(p, s, i-1, j-1, k);
            break;
        case 12:
            printPath(p, s, i-1, j, k-1);
            break;
        case 13:
            printPath(p, s, i, j-1, k-1);
        default:
            break;
    }
}

pair<int, int> LCS::max(int a, int b, int c, int d, int e, int f)
{
    pair<int, int> max(-1, 0);
    if (max.first < a)
    {
        max.first = a;
        max.second = 8;
    }
    if (max.first < b)
    {
        max.first = b;
        max.second = 9;
    }
    if (max.first < c)
    {
        max.first = c;
        max.second = 10;
    }
    if (max.first < d)
    {
        max.first = d;
        max.second = 11;
    }
    if (max.first < e)
    {
        max.first = e;
        max.second = 12;
    }
    if (max.first < f)
    {
        max.first = f;
        max.second = 13;
    }
    return max;
}
