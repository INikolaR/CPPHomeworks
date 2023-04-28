#include "stack.h"

Stack::Stack() {
    size_ = 0;
    head_ = nullptr;
}

Stack::~Stack() {
    delete head_;
}

void Stack::Push(int32_t value) {
    head_ = new Node(value, head_);
    ++size_;
}

void Stack::Pop() {
    Node* current_head = head_;
    head_ = head_->previous;
    delete current_head;
    --size_;
}

void Stack::Clear() {
    delete head_;
    size_ = 0;
}

int32_t Stack::Top() const {
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

bool Stack::Empty() const {
    return size_ == 0;
}

Node::Node(int32_t value, Node* previous) {
    this->value = value;
    this->previous = previous;
}
