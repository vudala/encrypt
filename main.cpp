#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#include "playfair.h"
#include "caesar.h"

string encrypt(string text, string key)
{
    string firstLayer = playfair(text, key);
    string secondLayer = caesar(firstLayer, key);
    return secondLayer;
}

string decrypt(string text, string key)
{
    string firstLayer = caesar(text, key, true);
    string secondLayer = playfair(firstLayer, key, true);
    return secondLayer;
}

bool DECRYPT = false;

void treat_input(int& argc, char **argv)
{
    int option;
    
    while((option = getopt(argc, argv, "dk:f:")) != -1){
        switch(option){
            case 'd':
                DECRYPT = true;
                break;
            case 'k':
                break;
            case 'f':
                break;
            default:
                cout << "Usage: ./main [-d] key filepath" << endl;
                exit(0); 
        }
    }
}


string readfile(char * path) {
    ifstream file(path);
    string res;
    string accumulator;
    while(file >> res)
        accumulator += " " + res;
    file.close();
    return accumulator;
}

int main(int argc, char **argv)
{
    treat_input(argc, argv);

    string key, text;
    if (argc >= 3) {
        key = argv[argc - 2];
        text = readfile(argv[argc - 1]);
    }
    else {
        cout << "Usage: ./main [-d] key filepath" << endl;
        exit(0);
    }

    string result = DECRYPT ? decrypt(text, key) : encrypt(text, key);

    cout << result << endl;
}
