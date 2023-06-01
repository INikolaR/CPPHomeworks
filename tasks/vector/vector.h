#pragma once

template <class T>
class Vector {
public:
    Vector() {
        data_ = new T[1]{0};
        size_ = 1;
        capacity_ = 1;
    }

    explicit Vector(size_t size) {
        data_ = new T[size];
        size_ = size;
        capacity_ = size;
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = T();
        }
    }

    Vector(std::initializer_list<int> init_list) {
        data_ = new T[init_list.size()];
        size_ = 0;
        capacity_ = init_list.size();
        for (auto it = init_list.begin(); it != init_list.end(); ++it) {
            data_[size_++] = *it;
        }
    }

    Vector(const Vector& copy) {
        size_ = copy.size_;
        capacity_ = copy.capacity_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = copy.data_[i];
        }
    }

    Vector(Vector&& move) {
        size_ = move.size_;
        capacity_ = move.capacity_;
        delete[] data_;
        data_ = move.data_;
    }

    Vector& operator=(const Vector& copy) {
        size_ = copy.size_;
        capacity_ = copy.capacity_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = copy.data_[i];
        }
        return *this;
    }

    Vector& operator=(Vector&& move) {
        size_ = move.size_;
        capacity_ = move.capacity_;
        delete[] data_;
        data_ = move.data_;
    }

    ~Vector() {
        delete[] data_;
    }

    void Swap(const Vector& vec1, const Vector& vec2) {
        std::swap(vec1.data_, vec2.data_);
        std::swap(vec1.size_, vec2.size_);
        std::swap(vec1.capacity_, vec2.capacity_);
    }

private:
    T* data_;
    size_t size_;
    size_t capacity_;
};
