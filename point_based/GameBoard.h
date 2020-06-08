#ifndef GAMEBOARD_H
#define GAMEBOARD_H

/*
File: GameBoard.h
Purpose: Manage the state of the game
*/

#include "Point.h"
#include "operators.cpp"

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
        std::set<Point*, ptrComp>* deadNeighbours;
        int numNeighbours (Point* point, bool trackDead);
        bool isAlive (Point* point);
        std::set<Point*, ptrComp>* nextGameBoard ();
        int step;
        void deallocateSet (std::set<Point*, ptrComp>* points);
};

#endif