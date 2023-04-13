#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    if (n == 0) {
        return 0;
    }
    else if (n == 1){
        return 1;
    }
    else {
        return CalculateNthFibonacci(n - 1) + CalculateNthFibonacci(n - 2);
    }
}
