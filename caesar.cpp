#include "caesar.h"
#include "utils.h"

map<char, char> caesarTable;
map<char, char> decryptTable;


// rotaciona o alfabeto utilizando
void rotate_alphabet(string alphabet, int k)
{
    k = k % 36;
    for (int i = 0; i < alphabet.size(); i++) {
        int index = (i + k) % alphabet.size();
        int decryptIndex = (i - k + alphabet.size()) % alphabet.size();
        
        caesarTable[alphabet[i]] = alphabet[index];
        decryptTable[alphabet[i]] = alphabet[decryptIndex];
    }
}


string caesar(string text, string key, bool decrypt)
{
  int k = magic_number(key);
  string scrambled = josephs_algorithm(alphabet, k);

  rotate_alphabet(scrambled, k);

  string result;
  for (char c : text)
    result += !decrypt ? caesarTable[c] : decryptTable[c];

  return result;
}
