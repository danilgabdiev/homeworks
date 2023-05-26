#include <iostream>
#include <cstring>
#include <vector>

std::vector<int> PrefFunc(std::string str) {
  std::vector<int> p(str.size(), 0);

  for (size_t i = 1; i < str.size(); ++i) {
    int k = p[i - 1];
    while (str[i] != str[k] && k > 0) {
      k = p[k - 1];
    }

    if (str[i] == str[k]) {
      p[i] = k + 1;
    }
  }

  return p;
}

int main() {
  std::string str;
  std::cin >> str;

  for (auto x : PrefFunc(str)) {
    std::cout << x << ' ';
  }

  return 0;
}