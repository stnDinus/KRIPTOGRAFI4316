#include <iostream>
#include <string>

#include "playfair.hxx"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "masukan argumen!" << std::endl;
    exit(1);
  }

  std::string encrypted = encrypt(argv[1]);
  std::string dencrypted = decrypt(encrypted);

  std::cout << argv[1] << std::endl;
  std::cout << encrypted << std::endl;
  std::cout << dencrypted << std::endl;

  return 0;
}
