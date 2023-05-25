#include "point.h"

#include "segment.h"

namespace geometry {
Point::Point(int64_t x, int64_t y) {
    x_coord_ = x;
    y_coord_ = y;
}

int64_t Point::GetX() const {
    return x_coord_;
}

int64_t Point::GetY() const {
    return y_coord_;
}

void Point::SetX(int64_t x) {
    x_coord_ = x;
}

void Point::SetY(int64_t y) {
    y_coord_ = y;
}

Point& Point::Move(const Vector& vector) {
    x_coord_ += vector.GetX();
    y_coord_ += vector.GetY();
    return *this;
}

bool Point::ContainsPoint(const Point& point) const {
    return x_coord_ == point.x_coord_ && y_coord_ == point.y_coord_;
}

bool Point::CrossesSegment(const Segment& segment) const {
    Vector first(x_coord_ - segment.GetStart().x_coord_, y_coord_ - segment.GetStart().y_coord_);
    Vector second(x_coord_ - segment.GetEnd().x_coord_, y_coord_ - segment.GetEnd().y_coord_);
    Vector seg_vect(segment.GetEnd().x_coord_ - segment.GetStart().x_coord_,
                    segment.GetEnd().y_coord_ - segment.GetStart().y_coord_);
    return ScalarMult(first, seg_vect) >= 0 && ScalarMult(second, seg_vect) <= 0 && VectorMult(first, seg_vect) == 0;
}

Point* Point::Clone() const {
    return new Point(x_coord_, y_coord_);
}

Vector Point::operator-(Point other) const {
    return Vector(GetX() - other.GetX(), GetY() - other.GetY());
}
}  // namespace geometry
