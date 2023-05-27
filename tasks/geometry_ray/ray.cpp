#include "ray.h"

#include "line.h"
#include "segment.h"
#include "vector.h"

namespace geometry {
Ray::Ray() {
    start_ = Point(0, 0);
    end_ = Point(0, 0);
}

Ray::Ray(geometry::Point first, geometry::Point second) {
    start_ = first;
    end_ = second;
}

Ray &Ray::Move(const geometry::Vector &vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool Ray::ContainsPoint(const geometry::Point &point) const {
    Vector to_point = Vector(point - start_);
    return Line(start_, end_).ContainsPoint(point) && ScalarMult(to_point, end_ - start_) >= 0;
}

bool Ray::CrossesSegment(const geometry::Segment &segment) const {
    if (segment.Degenerate()) {
        return ContainsPoint(segment.GetStart());
    }
    Vector first_vector = start_ - segment.GetStart();
    Vector second_vector = segment.GetEnd() - start_;
    Vector ray_vector = end_ - start_;
    Line line = Line(start_, end_);
    if (line.ContainsPoint(segment.GetStart())) {
        if (line.ContainsPoint(segment.GetEnd())) {
            return ScalarMult(first_vector, ray_vector) <= 0 || ScalarMult(second_vector, ray_vector) >= 0;
        } else {
            return ContainsPoint(segment.GetStart());
        }
    } else {
        if (line.ContainsPoint(segment.GetEnd())) {
            return ContainsPoint(segment.GetEnd());
        } else {
            return Line(start_, end_).CrossesSegment(segment) &&
                   VectorMult(first_vector, second_vector) * VectorMult(first_vector, ray_vector) >= 0;
        }
    }
}

Ray *Ray::Clone() const {
    return new Ray(start_, end_);
}

Point Ray::GetStart() const {
    return start_;
}

Point Ray::GetEnd() const {
    return end_;
}
}  // namespace geometry