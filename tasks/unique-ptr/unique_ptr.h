#pragma once

template <class T>
class UniquePtr {
public:
    explicit UniquePtr(T* object) {
        ptr_ = object;
    }

    UniquePtr() {
    }

    UniquePtr(const UniquePtr& copy) = delete;
    UniquePtr(UniquePtr&& move) {
        ptr_ = move.ptr_;
        move.ptr_ = nullptr;
    }

    UniquePtr& operator=(const UniquePtr& copy) = delete;
    UniquePtr& operator=(UniquePtr&& move) {
        if (ptr_ != nullptr) {
            delete ptr_;
        }
        ptr_ = move.ptr_;
        move.ptr_ = nullptr;
        return *this;
    }

    void Reset(T* target) {
        if (ptr_ != nullptr) {
            delete ptr_;
        }
        ptr_ = target;
    }

    void Reset() {
        if (ptr_ != nullptr) {
            delete ptr_;
        }
        ptr_ = nullptr;
    }

    ~UniquePtr() {
        if (ptr_ != nullptr) {
            delete ptr_;
        }
    }

    T* operator->() {
        return ptr_;
    }

private:
    T* ptr_ = nullptr;
};
