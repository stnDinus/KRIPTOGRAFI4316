/**
 * Cipher playfair
 * 1) Buat matriks enkripsi 5x5 berisi karakter unik setiap elemen
 * 2) Mengambil input string
 * 3) Membagi karakter menjadi kelompok 2 elemen
 * 4) Jika ada kelompok dengan huruf yang sama, pisah dengan z
 * 5) Jika panjang akhir ganjil, tambah huruf z
 */

static const char matriks_enkripsi[5][5] = {
  {'p', 'o', 'i', 'u', 'y'},
  {'q', 'w', 'e', 'r', 't'},
  {'l', 'k', 'j', 'h', 'm'},
  {'a', 's', 'd', 'f', 'g'},
  {'z', 'x', 'c', 'v', 'b'}
};

// WIP
char *encrypt(int n, char *input) {
  int l = 0;

  char last_char = input[0];
  for (int i = 1; i < n; i++) {
    if (input[i] == last_char) {
      l++;
    }
  }

  if (l % 2 == 1)
    l++;

  char return_str[l];

  if (l % 2 == 1)
    return_str[l - 1] = 'z';

  return return_str;
}
