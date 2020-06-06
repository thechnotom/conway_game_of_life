#ifndef GRID_H
#define GRID_H

/*
File: Grid.h
Purpose: Provide tools to create, observe, and manage a grid
*/

#define DEBUG true
#define SET   1
#define CLEAR 0

#include <iostream>
#include <string>

class Grid {
    public:
        Grid ();
        Grid (int columns, int rows);
        ~Grid ();
        static void set (int** grid, int row, int col);
        static void clear (int** grid, int row, int col);
        static int get (int** grid, int row, int col);
        void set (int row, int col);
        void clear (int row, int col);
        int get (int row, int col);
        std::string getString ();
        int** getPointer ();
        int** createEmpty ();
        void replace (int** grid);

    protected:
        int** grid;
        int rows;
        int columns;
        void init (int columns, int rows);
        bool verifyPoint (int x, int y);
        void deleteGrid ();
};

#endif