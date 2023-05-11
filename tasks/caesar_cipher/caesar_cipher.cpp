#include "caesar_cipher.h"

const int ALPHABET_SIZE = 26;

size_t GetNum(char c) {
    if ('A' <= c && c <= 'Z') {
        return c - 'A';
    }
    return c - 'a';
}

char Increase(char c, size_t shift) {

    size_t num = GetNum(c);
    if ('A' <= c && c <= 'Z') {
        return (num < shift) ? static_cast<char>('A' + num - shift + ALPHABET_SIZE)
                             : static_cast<char>('A' + num - shift);
    }
    return (num < shift) ? static_cast<char>('a' + num - shift + ALPHABET_SIZE) : static_cast<char>('a' + num - shift);
}

std::string Decipher(const std::string& cipher, size_t shift) {

    std::string deciphered;
    for (size_t i = 0; i < cipher.length(); ++i) {
        deciphered += Increase(cipher[i], shift);
    }
    return deciphered;
}
