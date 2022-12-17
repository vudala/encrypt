#include "caesar.h"
#include "utils.h"

map<char, char> caesarTable;
map<char, char> decryptTable;

void rotateAlphabet(string alphabet, int k) {
  for (int i = 0; i < alphabet.size(); i++) {
    int index = (i + k) % alphabet.size();
    int decryptIndex = i - k > 0 
      ? (i - k) % alphabet.size()
      : (i - k) + alphabet.size();
    
    caesarTable[alphabet[i]] = alphabet[index];
    decryptTable[alphabet[i]] = alphabet[decryptIndex];
  
  }
}

string caesar(string text, string key, bool decrypt){
  int k = magic_number(key);
  string myAlphabet = josephs_algorithm(alphabet, k);

  rotateAlphabet(myAlphabet, k);

  string result = "";
  for (char c : text) {
    result += !decrypt ? caesarTable[c] : decryptTable[c];
  }

  return result;
}

void printRotationTable(){
  for (auto it = caesarTable.begin(); it != caesarTable.end(); it++) {
    cout << it->first << " -> " << it->second << " | ";
  }
  cout << endl;

  for(auto it = decryptTable.begin(); it != decryptTable.end(); it++) {
    cout << it->first << " -> " << it->second << " | ";
  }
  cout << endl;
}