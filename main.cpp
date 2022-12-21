#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#include "caesar.h"
#include "playfair.h"

string encrypt(string text, string key)
{
    string firstLayer  = playfair(text, key);
    string secondLayer = caesar(firstLayer, key);
    return secondLayer;
}

string decrypt(string text, string key)
{
    string firstLayer  = caesar(text, key, true);
    string secondLayer = playfair(firstLayer, key, true);
    return secondLayer;
}

bool DECRYPT = false;

void treat_input(int &argc, char **argv, string &key, string &text, string &path)
{
    int option;

    while ((option = getopt(argc, argv, "dk:f:")) != -1)
    {
        switch (option)
        {
            case 'd':
                DECRYPT = true;
                break;
            case 'k':
                key = optarg;
                break;
            case 'f':
                path = optarg;
                break;
            default:
                cout << "Usage: ./main [-d] -k key -f filepath" << endl;
                exit(0);
        }
    }
}

string readfile(string path)
{
    ifstream file(path);
    string   res;
    string   accumulator;
    while (file >> res)
        accumulator += " " + res;
    file.close();
    return accumulator;
}

int main(int argc, char **argv)
{
    string key, text, path;
    treat_input(argc, argv, key, text, path);

    text = readfile(path);

    string result = DECRYPT ? decrypt(text, key) : encrypt(text, key);

    cout << result << endl;
}
