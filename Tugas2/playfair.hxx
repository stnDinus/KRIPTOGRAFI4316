/**
 * Cipher playfair
 * 1) Buat matriks kunci 5x5 berisi karakter unik setiap elemen, tanpa huruf j
 * 2) Jika plaintext mengandung huruf j, tukar dengan i
 * 3) Bagi input hingga terdiri dari kelompok 2 huruf
 * 4) Jika ada kelompok dengan huruf yang sama, pisah dengan z
 * 5) Jika panjang akhir ganjil, tambah huruf z
 */

#pragma once

#include <string>
#include <iostream>

std::string encrypt(std::string input);

std::string decrypt(std::string input);
