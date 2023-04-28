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
    const int MIN_LENGTH = 8;
    const int MAX_LENGTH = 14;
    if (password.length() < MIN_LENGTH || password.length() > MAX_LENGTH) {
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
    int sum = has_digits + has_lower + has_upper + has_other;
    return sum >= 3;
}
