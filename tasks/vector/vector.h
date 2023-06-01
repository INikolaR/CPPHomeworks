#pragma once

template <class T>
class Vector {
public:
    Vector() {
        data_ = new int[1]{0};
        size_ = 1;
        capacity_ = 1;
    }

    explicit Vector(size_t size) {
        data_ = new int[size];
        size_ = size;
        capacity_ = size;
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = 0;
        }
    }

    Vector(std::initializer_list<int> init_list) {
        data_ = new int[init_list.size()];
        size_ = 0;
        capacity_ = init_list.size();
        for (auto it = init_list.begin(); it != init_list.end(); ++it) {
            data_[size_++] = *it;
        }
    }

    Vector(const &Vector copy) {

    }

private:
    int* data_;
    size_t size_;
    size_t capacity_;
};
