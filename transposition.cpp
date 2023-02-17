#include <bits/stdc++.h>

#include "utils.h"

using namespace std;

int Span = 5;

vector<int> create_order_vector(int seed)
{
    srand(seed);

    vector<int> order;

    for(int i = 0; i < Span; i++) {
        int n;
        do {
            n = rand() % Span;
        } while(find(order.begin(), order.end(), n) != order.end());
        order.push_back(n);
    }

    return order;
}

string cypher(string text, int seed)
{
    int diff = text.size() % Span;
    if (diff > 0)
        for(int i = 0; i < Span - diff; i++)
            text += '_';

    vector<int> order = create_order_vector(seed);

    vector<string> cols (Span);

    for(int i = 0; i < Span; i++)
        for(int j = i; j < text.size(); j += Span)
            cols[order[i]] += text[j];

    string result;
    for(string s : cols)
        result += s;
    return result;
}


vector<string> parse_to_columns(string text)
{
    vector<string> res(Span);

    for(int i = 0; i < Span; i++) {
        res[i] += text.substr(i * text.size() / Span, text.size() / Span);
    }

    return res;
}


string decypher(string text, int seed)
{
    vector<string> col = parse_to_columns(text);

    vector<int> order = create_order_vector(seed);

    string res;

    for(int i = 0; i < text.size() / Span; i++)
        for(int j = 0; j < Span; j++)
            res += col[order[j]][i];

    return res;
}


string transposition(string text, string key, bool decrypt)
{
    int mn = magic_number(key);
    
    if (decrypt)
        return decypher(text, mn);

    return cypher(text, mn);
}