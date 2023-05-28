#include "circle.h"

#include "segment.h"
#include "vector.h"

namespace geometry {
Circle::Circle() {
    centre_ = Point(0, 0);
    radius_ = 0;
}

Circle::Circle(geometry::Point centre, int64_t radius) {
    centre_ = centre;
    radius_ = radius;
}

Circle &Circle::Move(const geometry::Vector &vector) {
    centre_.Move(vector);
    return *this;
}

bool Circle::ContainsPoint(const geometry::Point &point) const {
    Vector v = point - centre_;
    return v.GetX() * v.GetX() + v.GetY() * v.GetY() <= radius_ * radius_;
}

bool Circle::CrossesSegment(const geometry::Segment &segment) const {
    if (ContainsPoint(segment.GetStart()) && ContainsPoint(segment.GetEnd())) {
        return false;
    }
    if (!ContainsPoint(segment.GetStart()) && !ContainsPoint(segment.GetEnd())) {
        double d = segment.Distance(centre_);
        double rad = static_cast<double>(radius_);
        return d <= rad;
    }
    return true;
}

Circle *Circle::Clone() const {
    return new Circle(centre_, radius_);
}

int64_t Circle::GetRadius() const {
    return radius_;
}

Point Circle::GetCenter() const {
    return centre_;
}
}  // namespace geometry
