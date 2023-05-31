#include "segment.h"

#include <algorithm>
#include <numeric>

#include "line.h"

namespace geometry {
bool LinesAreEqual(Line a, Line b) {
    int64_t a_gcd = std::gcd(a.GetA(), std::gcd(a.GetB(), a.GetC()));
    int64_t b_gcd = std::gcd(b.GetA(), std::gcd(b.GetB(), b.GetC()));
    int64_t a_a = a.GetA() / a_gcd;
    int64_t a_b = a.GetB() / a_gcd;
    int64_t a_c = a.GetC() / a_gcd;
    int64_t b_a = b.GetA() / b_gcd;
    int64_t b_b = b.GetB() / b_gcd;
    int64_t b_c = b.GetC() / b_gcd;
    return (a_a == b_a && a_b == b_b && a_c == b_c) || (a_a == -b_a && a_b == -b_b && a_c == -b_c);
}

Segment::Segment() {
    start_ = Point(0, 0);
    end_ = Point(0, 0);
}

Segment::Segment(Point start, Point end) {
    start_ = start;
    end_ = end;
}

Point Segment::GetStart() const {
    return start_;
}

Point Segment::GetEnd() const {
    return end_;
}

double Segment::Distance(Point p) const {
    double d_points = std::min(Length(start_ - p), Length(end_ - p));
    double d_line = Line(start_, end_).Distance(p);
    return std::max(d_points, d_line);
}

bool Segment::Degenerate() const {
    return start_.GetX() == end_.GetX() && start_.GetY() == end_.GetY();
}

Segment& Segment::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool Segment::ContainsPoint(const Point& point) const {
    if (Degenerate()) {
        return (Segment(start_, point).Degenerate();
    }
    return point.CrossesSegment(*this);
}

bool Segment::CrossesSegment(const Segment& segment) const {
    if (Degenerate()) {
        return segment.ContainsPoint(start_);
    }
    if (segment.Degenerate()) {
        return ContainsPoint(segment.start_);
    }
    Line line_this = Line(start_, end_);
    Line line_that = Line(segment.start_, segment.end_);
    if (LinesAreEqual(line_this, line_that)) {
        return ContainsPoint(segment.GetStart()) || ContainsPoint(segment.GetEnd()) ||
               segment.ContainsPoint(GetStart()) || segment.ContainsPoint(GetEnd());
    }
    return (Line(start_, end_).CrossesSegment(segment) &&
            Line(segment.GetStart(), segment.GetEnd()).CrossesSegment(*this));
}

Segment* Segment::Clone() const {
    return new Segment(start_, end_);
}
}  // namespace geometry
