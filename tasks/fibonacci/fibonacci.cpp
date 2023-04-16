#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1){
        return 1;
    }
    int a = 0;
    int b = 1;
    for (int i = 1; i < n; ++i) {
        int t = b;
        b = a + b;
        a = t;
    }
    return b;
}
