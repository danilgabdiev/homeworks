#include <iostream>
#include <cstring>

int* ZFunc(std::string& str) {
  int str_size = str.size();
  auto z = new int[str_size]{0};
  z[0] = str_size;

  int left = 0, right = 0;
  for (int i = 1; i < str_size; ++i) {
    if (i <= right) {
      z[i] = std::min(z[i - left], right - i);
    }

    while ((i + z[i] < str_size) && (str[z[i]] == str[i + z[i]])) {
      ++z[i];
    }

    if (right < i + z[i]) {
      left = i;
      right = i + z[i];
    }
  }

  return z;
}

int main() {
  std::string str;
  std::cin >> str;

  auto z = ZFunc(str);

  int str_size = str.size();

  for (int x = 0; x < str_size; ++x) {
    std::cout << z[x] << ' ';
  }

  delete[] z;
  return 0;
}