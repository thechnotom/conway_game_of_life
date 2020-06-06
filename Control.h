#ifndef CONTROL_H
#define CONTROL_H

/*
File: Control.h
Purpose: Manage the progress of the game board
*/

#include "GameBoard.h"

#include <iostream>

class Control {
    public:
        static int start ();
    
    private:
        Control ();
        static void initGame (GameBoard* gameBoard);
};

#endif