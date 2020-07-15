/*
File: Point.cpp
*/

#include "Point.h"

// Operator overloading (important for ordering)
bool Point::operator== (const Point& point) const {
    return x == point.getX() && y == point.getY();
}

bool Point::operator< (const Point& point) const {
    return hash() < point.hash();
}

bool Point::operator> (const Point& point) const {
    return hash() > point.hash();
}

/* Function: Point
 * Purpose: default constructor
 * Arguments:
 *     none
 * Return
 *     none
 */
Point::Point () {
    init(0, 0);
}

/* Function: Point
 * Purpose: constructor which sets x and y variables
 * Arguments:
 *     x (int): x coordinate
 *     y (int): y coordinate
 * Return
 *     none
 */
Point::Point (int x, int y) {
    init(x, y);
}

/* Function: Point
 * Purpose: copy constructor
 * Arguments:
 *     none
 * Return
 *     none
 */
Point::Point (const Point& point) {
    if (SHOW_DEBUG_MESSAGES) { std::cout << "Point (copy): copying Point" << this->toString() << std::endl; }
    x = point.x;
    y = point.y;
}

/* Function: ~Point
 * Purpose: destructor
 * Arguments:
 *     none
 * Return
 *     none
 */
Point::~Point () {
    if (SHOW_DEBUG_MESSAGES) { std::cout << "~Point: destroying Point " << toString() << std::endl; }
}

/* Function: init
 * Purpose: initializes coordinates
 * Arguments:
 *     x (int): x coordinate
 *     y (int): y coordinate
 * Return
 *     (void)
 */
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

// Getters
int Point::getX () const { return x; }
int Point::getY () const { return y; }

/* Function: hash
 * Purpose: get a unique numeric value for a point
 * Arguments:
 *     none
 * Return
 *     (int) unique numeric value
 */
int Point::hash () const {
    return (POINT_HASH_MODIFIER * x) + y;
}

/* Function: toString
 * Purpose: provide a string representation of the Point
 * Arguments:
 *     none
 * Return
 *     (string) string representation of the Point
 */
std::string Point::toString () const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

/* Function: copy
 * Purpose: create a new Point object
 * Arguments:
 *     none
 * Return
 *     (Point) copy of the current Point
 */
Point Point::copy () {
    return Point(x, y);
}

// Functions to manage the number if instances of the Point
void Point::addUse () { ++instances; }
void Point::removeUse () { if (instances > 0) { --instances; } }
int Point::getUses () { return instances; }
void Point::resetUses () { instances = 0; }