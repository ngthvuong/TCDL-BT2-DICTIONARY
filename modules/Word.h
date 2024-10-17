#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <functional>
#include <string>
#include <vector>

using namespace std;

struct Word
{
    string originalWord;
    string partOfSpeech;
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
    static string getKey(const Word &);
    static int compareKey(const string &, const string &);
    static bool append(Word, WordEntry &);
};
#endif