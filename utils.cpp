#include "utils.h"

string alphabet = "0123456789abcdefghijklmnopqrstuvwxyz.,?:; /!$%=+-";

int magic_number(string key)
{
    int magic_number = 0;
    for(char c : key)
        magic_number += c;
    return (magic_number * 69 + 1337 * 420);
}


string josephs_algorithm(string alphabet, int k)
{
    string result;
    int n = alphabet.size();
    int i = 0;
    while (n > 0) {
        i = (i + k - 1) % n;
        result += alphabet[i];
        alphabet.erase(i, 1);
        n--;
    }
    return result;
}
