#include "polygon.h"

#include "segment.h"

namespace geometry {
bool InTriangle(const Point &p, const Point &p1, const Point &p2, const Point &p3) {
    if (VectorMult(p2 - p1, p3 - p2) == 0) {
        return Segment(p1, p2).ContainsPoint(p) || Segment(p1, p3).ContainsPoint(p) || Segment(p2, p3).ContainsPoint(p);
    }
    int64_t mult1 = VectorMult(p2 - p1, p - p1);
    int64_t mult2 = VectorMult(p3 - p2, p - p2);
    int64_t mult3 = VectorMult(p1 - p3, p - p3);
    return (mult1 >= 0 && mult2 >= 0 && mult3 >= 0) || (mult1 <= 0 && mult2 <= 0 && mult3 <= 0);
}

void GetSegments(std::vector<Point> points, std::vector<Segment> &out_segments) {
    out_segments.resize(points.size());
    for (size_t i = 0; i < points.size() - 1; ++i) {
        out_segments[i] = Segment(points[i + 1], points[i]);
    }
    out_segments[points.size() - 1] = Segment(points[0], points[points.size() - 1]);
}

Polygon::Polygon() {
    points_ = std::vector<Point>(0);
    num_points_ = 0;
}

Polygon::Polygon(std::vector<Point> points) {
    points_ = std::vector<Point>(points);
    num_points_ = points.size();
}

Polygon &Polygon::Move(const geometry::Vector &vector) {
    for (size_t i = 0; i < num_points_; ++i) {
        points_[i].Move(vector);
    }
    return *this;
}

bool Polygon::ContainsPoint(const geometry::Point &point) const {
    if (num_points_ == 0) {
        return false;
    }
    if (num_points_ == 1) {
        return point.GetX() == points_[0].GetX() && point.GetY() == points_[0].GetY();
    }
    if (num_points_ == 2) {
        return Segment(points_[0], points_[1]).ContainsPoint(point);
    }
    for (size_t i = 1; i < num_points_ - 1; ++i) {
        if (InTriangle(point, points_[0], points_[i], points_[i + 1])) {
            return true;
        }
    }
    return false;
}

bool Polygon::CrossesSegment(const geometry::Segment &segment) const {
    if (num_points_ == 0) {
        return false;
    }
    if (num_points_ == 1) {
        return segment.ContainsPoint(points_[0]);
    }
    if (num_points_ == 2) {
        return segment.CrossesSegment(Segment(points_[0], points_[1]));
    }
    std::vector<Segment> segments(num_points_);
    GetSegments(points_, segments);
    for (const auto &curr_segment : segments) {
        if (curr_segment.CrossesSegment(segment)) {
            return true;
        }
    }
    return false;
}

Polygon *Polygon::Clone() const {
    return new Polygon(std::vector<Point>(points_));
}
}  // namespace geometry