#include "cppstring.h"

#include <utility>

String::String() {
    size_ = 0;
    capacity_ = 0;
    data_ = new char[1]{'\0'};
}

String::String(size_t size, char symbol) {
    size_ = size;
    capacity_ = size;
    data_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = symbol;
    }
    data_[size_] = '\0';
}

String::String(const char *src) {
    size_ = 0;
    while (src[size_] != '\0') {
        ++size_;
    }
    data_ = new char[size_ + 1];
    capacity_ = size_;
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
    data_[size_] = '\0';
}

String::String(const char *src, size_t size) {
    size_ = size;
    data_ = new char[size + 1];
    capacity_ = size_;
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
    data_[size_] = '\0';
}

String::~String() {
    if (data_ != nullptr) {
        delete[] data_;
    }
}

String::String(const String &other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    data_[size_] = '\0';
}

String &String::operator=(const String &other) {
    if (data_ != nullptr) {
        delete[] data_;
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    data_[size_] = '\0';
    return *this;
}

const char &String::operator[](size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange{};
    }
    return data_[idx];
}

char &String::operator[](size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange{};
    }
    return data_[idx];
}

const char &String::At(size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange{};
    }
    return data_[idx];
}

char &String::At(size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange{};
    }
    return data_[idx];
}

const char &String::Front() const {
    return data_[0];
}

char &String::Front() {
    return data_[0];
}

const char &String::Back() const {
    return data_[size_ - 1];
}

char &String::Back() {
    return data_[size_ - 1];
}

const char *String::Data() const {
    if (Empty()) {
        return nullptr;
    }
    return data_;
}

char *String::Data() {
    if (Empty()) {
        return nullptr;
    }
    return data_;
}

const char *String::CStr() const {
    return Data();
}

char *String::CStr() {
    return Data();
}

bool String::Empty() const {
    return size_ == 0;
}

size_t String::Size() const {
    return size_;
}

size_t String::Length() const {
    return size_;
}

size_t String::Capacity() const {
    return capacity_;
}

void String::Clear() {
    if (data_ != nullptr) {
        delete[] data_;
    }
    data_ = new char[1]{'\0'};
    size_ = 0;
    capacity_ = 0;
}

void String::Swap(String &other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void String::PopBack() {
    if (!Empty()) {
        --size_;
        data_[size_] = '\0';
    }
}

void String::PushBack(char c) {
    if (capacity_ == 0) {
        size_ = 1;
        capacity_ = 1;
        data_ = new char[2]{c, '\0'};
        return;
    }
    if (size_ >= capacity_) {
        char *old_data = data_;
        data_ = new char[(capacity_ << 1) + 1];
        for (size_t i = 0; i < capacity_; ++i) {
            data_[i] = old_data[i];
        }
        capacity_ <<= 1;
        delete[] old_data;
    }
    data_[size_++] = c;
    data_[size_] = '\0';
}

void String::Resize(size_t new_size, char symbol) {
    if (new_size < size_) {
        size_ = new_size;
        data_[size_] = '\0';
        return;
    }
    Reserve(new_size);
    while (size_ < new_size) {
        data_[size_++] = symbol;
    }
    data_[size_] = '\0';
}

void String::Reserve(size_t new_capacity) {
    if (new_capacity == capacity_) {
        return;
    }
    if (new_capacity < capacity_) {
        return;
    }
    char *old_data = data_;
    capacity_ = new_capacity;
    data_ = new char[new_capacity + 1];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = old_data[i];
    }
    data_[size_] = '\0';
    delete[] old_data;
}

void String::ShrinkToFit() {
    char *old_data = data_;
    capacity_ = size_;
    data_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = old_data[i];
    }
    data_[size_] = '\0';
    delete[] old_data;
}

int String::Compare(const String &other) const {
    if (size_ == 0) {
        return other.Size() == 0 ? 0 : -1;
    }
    if (size_ == other.size_) {
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] == other.data_[i]) {
                continue;
            }
            return data_[i] - other.data_[i];
        }
        return 0;
    } else {
        return static_cast<int>(this->size_) - static_cast<int>(other.size_);
    }
}

String &String::operator+=(const String &other) {
    for (size_t i = 0; i < other.Size(); ++i) {
        PushBack(other[i]);
    }
    return *this;
}

String operator+(const String &first, const String &second) {
    String concat = String();
    concat.Reserve(first.size_ + second.size_);
    for (size_t i = 0; i < first.size_; ++i) {
        concat.PushBack(first[i]);
    }
    for (size_t i = 0; i < second.size_; ++i) {
        concat.PushBack(second[i]);
    }
    concat.data_[first.size_ + second.size_] = '\0';
    return concat;
}

std::ostream &operator<<(std::ostream &stream, const String &string) {
    for (size_t i = 0; i < string.Size(); ++i) {
        stream << string[i];
    }
    return stream;
}

bool operator==(const String &first, const String &second) {
    return first.Compare(second) == 0;
}

bool operator!=(const String &first, const String &second) {
    return first.Compare(second) != 0;
}

bool operator>(const String &first, const String &second) {
    return first.Compare(second) > 0;
}

bool operator<(const String &first, const String &second) {
    return first.Compare(second) < 0;
}

bool operator>=(const String &first, const String &second) {
    return first.Compare(second) >= 0;
}

bool operator<=(const String &first, const String &second) {
    return first.Compare(second) <= 0;
}
