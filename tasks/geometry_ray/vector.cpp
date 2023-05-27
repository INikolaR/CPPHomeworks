#include "vector.h"

#include <cstdint>

namespace geometry {
geometry::Vector::Vector() {
    x_coord_ = 0;
    y_coord_ = 0;
}

geometry::Vector::Vector(int64_t x, int64_t y) {
    x_coord_ = x;
    y_coord_ = y;
}

int64_t geometry::Vector::GetX() const {
    return x_coord_;
}

int64_t geometry::Vector::GetY() const {
    return y_coord_;
}

geometry::Vector geometry::Vector::operator+() const {
    return Vector(x_coord_, y_coord_);
}

geometry::Vector geometry::Vector::operator-() const {
    return Vector(-x_coord_, -y_coord_);
}

geometry::Vector geometry::Vector::operator+(const geometry::Vector &other) const {
    return Vector(x_coord_ + other.x_coord_, y_coord_ + other.y_coord_);
}

geometry::Vector geometry::Vector::operator-(const geometry::Vector &other) const {
    return Vector(x_coord_ - other.x_coord_, y_coord_ - other.y_coord_);
}

geometry::Vector geometry::Vector::operator*(int64_t number) const {
    return Vector(x_coord_ * number, y_coord_ * number);
}

geometry::Vector geometry::Vector::operator/(int64_t number) const {
    return Vector(x_coord_ / number, y_coord_ / number);
}

geometry::Vector &geometry::Vector::operator+=(const geometry::Vector &other) {
    x_coord_ += other.x_coord_;
    y_coord_ += other.y_coord_;
    return *this;
}

geometry::Vector &geometry::Vector::operator-=(const geometry::Vector &other) {
    x_coord_ -= other.x_coord_;
    y_coord_ -= other.y_coord_;
    return *this;
}

geometry::Vector &geometry::Vector::operator*=(int64_t number) {
    x_coord_ *= number;
    y_coord_ *= number;
    return *this;
}

geometry::Vector &geometry::Vector::operator/=(int64_t number) {
    x_coord_ /= number;
    y_coord_ /= number;
    return *this;
}

bool geometry::Vector::operator==(const geometry::Vector &other) const {
    return x_coord_ == other.x_coord_ && y_coord_ == other.y_coord_;
}

int64_t ScalarMult(const geometry::Vector &first, const geometry::Vector &second) {
    return first.GetX() * second.GetX() + first.GetY() * second.GetY();
}

int64_t VectorMult(const geometry::Vector &first, const geometry::Vector &second) {
    return first.GetX() * second.GetY() - first.GetY() * second.GetX();
}

double Length(Vector vector) {
    return std::sqrt(vector.GetX() * vector.GetX() + vector.GetY() * vector.GetY());
}
}  // namespace geometry
