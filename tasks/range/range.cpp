#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> ans = std::vector<int>();
    if (step == 0) {
        return ans;
    }
    if (step > 0) {
        if (from >= to) {
            return ans;
        }
        while (from < to) {
            ans.push_back(from);
            from += step;
        }
    } else {
        if (from <= to) {
            return ans;
        }
        while (from > to) {
            ans.push_back(from);
            from += step;
        }
    }
    return ans;
}
