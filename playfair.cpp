#include "playfair.h"
#include "utils.h"

// dimensões da tabela de consultar
#define TABLE_LIM 7

// posição de cada char na tabela de consulta
map<char, pair<int, int>> positions;

// tabela de consulta
vector<vector<char>> table (TABLE_LIM, vector<char> (TABLE_LIM));


void populate_table(string chars, map<char, bool> &taken, int &i, int &j)
{
    for(char c : chars) {
        if (taken[c] == false) {
            table[i][j] = c;
            positions[c] = {i, j};
            taken[c] = true;

            j++;
            if (j >= TABLE_LIM) {
                i++;
                j = 0;
            }
        }
    }
}


// preenche a tabela de consulta utilizando um chave
void build_table(string key)
{
    string chars = josephs_algorithm(alphabet, magic_number(key));

    map<char, bool> taken;
    for(char c : chars)
        taken[c] = false;

    int i = 0, j = 0;
    populate_table(key, taken, i, j);
    populate_table(chars, taken, i, j);
}


// quebra o texto claro em digramas
vector<string> parse_cleartext(string text)
{
    vector<string> digrams;

    for (int i = 0; i < text.size();) {
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


// quebra o texto 
vector<string> parse_cypheredtext(string text)
{
    vector<string> res;
    for(int i = 0; i < text.size(); i += 2)
        res.push_back(text.substr(i, 2));
    return res;
}


// encripta um digrama utilizando playfair
string encrypt_digram(string dig)
{
    auto [i1, j1] = positions[dig[0]];
    auto [i2, j2] = positions[dig[1]];

    string res;

    // mesma coluna
    if (j1 == j2) {
        res.push_back(i1 + 1 >= TABLE_LIM ? table[0][j1] : table[i1 + 1][j1]);
        res.push_back(i2 + 1 >= TABLE_LIM ? table[0][j1] : table[i2 + 1][j1]);
    }
    // mesma linha
    else if (i1 == i2) {
        res.push_back(j1 + 1 >= TABLE_LIM ? table[i1][0] : table[i1][j1 + 1]);
        res.push_back(j2 + 1 >= TABLE_LIM ? table[i2][0] : table[i2][j2 + 1]);
    }
    else {
        res.push_back(table[i1][j2]);
        res.push_back(table[i2][j1]);
    }

    return res;
}


string decrypt_digram(string dig)
{
    auto [i1, j1] = positions[dig[0]];
    auto [i2, j2] = positions[dig[1]];

    string res;

    // mesma coluna
    if (j1 == j2) {
        res.push_back(i1 - 1 < 0 ? table[TABLE_LIM - 1][j1] : table[i1 - 1][j1]);
        res.push_back(i2 - 1 < 0 ? table[TABLE_LIM - 1][j1] : table[i2 - 1][j1]);
    }
    // mesma linha
    else if (i1 == i2) {
        res.push_back(j1 - 1 < 0 ? table[i1][TABLE_LIM - 1] : table[i1][j1 - 1]);
        res.push_back(j2 - 1 < 0 ? table[i2][TABLE_LIM - 1] : table[i2][j2 - 1]);
    }
    else {
        res.push_back(table[i1][j2]);
        res.push_back(table[i2][j1]);
    }

    return res;
}


// processa o array de digramas
string process_digrams(vector<string> digrams, string (*func)(string))
{
    string ret;
    for(string s : digrams)
        ret += func(s);
    return ret;
}


string playfair(string text, string key, bool decrypt)
{
    build_table(key);

    vector<string> digrams;
    if (!decrypt) {
        digrams = parse_cleartext(text);
        return process_digrams(digrams, encrypt_digram);
    }
    else { 
        digrams = parse_cypheredtext(text);
        return process_digrams(digrams, decrypt_digram);
    }
}
