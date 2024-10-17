#include "modules/AVLTree.h"
#include "modules/Word.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
int main()
{
    AVLTree *dictionary = new AVLTree();
    vector<string> fileNames = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    int length = fileNames.size();
    cout << length << endl;

    for (int i = 0; i < length; i++)
    {
        string filePath = "data/" + fileNames[i] + ".txt";
        ifstream file(filePath);
        if (!file)
        {
            cout << "Unable to open file: " << filePath << endl;
            continue;
        }
        // int check = 0;
        string line;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                try
                {
                    Word word = WordService::stringToWord(line);
                    dictionary->addNode(word);
                }
                catch (const out_of_range error)
                {
                    cout << "Errors: " << error.what() << endl;
                    continue;
                }
            }
        }
        file.close();
    }
    cout << "========================" << endl;
    cout << "DICTIONARY PROGRAM" << endl;
    cout << "========================" << endl;

    while (true)
    {
        cout << "Fill in your word (0 to exit) : ";
        string keyword;
        getline(cin, keyword);
        keyword = WordService::trim(keyword);
        if (keyword == "0")
            break;

        if (keyword.empty())
        {
            cout << "- word must not contain all space!" << endl;
            continue;
        }

        WordEntry *wordEntry = dictionary->search(keyword);
        if (!wordEntry)
        {
            cout << "- No result found!" << endl;
        }
        else
        {
            for (Word &word : wordEntry->items)
            {
                cout << "- " << word.translatedMeaning << endl;
            }
        }
        cout << "------------------------------" << endl;
        delete wordEntry;
    }

    delete dictionary;
}