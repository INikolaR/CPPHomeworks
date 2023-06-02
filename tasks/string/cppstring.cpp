#include "cppstring.h"

#include <algorithm>
#include <utility>

String::String() {
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

String::String(size_t size, char symbol) {
    if (size == 0) {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    } else {
        size_ = size;
        capacity_ = size_;
        data_ = new char[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = symbol;
        }
    }
}

String::String(const char *src) {
    size_ = 0;
    while (src[size_] != '\0') {
        ++size_;
    }
    if (size_ == 0) {
        capacity_ = 0;
        data_ = nullptr;
    } else {
        capacity_ = size_;
        data_ = new char[capacity_];
        SafeCpy(data_, src, size_);
    }
}

String::String(const char *src, size_t size) {
    if (size == 0) {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    } else {
        size_ = size;
        capacity_ = size_;
        data_ = new char[capacity_];
        SafeCpy(data_, src, size);
    }
}

String::~String() {
    if (data_ != nullptr) {
        delete[] data_;
    }
}

String::String(const String &other) {
    if (other.Empty()) {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    } else {
        size_ = other.size_;
        capacity_ = other.size_;
        data_ = new char[capacity_];
        SafeCpy(data_, other.data_, size_);
    }
}

String &String::operator=(const String &other) {
    if (data_ != nullptr) {
        delete[] data_;
    }
    if (other.Empty()) {
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    } else {
        size_ = other.size_;
        capacity_ = other.size_;
        data_ = new char[capacity_];
        SafeCpy(data_, other.data_, size_);
    }
    return *this;
}

const char &String::operator[](size_t idx) const {
    return data_[idx];
}

char &String::operator[](size_t idx) {
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
    return data_;
}

char *String::Data() {
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
    delete[] data_;
    data_ = nullptr;
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
    }
}

void String::PushBack(char c) {
    if (capacity_ == 0) {
        size_ = 1;
        capacity_ = 1;
        data_ = new char[1]{c};
        return;
    }
    if (size_ == capacity_) {
        char *old_data = data_;
        data_ = new char[capacity_ << 1];
        SafeCpy(data_, old_data, capacity_);
        capacity_ <<= 1;
        delete[] old_data;
    }
    data_[size_++] = c;
}

void String::Resize(size_t new_size, char symbol) {
    if (new_size < size_) {
        size_ = new_size;
        return;
    }
    Reserve(new_size);
    while (size_ < new_size) {
        data_[size_++] = symbol;
    }
}

void String::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    char *old_data = data_;
    capacity_ = new_capacity;
    data_ = new char[new_capacity];
    SafeCpy(data_, old_data, size_);
    delete[] old_data;
}

void String::ShrinkToFit() {
    char *old_data = data_;
    capacity_ = size_;
    data_ = new char[capacity_];
    SafeCpy(data_, old_data, size_);
    delete[] old_data;
}

int String::Compare(const String &other) const {
    size_t min_size = std::min(Size(), other.Size());
    for (size_t i = 0; i < min_size; ++i) {
        if (data_[i] != other.data_[i]) {
            return data_[i] - other.data_[i];
        }
    }
    if (Size() == min_size) {
        if (other.Size() == min_size) {
            return 0;
        } else {
            return -1;
        }
    } else {
        return 1;
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

void SafeCpy(char *dest, const char *src, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        dest[i] = src[i];
    }
}
