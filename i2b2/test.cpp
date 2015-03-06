#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "ngram.h"

using namespace std;

int main()
{
    Lexicon* lexicon = new Lexicon;
    ifstream ffile, lfile;
    ffile.open("word_freq.txt",ios::in);
    lfile.open("lexicon.txt", ios::in);
    WordSpell* ws = new WordSpell[4];
    int k = 0;
    while (k < 4)
    {
        string line = "";
        getline(lfile, line);
        //cout<<line<<endl;
        int i = line.find_first_of('\t');
        string word = line.substr(0,i);
        string spell = line.substr(i+1);
        cout<<word<<" "<<spell<<endl;
        ws[k].word = word;
        ws[k].spell = spell;
        ++k;
    }
    k = 0;
    while (k < 4)
    {
        int id = 0;
        HeadWordItem hwi;
        string word = "";
        int freq = 0;
        ffile>>word>>freq;
        hwi.Wordid = k;
        hwi.freq = freq;
        for (int i = 0; i < 4; ++i)
        {
            if (word.compare(ws[i].word) == 0)
            {
                char* spell = ""; 
                spell = ws[i].spell.c_str();
                strcpy(hwi.ChineseString, spell);
            }
            else
            {
                char* spell = "ERROR";
                strcpy(hwi.ChineseString, spell);
            }
        }
    }
    return 0;
}
