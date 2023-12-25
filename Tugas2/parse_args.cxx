#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> args;

void parse_args(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    args[argv[i]] = argv[i + 1];
    i++;
  }
}
