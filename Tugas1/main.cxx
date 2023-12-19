#include "./homophonic.cxx"
#include "./parse_args.cxx"

#include <format>
#include <iostream>
#include <string>

using namespace std;

/**
 * @params -k - 4 character key
 * @params -e - encrypt (string)
 * @params -d - decrypt (space separated int)
 */
int main(int argc, char *argv[]) {
  // INIT ARGS
  args["-k"] = "word";
  parse_args(argc, argv);

  // GENERATE KEY
  Homophonic::sanitize_string(&args["-k"]);
  Homophonic h_instance(args["-k"]);
  cout << "- Key Table:\n";
  h_instance.print_table();
  cout << endl;

  // ENCRYPT
  if (args.contains("-e")) {
    Homophonic::sanitize_string(&args["-e"]);

    cout << format("- Plaintext:\n\"{}\"\n", args["-e"]) << endl;

    vector<int> cipher_vec = h_instance.encrypt(args["-e"]);
    cout << "- Cipher:\n";
    for (int i : cipher_vec)
      cout << format("{:0>d} ", i);
    cout << endl;
    return 0;
  }

  // DECRYPT
  if (args.contains("-d")) {
    cout << format("- Cipher:\n{}\n", args["-d"]) << endl;

    vector<int> cipher_vec;
    unsigned long prev_space_pos = -1;
    while (true) {
      unsigned long next_space_pos = args["-d"].find(' ', prev_space_pos + 1);

      if (next_space_pos == string::npos) {
        cipher_vec.push_back(stoi(args["-d"].substr(
            prev_space_pos + 1, args["-d"].length() - prev_space_pos)));
        break;
      }

      cipher_vec.push_back(stoi(args["-d"].substr(
          prev_space_pos + 1, next_space_pos - prev_space_pos)));
      prev_space_pos = next_space_pos;
    }

    cout                                  //
        << "- Plaintext:\n"               //
        << h_instance.decrypt(cipher_vec) //
        << endl;

    return 0;
  }
}
