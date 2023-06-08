#pragma once

#include <utility>
#include <vector>

template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

private:
    Iterator begin_, end_;
};

template <class T>
class RangeIterator {
public:
    explicit RangeIterator(T curr, T step) : curr_(curr), step_(step) {
    }

    RangeIterator& operator++() {
        curr_ += step_;
        return *this;
    }

    int operator*() const {
        return curr_;
    }

    bool operator!=(const RangeIterator& i) const {
        return curr_ < i.curr_;
    }

private:
    T curr_;
    T step_;
};

template <class T>
auto Range(T from, T to, T step) {
    return IteratorRange(RangeIterator(from, step), RangeIterator(to, step));
}

template <class T>
auto Range(T from, T to) {
    return Range(from, to, T{1});
}

template <class T>
auto Range(T to) {
    return Range(T{0}, to);
}

template <class T, class U>
class ZipIterator {
public:
    ZipIterator(T first, U second) {
        first_ = first;
        second_ = second;
    }

    ZipIterator& operator++() {
        ++first_;
        ++second_;
        return *this;
    }

    auto operator*() const {
        return std::make_pair(*first_, *second_);
    }

    bool operator!=(const ZipIterator& i) const {
        return first_ != i.first_ && second_ != i.second_;
    }

private:
    T first_;
    U second_;
};

template <class T, class U>
auto Zip(const T& first_container, const U& second_container) {
    return IteratorRange(ZipIterator(first_container.begin(), second_container.begin()),
                         ZipIterator(first_container.end(), second_container.end()));
}

template <class T>
class GroupIterator {
public:
    GroupIterator(T curr, T end) {
        curr_ = curr;
        end_ = end;
    }

    GroupIterator& operator++() {
        for (;;) {
            auto prev = curr_;
            ++curr_;
            if (curr_ != end_ || *curr_ != *prev) {
                break;
            }
        }
        return *this;
    }

    auto operator*() const {
        T next = curr_;
        while (next != end_ && *next != *curr_) {
            ++next;
        }
        return IteratorRange(curr_, next);
    }

    bool operator!=(const GroupIterator& i) const {
        return curr_ != i.curr_;
    }

private:
    T curr_, end_;
};

template <class T>
auto Group(const T& data) {
    return IteratorRange(GroupIterator(data.begin(), data.end()), GroupIterator(data.end(), data.end()));
}
