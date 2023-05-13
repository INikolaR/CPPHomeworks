#include "rational.h"

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int64_t gcd = std::gcd(numer, denom);
    numer_ = numer / gcd;
    denom_ = denom / gcd;
    if (denom_ < 0) {
        denom_ *= -1;
        numer_ *= -1;
    }
}

Rational::Rational() {
    Set(0, 1);
}

Rational::Rational(int value) {
    Set(value, 1);
}

Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}

int Rational::GetDenominator() const {
    return denom_;
}

int Rational::GetNumerator() const {
    return numer_;
}

void Rational::SetNumerator(int value) {
    Set(value, denom_);
}

void Rational::SetDenominator(int value) {
    Set(numer_, value);
}

Rational operator+(const Rational& ratio) {
    return Rational(ratio.GetNumerator(), ratio.GetDenominator());
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int lcm = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int lhs_multiplier = lcm / lhs.GetDenominator();
    int rhs_multiplier = lcm / rhs.GetDenominator();
    return Rational(lhs.GetNumerator() * lhs_multiplier + rhs.GetNumerator() * rhs_multiplier, lcm);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    return lhs + -rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.GetNumerator() * rhs.GetDenominator(), lhs.GetDenominator() * rhs.GetNumerator());
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() < lhs.GetDenominator() * rhs.GetNumerator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() > lhs.GetDenominator() * rhs.GetNumerator();
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return lhs > rhs || lhs == rhs;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator();
    if (ratio.GetDenominator() != 1) {
        os << "/" << ratio.GetDenominator();
    }
    return os;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs = lhs * rhs;
    return lhs;
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs = lhs / rhs;
    return lhs;
}

Rational operator++(Rational& ratio, int) {
    Rational temp = Rational(ratio);
    ++ratio;
    return temp;
}

Rational operator--(Rational& ratio, int) {
    Rational temp = Rational(ratio);
    --ratio;
    return temp;
}

Rational& operator++(Rational& ratio) {
    ratio.SetNumerator(ratio.GetNumerator() + ratio.GetDenominator());
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.SetNumerator(ratio.GetNumerator() - ratio.GetDenominator());
    return ratio;
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    std::string input;
    is >> input;
    size_t split_index = input.find('/');
    if (split_index == std::string::npos) {
        ratio = Rational(std::stoi(input), 1);
    } else {
        int numer = std::stoi(input.substr(0, split_index));
        int denom = std::stoi(input.substr(split_index + 1));
        ratio = Rational(numer, denom);
    }
    return is;
}
