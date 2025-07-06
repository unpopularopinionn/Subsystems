#include "string.h"

/* Returns length of null-terminated string */
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

/* Compares two strings (null-terminated), returns 0 if equal */
int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

/* Compares up to n characters of two strings */
int strncmp(const char* s1, const char* s2, size_t n) {
    size_t i = 0;
    while (i < n && s1[i] && (s1[i] == s2[i])) {
        i++;
    }
    if (i == n) return 0;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

/* Copies null-terminated string src to dest */
char* strcpy(char* dest, const char* src) {
    char* orig = dest;
    while ((*dest++ = *src++));
    return orig;
}

/* Copies up to n bytes from src to dest, pads with '\0' */
char* strncpy(char* dest, const char* src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i]; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

/* Sets first num bytes of ptr to value */
void* memset(void* ptr, int value, size_t num) {
    unsigned char* p = (unsigned char*)ptr;
    for (size_t i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}

/* Copies num bytes from src to dest, no overlap handling */
void* memcpy(void* dest, const void* src, size_t num) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (size_t i = 0; i < num; i++) {
        d[i] = s[i];
    }
    return dest;
}

/* Copies num bytes from src to dest, handles overlap */
void* memmove(void* dest, const void* src, size_t num) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    if (d < s) {
        for (size_t i = 0; i < num; i++) {
            d[i] = s[i];
        }
    } else if (d > s) {
        for (size_t i = num; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }
    return dest;
}

/* Compares first num bytes of ptr1 and ptr2 */
int memcmp(const void* ptr1, const void* ptr2, size_t num) {
    const unsigned char* p1 = (const unsigned char*)ptr1;
    const unsigned char* p2 = (const unsigned char*)ptr2;
    for (size_t i = 0; i < num; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

/* Searches first num bytes of ptr for value */
void* memchr(const void* ptr, int value, size_t num) { 
    const unsigned char* p = (const unsigned char*)ptr;
    unsigned char val = (unsigned char)value;
    for (size_t i = 0; i < num; i++) {
        if (p[i] == val) {
            return (void*)(p + i);
        }
    }
    return NULL;
}

/* Converts a decimal string to an integer*/
int atoi(const char* str) {
    int result = 0;
    int sign = 1;

    // Skip whitespace
    while (*str == ' ' || *str == '\t' || *str == '\n') {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    return sign * result;
}
// i shouldnt have even suggested doing this..this is torture