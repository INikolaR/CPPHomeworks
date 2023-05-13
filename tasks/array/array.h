#pragma once

#include <cstddef>
#include <initializer_list>

template <class T>
class Array {
private:
    size_t size_;
    T* data_;

public:
    Array();

    explicit Array(size_t size);

    Array(std::initializer_list<T> list);

    Array(const Array& other);

    Array& operator=(const Array& other);

    ~Array();

    T& operator[](size_t index);

    const T& operator[](size_t index) const;

    size_t size() const;  // NOLINT

    class Iterator {
    public:
        explicit Iterator(T* current);

        Iterator& operator++();

        T& operator*();

        bool operator!=(const Iterator& other);

    private:
        T* current_;
    };

    Iterator begin() const;  // NOLINT

    Iterator end() const;  // NOLINT
};

template <class T>
Array<T>::Iterator::Iterator(T* current) {
    current_ = current;
}

template <class T>
typename Array<T>::Iterator& Array<T>::Iterator::operator++() {
    ++current_;
    return *this;
}
template <class T>
T& Array<T>::Iterator::operator*() {
    return *current_;
}
template <class T>
bool Array<T>::Iterator::operator!=(const Array::Iterator& other) {
    return current_ != other.current_;
}

template <class T>
Array<T>::Array() {
    data_ = nullptr;
    size_ = 0;
}

template <class T>
Array<T>::Array(size_t size) {
    data_ = new T[size];
    size_ = size;
}

template <class T>
Array<T>::Array(std::initializer_list<T> list) {
    size_ = list.size();
    data_ = new T[size_];
    size_t index = 0;
    for (auto elem : list) {
        data_[index++] = elem;
    }
}

template <class T>
Array<T>::Array(const Array& other) {
    size_ = other.size();
    data_ = new T[size_];
    size_t index = 0;
    for (auto elem : other) {
        data_[index++] = elem;
    }
}

template <class T>
Array<T>::~Array() {
    if (data_) {
        delete data_;
    }
}

template <class T>
T& Array<T>::operator[](size_t index) {
    return data_[index];
}

template <class T>
const T& Array<T>::operator[](size_t index) const {
    return data_[index];
}

template <class T>
size_t Array<T>::size() const {
    return size_;
}

template <class T>
typename Array<T>::Iterator Array<T>::begin() const {
    return Array::Iterator(data_);
}

template <class T>
typename Array<T>::Iterator Array<T>::end() const {
    return Array::Iterator(data_ + size_);
}
template <class T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (data_) {
        delete data_;
    }
    size_ = other.size_;
    data_ = new T[size_];
    size_t index = 0;
    for (const auto& elem : other) {
        data_[index++] = elem;
    }
    return *this;
}
