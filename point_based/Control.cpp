/*
File: Control.cpp
*/

#include "Control.h"

int Control::start (std::string filename, int startX, int startY, int width, int height) {
    GameBoard* gameBoard = new GameBoard();
    initGame(gameBoard, filename);

    int maxSteps = 1000000;
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

void Control::initGame (GameBoard* gameBoard, std::string filename) {
    std::vector<Point*>* points = FileIO::getData(filename);
    for (unsigned i = 0; i < points->size(); ++i) {
        gameBoard->addInitPoint(points->at(i)->getX(), points->at(i)->getY());
        delete points->at(i);
    }
    delete points;
}