#include "./homophonic.cxx"
#include "./parse_args.cxx"

#include <format>
#include <iostream>

using namespace std;

/**
 * @params -k - 4 character key
 * @params -p - plaintext (letters only)
 */
int main(int argc, char *argv[]) {
  args["-k"] = "word";
  args["-p"] = "lorem";
  parse_args(argc, argv);

  Homophonic::sanitize_string(&args["-k"]);
  Homophonic::sanitize_string(&args["-p"]);

  Homophonic h_instance(args["-k"]);

  cout << "Key Table:\n";
  h_instance.print_table();
  cout << endl;

  cout << format("Plaintext:\n\"{}\"\n", args["-p"]) << endl;

  vector<int> cipher_vec = h_instance.encrypt(args["-p"]);
  cout << "Cipher:\n";
  for (int i : cipher_vec)
    cout << format("{:0>d} ", i);
  cout << endl;
}
