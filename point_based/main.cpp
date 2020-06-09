/*
File: main.cpp
*/

#include "Control.h"
//#include "operators.cpp"
//#include "Point.h"
//#include <set>
//#include <iostream>

int main(int argc, char* argv[]) {
    return Control::start();
    //std::cout << sizeof(Point) << std::endl;
    /*
    std::set<Point*, ptrComp> test;
    test.insert(new Point(0, 0));
    test.insert(new Point(0, 1));
    test.insert(new Point(0, 2));
    test.insert(new Point(1, 0));
    test.insert(new Point(1, 1));
    test.insert(new Point(0, 1));
    test.insert(new Point(24, 26));

    for (std::set<Point*, ptrComp>::iterator it = test.begin(); it != test.end(); ++it) {
        std::cout << "Found point: " << (*it)->toString() << std::endl;
    }
    */
}