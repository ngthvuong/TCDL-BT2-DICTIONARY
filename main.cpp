#include "modules/AVLTree.h"
#include "modules/Word.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void prepareDictionary(AVLTree *&);

int main()
{
    AVLTree *dictionary = new AVLTree();
    prepareDictionary(dictionary);

    cout << "========================" << endl;
    cout << "DICTIONARY PROGRAM" << endl;
    cout << "========================" << endl;

    WordEntry *wordEntry;
    string keyword;
    while (true)
    {
        cout << "Fill in your word (0 to exit) : ";
        getline(cin, keyword);
        keyword = WordService::trim(keyword);
        if (keyword == "0")
        {
            break;
        }

        if (keyword.empty())
        {
            cout << "- Word must not contain all space!" << endl;
            continue;
        }

        wordEntry = dictionary->search(keyword);
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
    }

    delete dictionary;
    cout << "- Program Exited!" << endl;
}

void prepareDictionary(AVLTree *&dictionary)
{
    vector<string> fileNames = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    int length = fileNames.size();

    string filePath;
    string line;
    Word word;
    
    for (int i = 0; i < length; i++)
    {
        filePath = "data/" + fileNames[i] + ".txt";
        ifstream file(filePath);
        if (!file)
        {
            cout << "Unable to open file: " << filePath << endl;
            continue;
        }

        while (getline(file, line))
        {
            if (!line.empty())
            {
                try
                {
                    word = WordService::stringToWord(line);
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
}