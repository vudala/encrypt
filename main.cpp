#include <bits/stdc++.h>
using namespace std;

#include "playfair.h"

int main()
{
    string key;
    cin >> key;

    string text;
    cin >> text;

    string firstLayer = play_fair(text, key);
    string decrypted = play_fair(firstLayer, key, true);

    print_table();

    cout << firstLayer << endl;
    cout << decrypted << endl;
}
