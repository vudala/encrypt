#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>
using namespace std;

extern string alphabet;

// Gera um número maluco baseado na chave
int magic_number(string key);

// Aplica o algoritmo de Josephus sobre o alfabeto para bagunçá-lo
string josephs_algorithm(string alphabet, int k);

string parse_input(string input);

#endif