#include "./block_cipher.cxx"
#include "./parse_args.cxx"
#include <format>
#include <iostream>

int main(int argc, char *argv[]) {
  args["-k"] = "0111";
  parse_args(argc, argv);

  bool key[4];
  for (int i = 0; i < 4; i++) {
    key[i] = args["-k"][i] == '1';
  }
  BlockCipher bc_instance(key);

  cout << format("- Key:\n{}\n", args["-k"]) << endl;

  // ENCRYPT
  if (args.contains("-e")) {
    cout << format("- Plaintext:\n\"{}\"\n", args["-e"]) << endl;

    string cipher = bc_instance.encrypt(args["-e"]);

    cout << "- Cipher:\n";
    for (int i = 0; i < cipher.size(); i++) {
      unsigned char c = cipher[i];
      cout << format("{:0>8b} ", c);
    }
    cout << endl;
  }

  return 0;
}
