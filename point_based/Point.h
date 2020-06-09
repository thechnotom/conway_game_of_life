#ifndef POINT_H
#define POINT_H

/*
File: Point.h
Purpose: Store information for a point on a 2-dimensional plane
*/

#include <iostream>
#include <string>

#define X_MULTIPLIER 1000000
//#define X_MULTIPLIER 1000

class Point {
    public:
        Point ();
        Point (int x, int y);
        Point (const Point& point);
        ~Point ();
        int getX () const;
        int getY () const;
        int hash () const;
        bool operator== (const Point& point) const;
        bool operator< (const Point& point) const;
        bool operator> (const Point& point) const;
        std::string toString () const;
        Point copy ();
        //bool operator() (const Point* point);
        void addUse ();
        void removeUse ();
        int getUses ();

    private:
        int x;
        int y;
        int instances;
        void init (int x, int y);
};

#endif