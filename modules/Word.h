#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <functional>
#include <string>
#include <vector>

using namespace std;

struct Word
{
    string key;
    string translatedMeaning;
};
struct WordEntry
{
    string key;
    vector<Word> items;
};
class WordService
{
public:
    static Word stringToWord(string &);
    static string getKey(const string &);
    static int compareKey(const string &, const string &);
    static WordEntry createWordEntry(const Word&);
    static bool append(Word, WordEntry &);
};
#endif