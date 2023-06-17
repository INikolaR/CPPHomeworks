#pragma once

#include <cstddef>
#include <utility>

template <class T>
class ListNode {
public:
    ListNode() : value_(nullptr), next_(this), prev_(this) {
    }

    explicit ListNode(T* const& value) : value_(nullptr), next_(this), prev_(this) {
        value_ = new T(*value);
    }

    explicit ListNode(T value) : value_(new T(value)), next_(this), prev_(this) {
    }

    ListNode* Prev() {
        return prev_;
    }

    ListNode* Next() {
        return next_;
    }

    T& Value() {
        return *value_;
    }

    friend void Unlink(ListNode<T>* node) {
        if (node->value_ == nullptr) {
            return;
        }
        node->prev_->next_ = node->next_;
        node->next_->prev_ = node->prev_;
        delete node;
    }

    friend void LinkAfter(ListNode<T>* target, ListNode<T>* after) {
        target->next_->prev_ = after;
        after->next_ = target->next_;
        target->next_ = after;
        after->prev_ = target;
    }

private:
    T* value_;
    ListNode* next_;
    ListNode* prev_;
};

template <typename T>
class List {
public:
    class Iterator {
    public:
        explicit Iterator(auto ptr) : ptr_(ptr) {
        }
        Iterator& operator++() {
            ptr_ = ptr_->Next();
            return *this;
        }
        Iterator operator++(int) {
            auto old_ptr = ptr_;
            ++ptr_;
            return Iterator(old_ptr);
        }

        Iterator& operator--() {
            ptr_ = ptr_->Prev();
            return *this;
        }
        Iterator operator--(int) {
            auto old_ptr = ptr_;
            --ptr_;
            return Iterator(old_ptr);
        }

        T& operator*() const {
            return ptr_->Value();
        }
        T* operator->() const {
            return ptr_->value_;
        }

        bool operator==(const Iterator& rhs) const {
            return ptr_ == rhs.ptr_;
        }
        bool operator!=(const Iterator& rhs) const {
            return ptr_ != rhs.ptr_;
        }

    private:
        ListNode<T>* ptr_ = nullptr;
    };

    List() : ptr_(new ListNode<T>()), size_(0) {
    }
    List(const List& list) {
        ptr_ = new ListNode<T>();
        auto it = list.ptr_->Prev();
        while (it != list.ptr_) {
            LinkAfter(ptr_, new ListNode(it->Value()));
            it = it->Prev();
        }
        size_ = list.Size();
    }
    List(List&& list) {
        std::swap(ptr_, list.ptr_);
        std::swap(size_, list.size_);
        while (size_ != 0) {
            list.PopBack();
        }
        delete &list;
    }
    ~List() {
        while (size_ != 0) {
            PopBack();
        }
    }

    List& operator=(const List& list) {
        ptr_ = new ListNode<T>();
        auto it = list.ptr_->Prev();
        while (it != list.ptr_) {
            LinkAfter(ptr_, new ListNode(it->Value()));
            it = it->Prev();
        }
        size_ = list.Size();
        return *this;
    }
    List& operator=(List&& list) {
        std::swap(ptr_, list.ptr_);
        std::swap(size_, list.size_);
        while (size_ != 0) {
            PopBack();
        }
        return *this;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }
    size_t Size() const {
        return size_;
    }

    void PushBack(const T& elem) {
        LinkAfter(ptr_->Prev(), new ListNode<T>(elem));
        ++size_;
    }
    void PushBack(T&& elem) {
        LinkAfter(ptr_->Prev(), new ListNode<T>(&elem));
        ++size_;
    }
    void PushFront(const T& elem) {
        LinkAfter(ptr_, new ListNode(elem));
        ++size_;
    }
    void PushFront(T&& elem) {
        LinkAfter(ptr_, new ListNode(&elem));
        ++size_;
    }

    T& Front() {
        return *Begin();
    }
    const T& Front() const {
        return ptr_->Next()->Value();
    }
    T& Back() {
        return *End();
    }
    const T& Back() const {
        return ptr_->Prev()->Value();
    }

    void PopBack() {
        if (size_ == 0) {
            return;
        }
        Unlink(ptr_->Prev());
        --size_;
    }
    void PopFront() {
        if (size_ == 0) {
            return;
        }
        Unlink(ptr_->Next());
        --size_;
    }

    Iterator Begin() {
        return ++Iterator(ptr_);
    }
    Iterator End() {
        return --Iterator(ptr_);
    }

private:
    ListNode<T>* ptr_;
    size_t size_;
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {
    return ++list.End();
}
