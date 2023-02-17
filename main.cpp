#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

#include "caesar.h"
#include "playfair.h"
#include "transposition.h"
#include "utils.h"

string encrypt(string text, string key)
{
    string first_layer  = playfair(text, key);
    string second_layer = caesar(first_layer, key);
    string third_layer = transposition(second_layer, key);
    return third_layer;
}

string decrypt(string text, string key)
{
    string third_layer = transposition(text, key, true);
    string second_layer  = caesar(third_layer, key, true);
    string first_layer = playfair(second_layer, key, true);
    return first_layer;
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
    ifstream t(path);
    stringstream buffer;
    buffer << t.rdbuf();

    string ret = buffer.str();

    transform(ret.begin(), ret.end(), ret.begin(),
    [](unsigned char c){ return tolower(c); });

    return parse_input(ret);
}

int main(int argc, char **argv)
{
    string key, text, path;
    treat_input(argc, argv, key, text, path);

    if (key.empty() || path.empty()) {
        cout << "Usage: ./main [-d] -k key -f filepath" << endl;
        exit(0);
    }

    text = readfile(path);

    string result = DECRYPT ? decrypt(text, key) : encrypt(text, key);
    cout << result;
}
