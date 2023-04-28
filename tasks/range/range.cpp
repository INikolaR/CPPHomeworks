#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> range;
    if (step == 0) {
        return range;
    }
    if (step > 0) {
        if (from >= to) {
            return range;
        }
        while (from < to) {
            range.push_back(from);
            from += step;
        }
    } else {
        if (from <= to) {
            return range;
        }
        while (from > to) {
            range.push_back(from);
            from += step;
        }
    }
    return range;
}
