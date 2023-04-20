#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    size_t l = 0;
    size_t r = str.length() - 1;
    while (l < r) {
        while (str[l] == ' ') {
            ++l;
        }
        while (str[r] == ' ') {
            --r;
        }
        if (str[l] != str[r]) {
            return false;
        } else {
            ++l;
            --r;
        }
    }
    return true;
}
