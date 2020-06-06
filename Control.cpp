/*
File: Control.cpp
*/

#include "Control.h"

int Control::start () {
    GameBoard* gameBoard = new GameBoard(51, 51);
    initGame(gameBoard);

    int step = 0;
    std::string garbage;
    while (step < 100) {
        std::cout << "Step: " << step << std::endl;
        std::cout << gameBoard->getString() << std::endl;
        std::getline(std::cin, garbage);
        gameBoard->advance();
        ++step;
    }
    delete gameBoard;
    return 0;
}

void Control::initGame (GameBoard* gameBoard) {
    gameBoard->set(25, 25);
    gameBoard->set(25, 26);
    gameBoard->set(25, 27);
    gameBoard->set(26, 25);
    gameBoard->set(26, 27);
    gameBoard->set(27, 25);
    gameBoard->set(27, 26);
    gameBoard->set(27, 27);
}