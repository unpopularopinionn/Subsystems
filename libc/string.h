#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

/* String functions */
size_t strlen(const char* str);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n); // exusce me?
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t n);

/* Memory functions */
void* memset(void* ptr, int value, size_t num);
void* memcpy(void* dest, const void* src, size_t num);
void* memmove(void* dest, const void* src, size_t num);
int memcmp(const void* ptr1, const void* ptr2, size_t num);
void* memchr(const void* ptr, int value, size_t num); // PATHETIC!

/* Conversion */
int atoi(const char* str);

#endif
