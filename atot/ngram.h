#include <iostream>
#define MAXWORDLEN 50 
#define MAXSPELLLEN 64
#define HEAD_LEN 920 
#define LEXICON_LEN 44404
#define BODY_LEN 329814 
#define UNIGRAM_LEN 42626
#define BIGRAM_LEN 2751825


using namespace std;

typedef struct HeadWordItem{
    int Wordid;
    char WordString[MAXWORDLEN];
    char ChineseString[MAXSPELLLEN];
    int freq;
    int BodyOffset;
}HeadWordItem;

typedef struct BodyWordItem{
    int Wordid;
    int freq;
}BodyWordItem;

typedef struct Lexicon{
    int Item_Number_of_Lexicon_Head;
    int Item_Number_of_Lexicon_Body;
    HeadWordItem LexiconHead[HEAD_LEN];
    BodyWordItem LexiconBody[BODY_LEN];
}Lexicon;

typedef struct WordSpell{
    string word;
    string spell;
}WordSpell;

typedef struct Word{
    string word;
    int Wordid;
    int freq;
}Word;

typedef struct Bigram{
    string word1;
    string word2;
    int freq;
}Bigram;

