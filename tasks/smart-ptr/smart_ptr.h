#pragma once

#include <iostream>
#include <string>

struct Counter {
    size_t strong_count = 0;
    size_t weak_count = 0;
    Counter() : strong_count(0), weak_count(0) {
    }
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
public:
    SharedPtr() : ptr_(nullptr), counter_(new Counter()) {
        counter_->strong_count = 1;
    }

    explicit SharedPtr(T* ptr) : ptr_(ptr), counter_(new Counter()) {
        counter_->strong_count = 1;
    }

    SharedPtr(const SharedPtr<T>& rhs) : ptr_(nullptr), counter_(nullptr) {
        ptr_ = rhs.ptr_;
        counter_ = rhs.counter_;
        counter_->strong_count += 1;
    }

    SharedPtr& operator=(const SharedPtr<T>& rhs) {
        ptr_ = rhs.ptr_;
        counter_ = rhs.counter_;
        counter_->strong_count += 1;
        return *this;
    }

    SharedPtr(SharedPtr<T>&& rhs) : ptr_(nullptr), counter_(new Counter()) {
        std::swap(ptr_, rhs.ptr_);
        std::swap(counter_, rhs.counter_);
        counter_->strong_count += 1;
    }

    SharedPtr& operator=(SharedPtr<T>&& rhs) {
        ptr_ = nullptr;
        counter_ = new Counter();
        std::swap(ptr_, rhs.ptr_);
        std::swap(counter_, rhs.counter_);
        counter_->strong_count += 1;
        return *this;
    }

    explicit SharedPtr(const WeakPtr<T>& rhs);

    T* Get() const {
        return ptr_;
    }

    Counter* GetCounter() const {
        return counter_;
    }

    T operator*() {
        return *ptr_;
    }

    void Reset(T* ptr) {
        --counter_->strong_count;
        if (counter_->strong_count == 0) {
            if (counter_->weak_count == 0) {
                delete counter_;
            }
            delete ptr_;
        }
        ptr_ = ptr;
        counter_ = new Counter();
        counter_->strong_count = 1;
    }

    ~SharedPtr() {
        //        std::cout << "Called strong destructor, counter: strong = " << counter_->strong_count
        //                  << "; weak = " << counter_->weak_count << '\n';
        --counter_->strong_count;
        if (counter_->strong_count == 0) {
            if (counter_->weak_count == 0) {
                delete counter_;
            }
            delete ptr_;
        }
    }

private:
    T* ptr_;
    Counter* counter_;
};

template <class T>
class WeakPtr {
public:
    WeakPtr() : ptr_(nullptr), counter_(new Counter()) {
        counter_->weak_count = 1;
    }

    WeakPtr(const WeakPtr<T>& rhs) : ptr_(nullptr), counter_(nullptr) {
        ptr_ = rhs.ptr_;
        counter_ = rhs.counter_;
        counter_->weak_count += 1;
    }

    explicit WeakPtr(const SharedPtr<T>& rhs) : ptr_(nullptr), counter_(nullptr) {
        ptr_ = rhs.Get();
        counter_ = rhs.GetCounter();
        counter_->weak_count += 1;
    }

    WeakPtr& operator=(const WeakPtr<T>& rhs) {
        ptr_ = rhs.Get();
        counter_ = rhs.GetCounter();
        counter_->weak_count += 1;
        return *this;
    }

    WeakPtr(WeakPtr<T>&& rhs) : ptr_(nullptr), counter_(new Counter()) {
        std::swap(ptr_, rhs.ptr_);
        std::swap(counter_, rhs.counter_);
    }

    WeakPtr& operator=(const SharedPtr<T>& rhs) {
        ptr_ = rhs.Get();
        counter_ = rhs.GetCounter();
        counter_->weak_count += 1;
        return *this;
    }

    WeakPtr& operator=(WeakPtr<T>&& rhs) {
        ptr_ = nullptr;
        counter_ = new Counter();
        std::swap(ptr_, rhs.ptr_);
        std::swap(counter_, rhs.counter_);
        return *this;
    }

    SharedPtr<T> Lock() {
        return SharedPtr(*this);
    }

    bool IsExpired() {
        return counter_->strong_count == 0;
    }

    T* Get() const {
        return ptr_;
    }

    Counter* GetCounter() const {
        return counter_;
    }

    ~WeakPtr() {
        //        std::cout << "Called weak destructor, counter: strong = " << counter_->strong_count
        //                  << "; weak = " << counter_->weak_count << '\n';
        --counter_->weak_count;
        //        std::cout << "After DECREASING weak destructor, counter: strong = " << counter_->strong_count
        //                  << "; weak = " << counter_->weak_count << '\n';
        if (counter_->strong_count == 0 && counter_->weak_count == 0) {
            delete counter_;
        }
    }

private:
    T* ptr_;
    Counter* counter_;
};

template <class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& rhs) : ptr_(nullptr), counter_(nullptr) {
    counter_ = rhs.GetCounter();
    ptr_ = rhs.Get();
    if (counter_->strong_count == 0) {
        ptr_ = nullptr;
    }
    counter_->strong_count += 1;
}
