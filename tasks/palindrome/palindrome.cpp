#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    size_t l = 0;
    size_t r = str.size() - 1;
    while (l < r) {
        while (str[l] == ' ') {
            ++l;
        }
        while (str[r] == ' ') {
            --r;
        }
        if (str[l] == str[r]) {
            ++l;
            --r;
        } else {
            return false;
        }
    }
    return true;
}
