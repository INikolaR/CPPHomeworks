#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    for (auto it = begin; it < end; ++it) {
        for (auto jt = begin; jt < end - 1; ++jt) {
            if (!comparator(*jt, *(jt + 1))) {
                std::swap(*jt, *(jt + 1));
            }
        }
    }
}
