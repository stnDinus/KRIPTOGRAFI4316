#include "playfair.hxx"

static const char matriks_enkripsi[5][5] = {{'p', 'o', 'i', 'u', 'y'},
                                            {'q', 'w', 'e', 'r', 't'},
                                            {'h', 'z', 'k', 'l', 'n'},
                                            {'a', 's', 'd', 'f', 'g'},
                                            {'m', 'x', 'c', 'v', 'b'}};

using namespace std;
string encrypt(string input) {
  // SANITASI
  for (int i = 0; i < input.length();) {
    if (input[i] == ' ') {
      input.erase(i, 1);
      continue;
    } else if (input[i] < 65 || (input[i] > 90 && input[i] < 97) ||
               input[i] > 122) {
      cerr << "pastikan input hanya berisi huruf alphabet!" << endl;
      exit(1);
    } else if (input[i] == 'j') {
      input[i] = 'i';
    } else if (input[i] < 97) {
      input[i] += 32;
    }

    i++;
  }

  bool dupe;

  do {
    dupe = false;

    for (int i = 1; i < input.length(); i += 2)
      if (input[i] == input[i - 1]) {
        input.insert(i, 1, 'z');

        dupe = true;
      }
  } while (dupe);

  if (input.length() % 2 == 1)
    input.push_back('z');

  // MULAI ENKRIPSI
  for (int i = 1; i < input.length(); i += 2) {
    int ly_idx, lx_idx, ry_idx, rx_idx;

    for (int y = 0; y < 5; y++) {
      for (int x = 0; x < 5; x++) {
        if (input[i] == matriks_enkripsi[y][x]) {
          ry_idx = y;
          rx_idx = x;
        } else if (input[i - 1] == matriks_enkripsi[y][x]) {
          ly_idx = y;
          lx_idx = x;
        }
      }
    }

    if (ly_idx == ry_idx) {
      input[i] = matriks_enkripsi[ry_idx][(rx_idx + 1) % 5];
      input[i - 1] = matriks_enkripsi[ly_idx][(lx_idx + 1) % 5];
    } else if (lx_idx == rx_idx) {
      input[i] = matriks_enkripsi[(ry_idx + 1) % 5][rx_idx];
      input[i - 1] = matriks_enkripsi[(ly_idx + 1) % 5][lx_idx];
    } else {
      input[i] = matriks_enkripsi[ry_idx][lx_idx];
      input[i - 1] = matriks_enkripsi[ly_idx][rx_idx];
    }
  }

  return input;
}
