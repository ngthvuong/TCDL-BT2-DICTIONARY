#include "modules/AVLTree.h"
#include "modules/Word.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
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
        cout << "Opened file: " << files[i] << endl;

        int check = 0;
        string line;

        string str1 = "cbcfef1";
        string str2 = "cbddef12";

        int result = WordService::compareKey(str1, str2);
        cout << "result: " << result << endl;

        while (getline(file, line))
        {
            if (!line.empty())
            {
                try
                {
                    Word word = WordService::stringToWord(line);
                }catch(out_of_range error){
                    cout << "Errors: "<< error.what() << endl;
                }
            }
            if (line.empty())
            {
                check++;
            }
            if (check == 1)
                break;
        }
        file.close();
    }
}