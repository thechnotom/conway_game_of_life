/*
File: Control.cpp
*/

#include "Control.h"

int Control::start (int startX, int startY, int width, int height) {
    GameBoard* gameBoard = new GameBoard();
    initGame(gameBoard);

    int maxSteps = 100;
    std::string input;
    std::cout << gameBoard->getString(startX, startY, width, height) << std::endl;
    while (gameBoard->getStep() <= maxSteps) {
        std::cout << "Step (Enter \"q\" to quit): " << gameBoard->getStep() << " / " << maxSteps << std::endl;
        std::cout << "Continue: ";
        std::getline(std::cin, input);
        if (input == "q") { break; }
        std::cout << "Advancing" << std::endl;
        gameBoard->advance();
        std::cout << "Advanced" << std::endl;
        std::cout << gameBoard->getString(startX, startY, width, height) << std::endl;
        std::cout << "=== GameBoard printed ===" << std::endl;
    }
    delete gameBoard;
    return 0;
}

void Control::initGame (GameBoard* gameBoard) {
    /*
    gameBoard->addInitPoint(2, 2);
    gameBoard->addInitPoint(2, 3);
    gameBoard->addInitPoint(3, 2);
    gameBoard->addInitPoint(3, 3);
    */

    /*
    gameBoard->addInitPoint(2, 2);
    gameBoard->addInitPoint(2, 3);
    gameBoard->addInitPoint(2, 4);
    gameBoard->addInitPoint(3, 2);
    gameBoard->addInitPoint(3, 4);
    gameBoard->addInitPoint(4, 2);
    gameBoard->addInitPoint(4, 3);
    gameBoard->addInitPoint(4, 4);
    */

    gameBoard->addInitPoint(9, 9);
    gameBoard->addInitPoint(9, 10);
    gameBoard->addInitPoint(9, 11);
    gameBoard->addInitPoint(10, 9);
    gameBoard->addInitPoint(10, 11);
    gameBoard->addInitPoint(11, 9);
    gameBoard->addInitPoint(11, 10);
    gameBoard->addInitPoint(11, 11);

    gameBoard->addInitPoint(10, 9);
    gameBoard->addInitPoint(10, 11);
    gameBoard->addInitPoint(11, 9);

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