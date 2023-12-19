/**
 * CIPHER HOMOFONIK
 *
 * Menggunakan tabel huruf dan angka
 * Terdapat 25 huruf, dua huruf akan disamakan
 * Terdapat 100 angka
 * Angka dimulai dari 01, 02, 03 ... 99 hingga 00
 * 1 huruf berelasi ke 4 angka
 */

#include <chrono>
#include <cstdlib>
#include <format>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Homophonic {
  unordered_map<char, int[4]> table;

public:
  char key[4];

  Homophonic(string key) {
    for (int i = 0; i < 4; i++) {
      this->key[i] = key[i];
    };
    generate_table();
  };

  // Methods
  void generate_table() {
    for (int i = 0; i < 4; i++) {
      int inc = 1;
      for (int j = 0; j < 26; j++) {
        char l = (key[i] - 97 + j) % 26 + 97;
        if (l == 'j') {
          inc = 0;
          continue;
        }
        table[l][i] = (25 * i + j + inc) % 100;
      }
    }
  }

  void print_table() {
    cout << "   ";
    for (int i = 97; i < 123; i++) {
      if (char(i) == 'j')
        continue;
      cout << char(i) << "  ";
    }
    cout << endl;
    for (int i = 0; i < 4; i++) {
      cout << key[i] << "  ";
      for (int j = 0; j < 26; j++) {
        char l = j + 97;
        if (l == 'j')
          continue;
        cout << format("{:0>2} ", table[l][i]);
      }
      cout << endl;
    }
  }

  vector<int> encrypt(string plaintext, string key = "word") {
    vector<int> cipher(plaintext.length());
    for (int i = 0; i < plaintext.length(); i++) {
      srand(chrono::high_resolution_clock().now().time_since_epoch().count());
      cipher[i] = table[plaintext[i]][rand() % 4];
    }
    return cipher;
  }

  /**
   * ensures string input contains only lowercase letters except 'j'
   */
  static void sanitize_string(string *s) {
    for (int i = 0; i < s->length(); i++) {
      // substitute j/J with i
      if ((*s)[i] == 'J' || (*s)[i] == 'j') {
        (*s)[i] = 'i';
        continue;
      }

      // if upper, to lower
      if (65 <= (*s)[i] && (*s)[i] <= 90) {
        (*s)[i] += 32;
        continue;
      }

      if (97 > (*s)[i] || (*s)[i] > 122) {
        s->erase(i, 1);
        i--;
        continue;
      }
    }
  }
};
