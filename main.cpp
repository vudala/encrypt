#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#include "playfair.h"
#include "caesar.h"

string encrypt(string text, string key) {
    string firstLayer = playfair(text, key);
    string secondLayer = caesar(firstLayer, key);
    return secondLayer;
}

string decrypt(string text, string key) {
    string firstLayer = caesar(text, key, true);
    string secondLayer = playfair(firstLayer, key, true);
    return secondLayer;
}

bool DECRYPT = false;

void treat_input(int argc, char **argv) {
    int option;
    
    while((option = getopt(argc, argv, "dh")) != -1){
        switch(option){
            case 'd':
                DECRYPT = true;
                break;
            case 'h':
                cout << "Usage: ./main [-d] [-h]" << endl;
                exit(0);
        }
    }

}


int main(int argc, char **argv)
{
    treat_input(argc, argv);

    string key, text;
    cout << "Enter key: ";
    cin >> key;

    DECRYPT ? cout << "Enter cypher: " : cout << "Enter text: ";
    cin >> text; 

    string result = DECRYPT ? decrypt(text, key) : encrypt(text, key);

    cout << result << endl;
}
