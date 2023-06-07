#pragma once

template <class T>
class Vector {
public:
    Vector() {
        data_ = new T[1]{T()};
        size_ = 0;
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
        data_ = move.data_;
        move.data_ = nullptr;
        move.size_ = 0;
        move.capacity_ = 0;
    }

    Vector& operator=(const Vector& copy) {
        delete[] data_;
        size_ = copy.size_;
        capacity_ = copy.capacity_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = copy.data_[i];
        }
        return *this;
    }

    Vector& operator=(Vector&& move) {
        if (&move == this) {
            return *this;
        }
        size_ = move.size_;
        capacity_ = move.capacity_;
        delete[] data_;
        data_ = move.data_;
        move.data_ = nullptr;
        move.size_ = 0;
        move.capacity_ = 0;
        return *this;
    }

    ~Vector() {
        delete[] data_;
    }

    void Swap(Vector<T>& vec) {
        std::swap(data_, vec.data_);
        std::swap(size_, vec.size_);
        std::swap(capacity_, vec.capacity_);
    }

    T& operator[](size_t index) {
        return data_[index];
    };

    const T& operator[](size_t index) const {
        return data_[index];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(T element) {
        if (Capacity() == 0) {
            data_ = new T[1]{element};
            size_ = 1;
            capacity_ = 1;
            return;
        }
        if (size_ == capacity_) {
            T* old_data = data_;
            data_ = new T[capacity_ << 1];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = old_data[i];
            }
            capacity_ <<= 1;
            delete[] old_data;
        }
        data_[size_++] = element;
    }

    void PopBack() {
        if (size_ != 0) {
            --size_;
        }
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T* old_data = data_;
            data_ = new T[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = old_data[i];
            }
            capacity_ = new_capacity;
            delete[] old_data;
        }
    }

    class Iterator : std::iterator<std::random_access_iterator_tag, T> {
    public:
        Iterator() {
            pointer_ = nullptr;
        }

        Iterator& operator+=(size_t index) {
            pointer_ += index;
            return *this;
        }

        friend Iterator operator+(const Iterator& it, size_t index) {
            return Iterator(it.pointer_ + index);
        }

        friend Iterator operator+(size_t index, const Iterator& it) {
            return Iterator(it.pointer_ + index);
        }

        Iterator& operator-=(size_t index) {
            pointer_ -= index;
            return *this;
        }

        friend Iterator operator-(const Iterator& it, size_t index) {
            return Iterator(it.pointer_ - index);
        }

        friend size_t operator-(const Iterator& a, const Iterator& b) {
            return a.pointer_ - b.pointer_;
        }

        friend size_t operator==(const Iterator& a, const Iterator& b) {
            return a.pointer_ == b.pointer_;
        }

        friend size_t operator!=(const Iterator& a, const Iterator& b) {
            return a.pointer_ != b.pointer_;
        }

        T operator*() {
            return *pointer_;
        }

        explicit Iterator(T* pointer) {
            pointer_ = pointer;
        }

        Iterator operator++() {
            ++pointer_;
            return *this;
        }

        friend Iterator operator++(Iterator& it, int) {
            T* old_pointer = it.pointer_;
            ++it.pointer_;
            return Iterator(old_pointer);
        }

        Iterator operator--() {
            --pointer_;
            return *this;
        }

        friend Iterator operator--(Iterator& it, int) {
            T* old_pointer = it.pointer_;
            --it.pointer_;
            return Iterator(old_pointer);
        }

        T* operator->() {
            return pointer_;
        }

    private:
        T* pointer_;
    };

    Iterator Begin() {
        return Iterator(data_);
    }

    Iterator End() {
        return Iterator(data_ + size_);
    }

    Iterator begin() {  // NOLINT
        return Begin();
    }

    Iterator end() {  // NOLINT
        return End();
    }

private:
    T* data_;
    size_t size_;
    size_t capacity_;
};
