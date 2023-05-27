#include "polygon.h"

#include "segment.h"

namespace geometry {
void GetVectors(std::vector<Point> points, std::vector<Vector> &out_vectors) {
    out_vectors.resize(points.size());
    for (size_t i = 0; i < points.size() - 1; ++i) {
        out_vectors[i] = points[i + 1] - points[i];
    }
    out_vectors[points.size() - 1] = points[0] - points[points.size() - 1];
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
    std::vector<Vector> vectors(num_points_);
    GetVectors(points_, vectors);
    bool is_positive = ScalarMult(vectors[num_points_ - 1], vectors[0]) >= 0;
    for (size_t i = 0; i < num_points_ - 1; ++i) {
        if ((ScalarMult(vectors[i + 1], vectors[i]) >= 0) != is_positive) {
            return false;
        }
    }
    return true;
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