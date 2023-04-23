#ifndef CSTRING_H
#define CSTRING_H

#include <iostream>
#include <cstddef>

size_t Strlen(const char* str);

int Strncmp(const char* first, const char* second, size_t count);
int Strcmp(const char* first, const char* second);

char* Strncpy(char* dest, const char* src, size_t count);
char* Strcpy(char* dest, const char* src);

char* Strcat(char* dest, const char* src);
char* Strncat(char* dest, const char* src, size_t count);

const char* Strchr(const char* str, char symbol);
const char* Strrchr(const char* str, char symbol);

size_t StrCounter(const char* dest, const char* src, bool is_strspn);
size_t Strspn(const char* dest, const char* src);
size_t Strcspn(const char* dest, const char* src);

const char* Strpbrk(const char* dest, const char* breakset);
const char* Strstr(const char* str, const char* pattern);

#endif