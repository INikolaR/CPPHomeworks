#include "provinces.h"

#include <cstdint>
#include <set>

int64_t CountPassports(const std::vector<int>& provinces) {
    std::set<int64_t> provinces_set{};
    for (const auto& province : provinces) {
        provinces_set.insert(province);
    }
    int64_t count_passports = 0;

    while (provinces_set.size() > 1) {
        int64_t new_passports = *provinces_set.begin();
        provinces_set.erase(provinces_set.begin());
        new_passports += *provinces_set.begin();
        provinces_set.erase(provinces_set.begin());
        provinces_set.insert(new_passports);
        count_passports += new_passports;
    }
    return count_passports;
}
