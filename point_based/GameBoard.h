#ifndef GAMEBOARD_H
#define GAMEBOARD_H

/*
File: GameBoard.h
Purpose: Manage the state of the game
*/

#include "Point.h"
#include "operators.cpp"
#include "constants.h"

#include <iostream>
#include <string>
#include <vector>
#include <set>

class GameBoard {
    public:
        GameBoard ();
        ~GameBoard ();
        void advance ();
        std::string getString ();
        std::string getString (int startX, int startY, int width, int height);
        int getStep ();
        void addInitPoint (int x, int y);

    private:
        void init ();
        std::set<Point*, ptrComp>* alive;
        int numNeighbours (Point* point);
        void addNewNeighbours (Point* point, std::set<Point*, ptrComp>* points);
        bool isAlive (Point* point);
        std::set<Point*, ptrComp>* nextGameBoard ();
        int step;
        bool deallocateSet (std::set<Point*, ptrComp>* points);
        bool deallocateSet (std::set<Point*, ptrComp>* points, bool decrementUses);
        bool clearSet (std::set<Point*, ptrComp>* points);
        bool clearSet (std::set<Point*, ptrComp>* points, bool decrementUses);
        bool deletePoint (Point* point);
        bool deletePoint (Point* point, bool decrementUses);
        bool addPoint (Point* point, std::set<Point*, ptrComp>* points);
};

#endif