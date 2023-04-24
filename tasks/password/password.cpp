#include "password.h"

bool IsCorrect(const char& letter) {
    return '!' <= letter && letter <= '~';
}

bool IsLower(const char& letter) {
    return 'a' <= letter && letter <= 'z';
}

bool IsUpper(const char& letter) {
    return 'A' <= letter && letter <= 'Z';
}

bool IsDigit(const char& letter) {
    return '0' <= letter && letter <= '9';
}

bool IsOther(const char& letter) {
    return !IsLower(letter) && !IsUpper(letter) && !IsDigit(letter);
}

bool ValidatePassword(const std::string& password) {
    bool has_digits = false;
    bool has_lower = false;
    bool has_upper = false;
    bool has_other = false;
    const int min_length = 8;
    const int max_length = 14;
    if (password.length() < min_length || password.length() > max_length) {
        return false;
    }
    for (size_t i = 0; i < password.length(); ++i) {
        if (!IsCorrect(password[i])) {
            return false;
        }
        has_digits = has_digits || IsDigit(password[i]);
        has_lower = has_lower || IsLower(password[i]);
        has_upper = has_upper || IsUpper(password[i]);
        has_other = has_other || IsOther(password[i]);
    }
    int sum = (has_digits ? 1 : 0) + (has_lower ? 1 : 0) + (has_upper ? 1 : 0) + (has_other ? 1 : 0);
    return sum >= 3;
}