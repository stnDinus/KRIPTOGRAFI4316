#include <string>
#include <vector>

using namespace std;

class BlockCipher {
  vector<bool> expand_key(int length) {
    vector<bool> expanded_key;
    for (int i = 0; i < length; i++) {
      expanded_key.push_back(key[i % 4]);
    }
    return expanded_key;
  }

  string stringify_key(vector<bool> expanded_key) {
    string key_string;
    for (int i = 0; i < expanded_key.size(); i += 8) {
      unsigned char c = 0b0;
      for (int j = 0; j < 8; j++) {
        c |= expanded_key[i + j];
        if (j != 7)
          c <<= 1;
      }
      key_string.push_back(c);
    }
    return key_string;
  }

public:
  bool key[4];

  BlockCipher(bool *key) {
    for (int i = 0; i < 4; i++) {
      this->key[i] = key[i];
    }
  }

  string encrypt(string plaintext) {
    string key_string = stringify_key(expand_key(plaintext.length()));

    string xor_str;
    for (int i = 0; i < plaintext.length(); i++) {
      // TODO: shift 4 (or any arbitrary number) bits at a time
      xor_str.push_back((plaintext[i] ^ key_string[i]) << 1);
    }

    return xor_str;
  }
};
