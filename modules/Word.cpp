#include "Word.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Word WordService::stringToWord(string &input)
{
    size_t cue1 = input.find('(');
    size_t cue2 = input.find(')');
    if (cue1 == string::npos || cue2 == string::npos || cue2 < cue1)
    {
        throw out_of_range("string not map with word format!");
    }

    size_t ows = 0;
    size_t owl = cue1 - 1;
    size_t pss = cue1;
    size_t psl = cue2 - cue1 + 1;
    size_t tls = cue2 + 2;
    try
    {
        string originalWord = input.substr(ows, owl);
        string partOfSpeech = input.substr(pss, psl);
        string translatedMeaning = input.substr(tls);

        Word word;
        word.key = WordService::getKey(originalWord);
        word.originalWord = originalWord;
        word.partOfSpeech = partOfSpeech;
        word.translatedMeaning = translatedMeaning;
        return word;
    }
    catch (const out_of_range error)
    {
        cout << "input : " << input << endl;
        throw out_of_range(error.what());
    }
}
string WordService::getKey(const string &value)
{
    string result = value;
    for (char &c : result)
    {
        c = tolower(static_cast<unsigned char>(c));
    }
    return result;
}
int WordService::compareKey(const string &key1, const string &key2)
{
    int result = 0;
    if (key1.compare(key2) != 0)
    {
        int length1 = key1.size();
        int length2 = key2.size();
        int compareLength = min(length1, length2);

        string compareKey1 = key1.substr(0, compareLength);
        string compareKey2 = key2.substr(0, compareLength);

        int compareResult = compareKey1.compare(compareKey2);
        if (compareResult == 0)
        {
            result = (length1 == compareLength) ? -1 : 1;
        }
        else if (compareResult < 0)
        {
            result = -1;
        }
        else
        {
            result = 1;
        }
    }

    return result;
}
WordEntry WordService::createWordEntry(const Word &word)
{
    WordEntry wordEntry;
    wordEntry.key = word.key;
    wordEntry.items = {word};
    return wordEntry;
}
bool WordService::append(Word word, WordEntry &wordEntry)
{
    wordEntry.items.push_back(word);
    return true;
}