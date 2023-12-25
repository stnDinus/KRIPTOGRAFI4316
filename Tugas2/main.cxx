#include <iostream>
#include <string>

#include "./parse_args.cxx"
#include "playfair.hxx"

int main(int argc, char *argv[]) {
  parse_args(argc, argv);

  if (args.contains("-e")) {
    cout << "- Plaintext:\n" << args["-e"] << "\n\n";
    cout << "- Ciphertext:\n" << encrypt(args["-e"]) << endl;
  } else if (args.contains("-d")) {
    cout << "- Ciphertext:\n" << args["-d"] << "\n\n";
    cout << "- Plaintext:\n" << decrypt(args["-d"]) << endl;
  }

  return 0;
}
