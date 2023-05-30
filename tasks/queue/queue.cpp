#include "queue.h"

Queue::Queue() {
    front_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

void Queue::Clear() {
    while (!Empty()) {
        Pop();
    }
    size_ = 0;
}

void Queue::Pop() {
    if (Empty()) {
        return;
    }
    if (Size() == 1) {
        tail_ = nullptr;
    }
    Node* new_front = front_->next;
    delete front_;
    front_ = new_front;
    --size_;
}

bool Queue::Empty() const {
    return size_ == 0;
}

Queue::~Queue() {
    Clear();
}

void Queue::Push(int32_t value) {
    if (Empty()) {
        front_ = new Node(value, nullptr);
        tail_ = front_;
        size_ = 1;
    } else {
        tail_->next = new Node(value, nullptr);
        tail_ = tail_->next;
        ++size_;
    }
}

int32_t Queue::Size() const {
    return size_;
}

int32_t Queue::Front() const {
    return front_->value;
}

Node::Node(int32_t value, Node* next) {
    this->value = value;
    this->next = next;
}