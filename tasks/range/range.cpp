#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> ans = std::vector<int>();
    if (step > 0) {
        while (from < to) {
            ans.push_back(from);
            from += step;
        }
    } else {
        while (from > to) {
            ans.push_back(from);
            from += step;
        }
    }
    return ans;
}
