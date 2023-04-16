#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    int64_t a = 0;
    int64_t b = 1;
    for (int64_t i = 1; i < n; ++i) {
        int64_t t = b;
        b = a + b;
        a = t;
    }
    return b;
}
