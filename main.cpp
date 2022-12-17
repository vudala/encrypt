#include <bits/stdc++.h>
using namespace std;

#include "playfair.h"

int main()
{
    string key, text;
    cin >> key >> text;

    string enc = playfair_encrypt(key, text);

    string dec = playfair_decrypt(key, enc);

    cout << text << "\n";
    cout << enc << "\n";
    cout << dec << "\n";
}
