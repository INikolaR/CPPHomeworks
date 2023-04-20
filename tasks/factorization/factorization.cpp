#include "factorization.h"

#include <cstdint>

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> ans = std::vector<std::pair<int64_t, int>>(0);
    for (int64_t i = 2; i * i <= x; ++i) {
        int num = 0;
        while (x % i == 0) {
            ++num;
            x /= i;
        }
        ans.push_back({i, num});
    }
    return ans;
}
