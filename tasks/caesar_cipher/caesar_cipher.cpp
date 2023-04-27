#include "caesar_cipher.h"

size_t GetNum(char c) {
    if ('A' <= c && c <= 'Z') {
        return c - 'A';
    }
    return c - 'a';
}

char Increase(char c, size_t shift) {
    const int alphabet_size = 26;
    size_t num = GetNum(c);
    if ('A' <= c && c <= 'Z') {
        return (num < shift) ? static_cast<char>('A' + num - shift + alphabet_size)
                             : static_cast<char>('A' + num - shift);
    }
    return (num < shift) ? static_cast<char>('a' + num - shift + alphabet_size) : static_cast<char>('a' + num - shift);
}

std::string Decipher(const std::string& cipher, size_t shift) {

    std::string ans;
    for (size_t i = 0; i < cipher.length(); ++i) {
        ans += Increase(cipher[i], shift);
    }
    return ans;
}
