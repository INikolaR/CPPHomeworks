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
class ReversedIterator {
public:
    ReversedIterator(T curr, U& value) : curr_(curr), value_(value) {
    }

    ReversedIterator& operator++() {
        --curr_;
        return *this;
    }

    U& operator*() {
        return *curr_;
    }

    bool operator!=(const ReversedIterator& i) {
        return curr_ != i.curr_;
    }

private:
    T curr_;
    U& value_;
};

template <class T>
auto Reversed(T& c) {
    if (c.empty()) {
        T t(1);
        return IteratorRange(ReversedIterator(c.end(), *t.begin()), ReversedIterator(c.begin(), *t.begin()));
    }
    return IteratorRange(ReversedIterator(--c.end(), *(--c.end())), ReversedIterator(--c.begin(), *(--c.end())));
}
