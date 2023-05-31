#pragma once

#include <utility>

template <typename Iterator>
void Reverse(Iterator begin, Iterator end) {
    --end;
    while (begin < end) {
        std::swap(*begin, *end);
        ++begin;
        --end;
    }
}

template <typename Iterator>
void Rotate(Iterator begin, Iterator mid, Iterator end) {
    Reverse(begin, mid);
    Reverse(mid, end);
    Reverse(begin, end);
}
