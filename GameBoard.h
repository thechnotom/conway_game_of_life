#ifndef GAMEBOARD_H
#define GAMEBOARD_H

/*
File: GameBoard.h
Purpose: Provide tools to create, observe, and manage a grid in the context of Conway's Game of Life
*/

#include "Grid.h"

#include <iostream>
#include <string>

class GameBoard : public Grid {
    public:
        GameBoard();
        GameBoard(int columns, int rows);
        std::string getString (char dead, char alive);
        std::string getString ();
        bool isAlive (int row, int col);
        int numNeighbours (int row, int col);
        void advance ();

    private:
        int** nextGameBoard ();
};

#endif