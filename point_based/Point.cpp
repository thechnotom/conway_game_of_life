/*
File: Point.cpp
*/

#include "Point.h"

/*
bool Point::operator() (const Point* point) {
    return hash() < point->hash();
}
*/

bool Point::operator== (const Point& point) const {
    return x == point.getX() && y == point.getY();
}

bool Point::operator< (const Point& point) const {
    return hash() < point.hash();
}

bool Point::operator> (const Point& point) const {
    return hash() > point.hash();
}

Point::Point () {
    init(0, 0);
}

Point::Point (int x, int y) {
    init(x, y);
}

Point::Point (const Point& point) {
    x = point.x;
    y = point.y;
}

void Point::init (int x, int y) {
    if (y >= (X_MULTIPLIER / 10)) {
        Point::x = 0;
        Point::y = 0;
    }
    Point::x = x;
    Point::y = y;
}

int Point::getX () const { return x; }
int Point::getY () const { return y; }

int Point::hash () const { return (X_MULTIPLIER * x) + y; }

std::string Point::toString () const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

Point Point::copy () {
    return Point(x, y);
}