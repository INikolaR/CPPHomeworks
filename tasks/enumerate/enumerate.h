#pragma once

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

template <class T, class U>
class EnumerateIterator {
public:
    explicit EnumerateIterator(T ptr, U& value) : value_(value), index_(0), ptr_(ptr) {
    }

    EnumerateIterator& operator++() {
        ++ptr_;
        value_ = *ptr_;
        ++index_;
        return *this;
    }

    std::pair<int, U&> operator*() {
        U& r = *ptr_;
        return {index_, r};
    }

    bool operator!=(const EnumerateIterator& i) const {
        return ptr_ != i.ptr_;
    }

private:
    U& value_;
    int index_;
    T ptr_;
};

template <class T>
auto Enumerate(T c) {
    return IteratorRange(EnumerateIterator(c.begin(), *c.begin()), EnumerateIterator(c.end(), *c.end()));
}
