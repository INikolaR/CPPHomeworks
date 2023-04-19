#include "reduce_fraction.h"

#include <math.h>

#include <numeric>

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t sign = (numerator > 0 ? 1 : -1) * (denominator > 0 ? 1 : -1);
    int64_t d = std::gcd(abs(numerator), abs(denominator));
    int64_t a = abs(numerator) / d;
    int64_t b = abs(denominator) / d;
    return sign * a + b;
}
