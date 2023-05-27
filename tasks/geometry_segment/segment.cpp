#include "segment.h"

#include "line.h"

namespace geometry {
bool lines_are_equal(Line a, Line b) {
    if (a.GetC() < b.GetC()) {
        std::swap(a, b);
    }
    // now a.GetC() >= b.GetC();
    if (a.GetC() % b.GetC() != 0) {
        return false;
    }
    int64_t d = a.GetC() / b.GetC();
    return a.GetA() == b.GetA() * d && a.GetB() == b.GetB() * d;
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
        if (Segment(start_, point).Degenerate()) {
            return true;
        } else {
            return false;
        }
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
    if (lines_are_equal(line_this, line_that)) {
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
