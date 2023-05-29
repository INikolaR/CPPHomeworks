#include "cstring.h"

#include <cstddef>

size_t Strlen(const char *str) {
    size_t size = 0;
    while (str[size] != '\0') {
        ++size;
    }
    return size;
}

int Strcmp(const char *first, const char *second) {
    size_t i = 0;
    while (first[i] != '\0' && second[i] != '\0') {
        if (first[i] != second[i]) {
            return first[i] - second[i];
        }
        ++i;
    }
    if (first[i] == '\0') {
        if (second[i] == '\0') {
            return 0;
        } else {
            return -1;
        }
    } else {
        return 1;
    }
}

int Strncmp(const char *first, const char *second, size_t count) {
    size_t i = 0;
    while (first[i] != '\0' && second[i] != '\0' && i < count) {
        if (first[i] != second[i]) {
            return first[i] - second[i];
        }
        ++i;
    }
    if (first[i] == '\0') {
        if (second[i] == '\0') {
            return 0;
        } else {
            return -1;
        }
    } else {
        if (second[i] == '\0') {
            return 1;
        } else {
            return 0;
        }
    }
}

char *Strcpy(char *dest, const char *src) {
    size_t i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return dest;
}

char *Strncpy(char *dest, const char *src, size_t count) {
    size_t i = 0;
    while (src[i] != '\0' && i < count) {
        dest[i] = src[i];
        ++i;
    }
    dest[i++] = '\0';
    while (i < count) {
        dest[i++] = '\0';
    }
    return dest;
}

char *Strcat(char *dest, const char *src) {
    size_t dest_size = Strlen(dest);
    size_t i = 0;
    while (src[i] != '\0') {
        dest[dest_size + i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return dest;
}

char *Strncat(char *dest, const char *src, size_t count) {
    size_t dest_size = Strlen(dest);
    size_t i = 0;
    while (src[i] != '\0' && i < count) {
        dest[dest_size + i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return dest;
}

const char *Strchr(const char *str, char symbol) {
    if (symbol == '\0') {
        return str + Strlen(str);
    }
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == symbol) {
            return str + i;
        }
        ++i;
    }
    return nullptr;
}

const char *Strrchr(const char *str, char symbol) {
    size_t i = Strlen(str);
    while (i != 0) {
        if (str[i] == symbol) {
            return str + i;
        }
        --i;
    }
    if (str[0] == symbol) {
        return str;
    } else {
        return nullptr;
    }
}

size_t Strspn(const char *dest, const char *src) {
    size_t i = 0;
    while (dest[i] != '\0') {
        size_t j = 0;
        bool found = false;
        while (src[j] != '\0') {
            if (src[j] == dest[i]) {
                found = true;
                break;
            }
            ++j;
        }
        if (!found) {
            return i;
        }
        ++i;
    }
    return i;
}

size_t Strcspn(const char *dest, const char *src) {
    size_t i = 0;
    while (dest[i] != '\0') {
        size_t j = 0;
        bool found = false;
        while (src[j] != '\0') {
            if (src[j] == dest[i]) {
                found = true;
                break;
            }
            ++j;
        }
        if (found) {
            return i;
        }
        ++i;
    }
    return i;
}

const char *Strpbrk(const char *dest, const char *breakset) {
    size_t prefix = Strcspn(dest, breakset);
    if (prefix == Strlen(dest)) {
        return nullptr;
    } else {
        return dest + prefix;
    }
}

const char *Strstr(const char *str, const char *pattern) {
    size_t i = 0;
    if (pattern[0] == '\0') {
        return str;
    }
    size_t pattern_length = Strlen(pattern);
    while (str[i] != '\0') {
        size_t j = 0;
        while (pattern[j] != '\0' && str[i + j] != '\0') {
            if (str[i + j] != pattern[j]) {
                break;
            }
            ++j;
        }
        if (j == pattern_length) {
            return str + i;
        }
        ++i;
    }
    return nullptr;
}
