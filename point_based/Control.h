#ifndef CONTROL_H
#define CONTROL_H

/*
File: Control.h
Purpose: Manage the progress of the game
*/

#include "GameBoard.h"
#include "FileIO.h"

#include <iostream>

class Control {
    public:
        static int start (std::string filename, int startX, int startY, int width, int height);

    private:
        Control ();
        static void initGame (GameBoard* gameBoard, std::string filename);
};

#endif