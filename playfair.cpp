#include "playfair.h"

#include <bits/stdc++.h>

using namespace std;

// dimensoes da tabela de consulta
int LIN_LIM = 6, COL_LIM = 6;

// posicao de cada char na tabela
map<char, pair<int, int>> positions;

// tabela de consulta
vector<vector<char>> table (LIN_LIM, vector<char> (COL_LIM));


// preenche a tabela de consulta utilizando uma chave
void build_table(string key)
{
    string chars = "0123456789abcdefghijklmnopqrstuvxwyz";
    map<char, bool> taken;
    for(char c : chars)
        taken[c] = false;

    // preenche a tabela com os caracteres da chave
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

    // termina de encher a tabela com os caracteres restantes do alfabeto, em ordem
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


// quebra o texto em digramas
vector<string> split_text(string text)
{
    vector<string> digrams;

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

    return digrams;
}


// cifra um digrama
string encrypt_digram(string dig)
{
    auto [i1, j1] = positions[dig[0]];
    auto [i2, j2] = positions[dig[1]];

    string res;

    // mesma coluna
    if (j1 == j2) {
        res.push_back(i1 + 1 >= LIN_LIM ? table[0][j1] : table[i1 + 1][j1]);
        res.push_back(i2 + 1 >= LIN_LIM ? table[0][j1] : table[i2 + 1][j1]);
    }
    // mesma linha
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


// decifra um digrama
string decrypt_digram(string dig)
{
    auto [i1, j1] = positions[dig[0]];
    auto [i2, j2] = positions[dig[1]];

    string res;

    // mesma coluna
    if (j1 == j2) {
        res.push_back(i1 - 1 < 0 ? table[LIN_LIM - 1][j1] : table[i1 - 1][j1]);
        res.push_back(i2 - 1 < 0 ? table[LIN_LIM - 1][j1] : table[i2 - 1][j1]);
    }
    // mesma linha
    else if (i1 == i2) {
        res.push_back(j1 - 1 < 0 ? table[i1][COL_LIM - 1] : table[i1][j1 - 1]);
        res.push_back(j2 - 1 < 0 ? table[i2][COL_LIM - 1] : table[i2][j2 - 1]);
    }
    else {
        res.push_back(table[i1][j2]);
        res.push_back(table[i2][j1]);
    }

    return res;
}


// cifra o texto
string playfair_encrypt(string key, string clear_text)
{
    build_table(key);

    vector<string> digrams = split_text(clear_text);

    string res;

    for(string d : digrams)
        res += encrypt_digram(d);

    return res;
}


// decifra o texto
string playfair_decrypt(string key, string cyphered_text)
{
    build_table(key);

    string res;

    for(int i = 0; i < cyphered_text.length(); i += 2)
        res += decrypt_digram(cyphered_text.substr(i, 2));

    return res;
}