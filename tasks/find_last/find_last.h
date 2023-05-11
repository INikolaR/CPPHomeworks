#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    if (first == last) {
        return last;
    }
    for (auto it = last - 1; it >= first; --it) {
        if (*it == val) {
            return it;
        }
    }
    return last;
}
