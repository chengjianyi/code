#include "lcs.h"

typedef pair<string, string> StrPair;

int main()
{
    string s1, s2, s3;
    //cout<<"Input str1, str2, str3:"<<endl;
    //cin>>s1>>s2>>s3;
    StrPair sp[20];
    StrPair sp1[10];
    int len[10] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    double t = 0;
    srand((unsigned int)time(0));
    LCS lcs;
    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            char c = rand()%26 + 'a';
            sp[i].first = sp[i].first + c;
        }
        for (int j = 0; j < 10; ++j)
        {
            char c = rand()%26 + 'a';
            sp[i].second = sp[i].second + c;
        }
        cout<<"String1:"<<sp[i].first<<endl;
        cout<<"String2:"<<sp[i].second<<endl;
        cout<<"Using recursion: "<<lcs.LCS_Recursion(sp[i].first, sp[i].second)<<endl;
        //cout<<"Using dynamic programming: ";
        clock_t s,e;
        s = clock();
        lcs.LCS_DP(sp[i].first, sp[i].second);
        e = clock();
        t += (double)(e-s)/CLOCKS_PER_SEC;
    }
    cout<<t<<endl;
    /*for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < len[i]; ++j)
        {
            char c = rand()%26 + 'a';
            sp1[i].first = sp1[i].first + c; 
        }
        for (int j = 0; j < len[i]; ++j)
        {
            char c = rand()%26 + 'a';
            sp1[i].second = sp1[i].second + c;
        }
        cout<<"String1:"<<sp1[i].first<<endl;
        cout<<"String2:"<<sp1[i].second<<endl;
        //cout<<"Using recursion: "<<lcs.LCS_Recursion(sp[i].first, sp[i].second)<<endl;
        cout<<"Using dynamic programming: ";
        clock_t s,e;
        s = clock();
        lcs.LCS_DP(sp1[i].first, sp1[i].second);
        e = clock();
        cout<<"Lengh = "<<len[i]<<": "<<(double)(e-s)/CLOCKS_PER_SEC<<endl;
    }
    cout<<sp[1].first<<endl;
    cout<<sp[5].first<<endl;
    cout<<sp[10].first<<endl;
    clock_t s, e;
    s = clock();
    lcs.LCS_DP(sp[1].first, sp[5].first, sp[10].first);
    e = clock();
    cout<<(double)(e-s)/CLOCKS_PER_SEC<<endl;//*/
}
