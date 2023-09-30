#include <iostream>

#include "playfair.hxx"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "masukan argumen!" << std::endl;
    exit(1);
  }

  std::cout << argv[1] << std::endl;
  std::cout << encrypt(argv[1]) << std::endl;

  return 0;
}
