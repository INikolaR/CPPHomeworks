#pragma once

template <typename T>
T Unique(T begin, T end) {
    if (begin == end) {
        return begin;
    }
    T current_end = begin + 1;
    for (T it = begin + 1; it != end; ++it) {
        if (*it != *(it - 1)) {
            *current_end = *it;
            ++current_end;
        }
    }
    return current_end;
}
