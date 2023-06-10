#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

using std::string;

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> vec;
    for (const auto& item : items) {
        vec.emplace_back(std::make_unique<T>(*item));
    }
    return vec;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    struct Comp {
        bool operator()(const std::shared_ptr<T>& lsh, const std::shared_ptr<T>& rsh) const {
            return *lsh < *rsh;
        }
    };

    std::vector<std::shared_ptr<T>> vec;
    std::set<std::shared_ptr<T>, Comp> pool;
    for (const auto& item : items) {
        auto copy = std::make_shared<T>(*item);
        auto copy_copy = *pool.insert(copy).first;
        vec.push_back(copy_copy);
    }
    return vec;
}
