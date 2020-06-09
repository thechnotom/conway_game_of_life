/*
File: Point.cpp
*/

#include "Point.h"

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
    if (SHOW_DEBUG_MESSAGES) { std::cout << "Point (copy): copying Point" << this->toString() << std::endl; }
    x = point.x;
    y = point.y;
}

Point::~Point () {
    if (SHOW_DEBUG_MESSAGES) { std::cout << "~Point: destroying Point " << toString() << std::endl; }
}

void Point::init (int x, int y) {
    instances = 0;
    if (abs(y) >= (POINT_HASH_MODIFIER / 10)) {
        if (SHOW_CRITICAL_MESSAGES) { std::cout << "Point: WARNING - abs(y) exceeds maximum permitted value" << std::endl; }
        Point::x = 0;
        Point::y = 0;
    }
    Point::x = x;
    Point::y = y;
}

int Point::getX () const { return x; }
int Point::getY () const { return y; }

int Point::hash () const {
    if (x != 0) {
        return (POINT_HASH_MODIFIER * x) + y;
    }
    return POINT_HASH_MODIFIER + y;
}

std::string Point::toString () const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

Point Point::copy () {
    return Point(x, y);
}

void Point::addUse () { ++instances; }
void Point::removeUse () { if (instances > 0) { --instances; } }
int Point::getUses () { return instances; }
void Point::resetUses () { instances = 0; }