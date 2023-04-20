#include "factorization.h"

#include <vector>

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> ans = std::vector<std::pair<int64_t, int>>(0);
    for (int64_t i = 2; i * i <= x; ++i) {
        int num = 0;
        while (x % i == 0) {
            ++num;
            x /= i;
        }
        if (num != 0) {
            ans.push_back(std::make_pair(i, num));
        }
    }
    if (x != 1) {
        ans.push_back(std::make_pair(x, 1));
    }
    return ans;
}
