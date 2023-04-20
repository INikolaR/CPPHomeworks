#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    unsigned long long l = 0;
    unsigned long long r = str.length() - 1;
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
