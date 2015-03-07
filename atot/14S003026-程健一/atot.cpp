#include <iostream>
#include "ngram.h"
#include <vector>
#include <cctype>
#include <string.h>
#include <fstream>

using namespace std;

vector<string> segment(string input, Lexicon* lexicon);
string viterbi(Lexicon* lexicon, string input);

int main()
{
    FILE *fp = fopen("words.txt", "rb");
    Lexicon* lexicon = new Lexicon;
    fread(lexicon, sizeof(Lexicon), 1, fp);
    cout<<"Input a string:";
    string input;
    getline(cin, input);
    cout<<viterbi(lexicon, input)<<endl;
    delete lexicon;
}

vector<string> segment(string input, Lexicon* lexicon)
{
    vector<string> strlist;
    int i = 0;
    int j = 0;
    while (input[j] != '\0')
    {
        if (input[j] == ' ')
        {
            strlist.push_back(input.substr(i, j - i));
            i = j + 1;
        }
        ++j;
    }
    strlist.push_back(input.substr(i, j - i));
    return strlist;
}

string viterbi(Lexicon* lexicon, string input)
{
    vector<string> seglist = segment(input, lexicon);
    vector<string>::iterator siter = seglist.begin();
    int num = seglist.size();
    double** transition = new double*[HEAD_LEN];
    double** delta = new double*[HEAD_LEN];
    double* pi = new double[HEAD_LEN];
    double** out = new double*[HEAD_LEN];
    int** opath = new int*[HEAD_LEN];
    for (int i = 0; i < HEAD_LEN; ++i)
    {
        transition[i] = new double[HEAD_LEN];
        delta[i] = new double[num];
        out[i] = new double[num];
        opath[i] = new int[num];
        int j = 0;
        for (siter = seglist.begin(); siter != seglist.end(); ++siter)
        {
            string spell = lexicon->LexiconHead[i].ChineseString;
            spell = spell.erase(spell.size() - 1);
            if (spell.compare(*siter) == 0)
                out[i][j] = 1;
            else out[i][j] = 0;
            ++j;
        }
        pi[i] = (double)lexicon->LexiconHead[i].freq/(double)lexicon->Item_Number_of_Lexicon_Head;
    }
    for (int i = 0; i < HEAD_LEN; ++i)
    {
        for (int j = 0; j < HEAD_LEN; ++j)
        {
            int bfreq = 1;
            int ub = (i < HEAD_LEN - 1)?lexicon->LexiconHead[i+1].BodyOffset:BODY_LEN;
            for (int k = lexicon->LexiconHead[i].BodyOffset; k < ub; ++k)
            {
                if (lexicon->LexiconBody[k].Wordid == lexicon->LexiconHead[j].Wordid)
                {
                    bfreq = bfreq + lexicon->LexiconBody[k].freq;
                    break;
                }
            }
            transition[i][j] = (double)bfreq/(double)(lexicon->Item_Number_of_Lexicon_Body + 1);
        }
    }
    string path = "";
    double max = 0;
    int maxid = 0;
    for (int i = 0; i < HEAD_LEN; ++i)
    {
        delta[i][0] = pi[i]*out[i][0];
        opath[i][0] = 0;
    }
    for (int t = 1; t < num; ++t)
    {
        for (int i = 0; i < HEAD_LEN; ++i)
        {
            max = 0;
            maxid = 0;
            for (int j = 0; j < HEAD_LEN; ++j)
            {
                double temp = delta[j][t-1]*transition[j][i]*out[i][t];
                if (max < temp)
                {
                    max = temp;
                    maxid = j;
                }
            }
            delta[i][t] = max;
            opath[i][t] = maxid;
        }
    }
    max = 0;
    maxid = 0;
    for (int i = 0; i < HEAD_LEN; ++i)
    {
        if (max < delta[i][num-1])
        {
            max = delta[i][num-1];
            maxid = i;
        }
    }
    for (int i = num - 1; i >= 0 ; --i)
    {
        string str = lexicon->LexiconHead[maxid].WordString;
        path = str + path;
        maxid = opath[maxid][i];
    }
    return path;
}
