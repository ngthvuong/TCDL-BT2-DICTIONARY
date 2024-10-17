#include "modules/AVLTree.h"
#include "modules/Word.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    AVLTree dictionary;
    vector<string> files = {"data/a.txt"};
    int length = files.size();
    for (int i = 0; i < length; i++)
    {
        ifstream file(files[i]);
        if (!file)
        {
            cout << "Unable to open file: " << files[i] << endl;
            continue; // Skip to the next file if it can't be opened
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
                    dictionary.addNode(word);
                }
                catch (const out_of_range error)
                {
                    cout << "Errors: " << error.what() << endl;
                    continue;
                }
            }

            // if (line.empty())
            // {
            //     check++;
            // }
            // if (check == 1)
            //     break;
        }
        file.close();
    }
    dictionary.print();
}