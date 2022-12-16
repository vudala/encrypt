#include <bits/stdc++.h>
using namespace std;

int LIN_LIM = 6, COL_LIM = 6;
map<char, pair<int, int>> positions;
vector<vector<char>> table (LIN_LIM, vector<char> (COL_LIM));

// preenche a tabela de consulta utilizando um chave
void build_table(string key)
{
    string chars = "0123456789abcdefghijklmnopqrstuvxwyz";
    map<char, bool> taken;
    for(char c : chars)
        taken[c] = false;

    int i = 0, j = 0;
    for(char c : key) {
        if (taken[c] == false) {
            table[i][j] = c;
            positions[c] = {i, j};
            taken[c] = true;

            j++;
            if (j >= COL_LIM) {
                i++;
                j = 0;
            }
        }
    }

    for(char c : chars) {
        if (taken[c] == false) {
            table[i][j] = c;
            positions[c] = {i, j};
            taken[c] = true;

            j++;
            if (j >= COL_LIM) {
                i++;
                j = 0;
            }
        }
    }
}


// quebra o texto claro em digramas
vector<string> digrams;
void split_text(string text)
{
    for (int i = 0; i < text.size();) {
        if (text[i] == ' ') {
            i += 1;
            continue;
        }
        if (text[i] != text[i+1]) {
            digrams.push_back(text.substr(i, 2));
            i += 2;
        }      
        else {
            string aux;
            aux.push_back(text[i]);
            aux += "x";
            digrams.push_back(aux);
            i += 1;
        } 
    }

    if (digrams.back().length() == 1)
        digrams[digrams.size() - 1] += "z";
}

// encripta um digrama utilizando playfair
string encrypt_digram(string dig)
{
    auto [i1, j1] = positions[dig[0]];
    auto [i2, j2] = positions[dig[1]];

    string res;

    if (j1 == j2) {
        res.push_back(i1 + 1 >= LIN_LIM ? table[0][j1] : table[i1 + 1][j1]);
        res.push_back(i2 + 1 >= LIN_LIM ? table[0][j1] : table[i2 + 1][j1]);
    }
    else if (i1 == i2) {
        res.push_back(j1 + 1 >= LIN_LIM ? table[i1][0] : table[i1][j1 + 1]);
        res.push_back(j2 + 1 >= LIN_LIM ? table[i2][0] : table[i2][j2 + 1]);
    }
    else {
        res.push_back(table[i1][j2]);
        res.push_back(table[i2][j1]);
    }

    return res;
}

int main()
{
    string key;
    cin >> key;

    build_table(key);

    string text;
    cin >> text;

    split_text(text);

    for(vector<char> v : table) {
        for (char c : v)
            cout << c << " ";
        cout << "\n";
    }

    for (string s : digrams)
        cout << s << " ";
    cout << "\n";

    for (string s : digrams)
        cout << encrypt_digram(s) << " ";
    cout << "\n";
}
