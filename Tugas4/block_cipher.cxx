#include <format>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string bools_to_str(vector<bool> bools);
vector<bool> str_to_bools(string input);
void shift_right_4(vector<bool> *bools);

class BlockCipher {
  vector<bool> expand_key(int length) {
    vector<bool> expanded_key;
    for (int i = 0; i < length; i++) {
      expanded_key.push_back(key[i % 4]);
    }
    return expanded_key;
  }

public:
  bool key[4];

  BlockCipher(bool *key) {
    for (int i = 0; i < 4; i++) {
      this->key[i] = key[i];
    }
  }

  string encrypt(string plaintext) {
    vector<bool> expanded_key =
        expand_key(plaintext.length() * sizeof(plaintext[0]) * 8);
    vector<bool> plaintext_bools = str_to_bools(plaintext);

    // xor
    for (int i = 0; i < plaintext_bools.size(); i++) {
      plaintext_bools[i] = expanded_key[i] != plaintext_bools[i];
    }

    shift_right_4(&plaintext_bools);

    return bools_to_str(plaintext_bools);
  }
};

string bools_to_str(vector<bool> bools) {
  string string;
  for (int i = 0; i < bools.size(); i += 8) {
    unsigned char c = 0b0;
    for (int j = 0; j < 8; j++) {
      c |= bools[i + j];
      if (j != 7)
        c <<= 1;
    }
    string.push_back(c);
  }
  return string;
}

vector<bool> str_to_bools(string input) {
  vector<bool> bools;
  for (int i = input.size() - 1; i >= 0; i--) {
    for (int _j = 0; _j < sizeof(input[i]); _j++) {
      for (int _k = 0; _k < 8; _k++) {
        bools.insert(bools.begin(), input[i] & 0b00000001);
        input[i] >>= 1;
      }
    }
  }
  return bools;
}

void shift_right_4(vector<bool> *bools) {
  for (int i = 0; i < bools->size();) {
    bool temp = (*bools)[i];
    (*bools)[i] = (*bools)[i + 3];
    i++;
    for (int _j = 1; _j < 4; _j++, i++) {
      bool temp2 = (*bools)[i];
      (*bools)[i] = temp;
      temp = temp2;
    }
  }
}
