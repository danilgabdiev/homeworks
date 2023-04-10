#include "cstring.h"

size_t Strlen(const char* str) {
  size_t i = 0;

  while (str[i] != '\0') {
    ++i;
  }

  return i;
}

int Strncmp(const char* first, const char* second, size_t count) {
  size_t first_len = Strlen(first);
  size_t second_len = Strlen(second);

  first_len = (first_len < count ? first_len : count);
  second_len = (second_len < count ? second_len : count);

  size_t i = 0, j = 0;

  while (i < first_len && j < second_len) {
    if (first[i] < second[j]) {
      return -1;
    }

    if (first[i] > second[j]) {
      return 1;
    }

    ++i, ++j;
  }

  if (first_len == second_len) {
    return 0;
  }

  if (first_len > second_len) {
    return 1;
  }

  return -1;
}

int Strcmp(const char* first, const char* second) {
  size_t longest = (Strlen(first) < Strlen(second) ? Strlen(second) : Strlen(first));
  return Strncmp(first, second, longest);
}

char* Strncpy(char* dest, const char* src, size_t count) {
  size_t src_len = Strlen(src);

  for (size_t i = 0; i < count; ++i) {
    if (i < src_len) {
      dest[i] = src[i];
    } else {
      dest[i] = '\0';
    }
  }

  dest[src_len] = '\0';
  return dest;
}

char* Strcpy(char* dest, const char* src) {
  size_t src_len = Strlen(src);
  return Strncpy(dest, src, src_len);
}

char* Strcat(char* dest, const char* src) {
  size_t dest_len = Strlen(dest);
  size_t src_len = Strlen(src);

  for (size_t i = dest_len; i < dest_len + src_len; ++i) {
    dest[i] = src[i - dest_len];
  }

  return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
  size_t dest_len = Strlen(dest);
  size_t src_len = Strlen(src);

  if (count > src_len) {
    return Strcat(dest, src);
  }

  for (size_t i = dest_len; i < dest_len + count; ++i) {
    dest[i] = src[i - dest_len];
  }

  return dest;
}

const char* Strchr(const char* str, char symbol) {
  size_t str_len = Strlen(str);

  size_t i = 0;
  while (i < str_len) {
    if (str[i] == symbol) {
      return &(str[i]);
    }

    ++i;
  }

  if (symbol == '\0') {
    return &(str[str_len]);
  }

  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  size_t str_len = Strlen(str);

  size_t i = str_len;
  while (i > 0) {
    if (str[i] == symbol) {
      return &(str[i]);
    }

    --i;
  }

  if (str[i] == symbol) {
    return &(str[i]);
  }

  return nullptr;
}

size_t StrCounter(const char* dest, const char* src, bool is_strspn) {
  size_t len = 0;

  size_t i = 0;
  size_t j = 0;
  while (dest[i] != '\0') {
    bool found = false;

    while (src[j] != '\0') {
      if (dest[i] == src[j]) {
        found = true;
        break;
      }

      ++j;
    }

    if ((!found && is_strspn) || (found && !is_strspn)) {
      return len;
    }

    ++len;
    ++i;
    j = 0;
  }

  return len;
}

size_t Strspn(const char* dest, const char* src) {
  return StrCounter(dest, src, true);
}

size_t Strcspn(const char* dest, const char* src) {
  return StrCounter(dest, src, false);
}

const char* Strpbrk(const char* dest, const char* breakset) {
  size_t i = 0;
  size_t j = 0;
  while (dest[i] != '\0') {
    while (breakset[j] != '\0') {

      if (dest[i] == breakset[j]) {
        return &(dest[i]);
      }
      ++j;
    }

    ++i;
  }
  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  int str_len = Strlen(str);
  int pattern_len = Strlen(pattern);

  for (int i = 0; i <= str_len - pattern_len; ++i) {
    int j = 0;
    while ((j < pattern_len) && (str[i + j] == pattern[j])) {
      ++j;
    }

    if (j == pattern_len) {
      return &str[i];
    }
  }

  return nullptr;
}