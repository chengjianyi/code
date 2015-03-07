#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <cctype>
#include <vector>
#include "ngram.h"

using namespace std;

int main()
{
    Lexicon* lexicon = new Lexicon;
    ifstream ffile, lfile, bfile;
    ffile.open("word_freq1.txt",ios::in);
    bfile.open("Bigram_freq1.txt", ios::in);
    lfile.open("lexicon1.txt", ios::in);
    WordSpell* ws = new WordSpell[LEXICON_LEN];
    Bigram* b = new Bigram[BIGRAM_LEN];
    Word* words = new Word[UNIGRAM_LEN];
    int k = 0;
    while (k < LEXICON_LEN)
    {
        string line = "";
        getline(lfile, line);
        int i = line.find_first_of('\t');
        string word = line.substr(0,i);
        string spell = line.substr(i+1);
        ws[k].word = word;
        ws[k].spell = spell;
        ++k;
    }
    k = 0;
    lfile.close();
    while (k < BIGRAM_LEN)
    {
        bfile>>b[k].word1>>b[k].word2>>b[k].freq;
        ++k;
    }
    bfile.close();
    k = 0;
    while (k < UNIGRAM_LEN)
    {
        string word = "";
        int freq = 0;
        ffile>>word>>freq;
        words[k].word = word;
        words[k].Wordid = k+1;
        words[k].freq = freq;
        ++k;
    }
    ffile.close();
    k = 0;
    int id = 0;
    int offset = 0;
    while (k < UNIGRAM_LEN)
    {
        if ((words[k].word.size() == 3) && (words[k].freq > 1000))
        {
            lexicon->LexiconHead[id].Wordid = words[k].Wordid;
            strcpy(lexicon->LexiconHead[id].WordString, (words[k].word).c_str());
            lexicon->LexiconHead[id].freq = words[k].freq;
            lexicon->LexiconHead[id].BodyOffset = offset;
            for (int i = 0; i < BIGRAM_LEN; ++i)
            {
                if ((words[k].word).compare(b[i].word1) == 0 && b[i].word2.size() == 3)
                {
                    for (int j = 0; j < UNIGRAM_LEN; ++j)
                    {
                        if ((words[j].word).compare(b[i].word2) == 0)
                        {
                            lexicon->LexiconBody[offset].Wordid = words[j].Wordid;
                            lexicon->LexiconBody[offset].freq = b[i].freq;
                            lexicon->Item_Number_of_Lexicon_Body += b[i].freq;
                            ++offset;
                            break;
                        }
                    }
                }
            }
            bool flag = true;
            for (int i = 0; i < LEXICON_LEN; ++i)
            {
                if ((words[k].word).compare(ws[i].word) == 0)
                {
                    string::iterator iter = ws[i].spell.begin();
                    while (*iter != '\0')
                    {
                        if (isdigit(*iter))
                            ws[i].spell.erase(iter);
                        ++iter;
                    }
                    strcpy(lexicon->LexiconHead[id].ChineseString, ws[i].spell.c_str());
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                string spell = "ERROR";
                strcpy(lexicon->LexiconHead[id].ChineseString, spell.c_str());  
            }
            lexicon->Item_Number_of_Lexicon_Head += words[k].freq;
            ++id;
        }
        ++k;
    }
    ffile.close();
    FILE* fp = fopen("words.txt","w+b");
    fwrite(lexicon, sizeof(Lexicon), 1, fp);
    fclose(fp);
    delete lexicon;
    delete[] ws;
    delete[] words;
    delete[] b;
    return 0;
}

