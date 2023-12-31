#include "line.h"

#include "math.h"

namespace geometry {
Line::Line() {
    start_ = Point(0, 0);
    end_ = Point(0, 0);
}
int64_t Line::GetA() const {
    return end_.GetY() - start_.GetY();
}

int64_t Line::GetB() const {
    return start_.GetX() - end_.GetX();
}
int64_t Line::GetC() const {
    return -(GetA() * start_.GetX() + GetB() * start_.GetY());
}
Line::Line(Point start, Point end) {
    start_ = start;
    end_ = end;
}
double Line::Distance(Point point) const {
    int64_t a = GetA();
    int64_t b = GetB();
    int64_t c = GetC();
    int64_t d = a * point.GetX() + b * point.GetY() + c;
    return d > 0 ? static_cast<double>(d) / std::sqrt(a * a + b * b)
                 : static_cast<double>(-d) / std::sqrt(a * a + b * b);
}
Line& Line::Move(const Vector& vector) {
    start_ = start_.Move(vector);
    end_ = end_.Move(vector);
    return *this;
}
bool Line::ContainsPoint(const Point& point) const {
    int64_t a = GetA();
    int64_t b = GetB();
    int64_t c = GetC();
    return a * point.GetX() + b * point.GetY() + c == 0;
}
bool Line::CrossesSegment(const Segment& segment) const {
    return (GetA() * segment.GetStart().GetX() + GetB() * segment.GetStart().GetY() + GetC()) *
               (GetA() * segment.GetEnd().GetX() + GetB() * segment.GetEnd().GetY() + GetC()) <=
           0;
}
Line* Line::Clone() const {
    return new Line(start_, end_);
}
}  // namespace geometry
