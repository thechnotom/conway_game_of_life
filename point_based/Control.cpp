/*
File: Control.cpp
*/

#include "Control.h"

int Control::start () {
    GameBoard* gameBoard = new GameBoard();
    initGame(gameBoard);

    std::string garbage;
    while (gameBoard->getStep() < 100) {
        std::cout << "Step (Ctrl + C to quit): " << gameBoard->getStep() << std::endl;
        std::cout << gameBoard->getString() << std::endl;
        if (gameBoard->getStep() >= 2) { break; }
        std::cout << "=== GameBoard printed ===" << std::endl;
        std::getline(std::cin, garbage);
        std::cout << "Advancing" << std::endl;
        gameBoard->advance();
        std::cout << "Advanced" << std::endl;
    }
    delete gameBoard;
    return 0;
}

void Control::initGame (GameBoard* gameBoard) {
    //gameBoard->addInitPoint(2, 2);
    //gameBoard->addInitPoint(2, 3);
    //gameBoard->addInitPoint(3, 2);

    gameBoard->addInitPoint(2, 2);
    gameBoard->addInitPoint(2, 3);
    gameBoard->addInitPoint(2, 4);
    gameBoard->addInitPoint(3, 2);
    gameBoard->addInitPoint(3, 4);
    gameBoard->addInitPoint(4, 2);
    gameBoard->addInitPoint(4, 3);
    gameBoard->addInitPoint(4, 4);

    /*
    gameBoard->addInitPoint(25, 25);
    gameBoard->addInitPoint(25, 26);
    gameBoard->addInitPoint(25, 27);
    gameBoard->addInitPoint(26, 25);
    gameBoard->addInitPoint(26, 27);
    gameBoard->addInitPoint(27, 25);
    gameBoard->addInitPoint(27, 26);
    gameBoard->addInitPoint(27, 27);
    */
}