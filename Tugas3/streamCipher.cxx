#include <format>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, string> args;

bool argsIsValid(int argc, char *argv[]);

vector<bool> generateKeystream();

string stringifyKeystream(vector<bool> keystream);

string streamCipher(string keystream);

int main(int argc, char *argv[]) {
  // NILAI DEFAULT
  args["-i"] = "VAR";  // text input (plain teks / cipher teks)
  args["-s"] = "0011"; // seed untuk keystream

  if (!argsIsValid(argc, argv)) {
    return -1;
  }

  vector<bool> keystream = generateKeystream();
  for (int i = 0; i < keystream.size(); i += 4) {
    for (int i2 = 0; i2 < 4; i2++)
      cout << keystream[i + i2];
    cout << " ";
  }
  cout << endl;

  cout << streamCipher(stringifyKeystream(keystream)) << endl;

  return 0;
}

bool argsIsValid(int argc, char *argv[]) {
  // VALIDASI NAMA ARGUMEN FLAG VALID
  for (int i = 1; i < argc; i++) {
    if (args.contains(argv[i])) {
      args[argv[i]] = argv[i + 1];
      i++;
    } else {
      cerr << format("{} bukan argumen valid", argv[i]) << endl;
      return false;
    }
  };

  // VALIDASI PANJANG SEED LEBIH DARI 4 DIGIT
  if (args["-s"].length() < 4) {
    cerr << format("panjang seed harus lebih dari 4 digit biner") << endl;
    return false;
  }

  // VALIDASI ISI SEED BILANGAN BINER
  for (int i = 0; i < args["-s"].length(); i++) {
    char c = args["-s"][i] - 48;
    if ((c != true) == (c != false)) { // c != false atau true
      cerr << format("'{}' pada \"{}\" bukan bilangan biner", char(c + 48),
                     args["-s"])
           << endl;
      return false;
    }
  }

  return true;
};

vector<bool> generateKeystream() {
  vector<bool> keystream(args["-i"].length() * 8);

  // masukan seed
  for (int i = 0; i < args["-s"].length(); i++)
    keystream[i] = args["-s"][i] - 48;
  // lanjutkan dari seed
  for (int i = args["-s"].length(); i < keystream.size(); i++)
    keystream[i] = keystream[i - 1] != keystream[i - 4];

  return keystream;
}

/**
 * menggabungkan boolean bit terpangkas menjadi sebuah string
 */
string stringifyKeystream(vector<bool> keystream) {
  string keystreamString;
  for (int i = 0; i < keystream.size();) {
    unsigned char c = 0b0;

    for (int i2 = 0; i2 < 8; i2++) {
      c |= keystream[i + i2];
      if (i2 != 7)
        c <<= 1;
    }

    keystreamString.push_back(c);

    i += 8;
  }
  return keystreamString;
}

string streamCipher(string keystream) {
  string output;

  for (int i = 0; i < args["-i"].length(); i++) {
    output.push_back(args["-i"][i] ^ keystream[i]);
  }

  return output;
}
