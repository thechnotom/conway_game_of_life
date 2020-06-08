/*
File: GameBoard.cpp
*/

#include "GameBoard.h"

GameBoard::GameBoard () {
    init();
}

void GameBoard::init () {
    step = 0;
    alive = new std::set<Point*, ptrComp>;
    deadNeighbours = new std::set<Point*, ptrComp>;
}

GameBoard::~GameBoard () {
    deallocateSet(alive);
    deallocateSet(deadNeighbours);
}

int GameBoard::numNeighbours (Point* point, bool trackDead) {
    int result = 0;
    Point* currNeighbour;
    for (int xOffset = -1; xOffset <= 1; ++xOffset) {
        for (int yOffset = -1; yOffset <= 1; ++yOffset) {
            currNeighbour = new Point(point->getX() + xOffset, point->getY() + yOffset);
            if (isAlive(currNeighbour) &&
                !(xOffset == 0 && yOffset == 0)) {
                std::cout << "numNeighbours: found living neighbour" << std::endl;
                result += 1;
                delete currNeighbour;
            }
            // Mark neighbours that need to be checked
            else {
                if (trackDead) {
                    std::cout << "numNeighbours: adding dead neighbour at Point " << currNeighbour->toString() << std::endl;
                    deadNeighbours->insert(currNeighbour);
                }
            }
        }
    }
    std::cout << "numNeighbours: living neighbours found: " << result << std::endl;
    return result;
}

bool GameBoard::isAlive (Point* point) {
    if (alive->count(point) == 1) {
        return true;
    }
    return false;
}

std::set<Point*, ptrComp>* GameBoard::nextGameBoard () {
    std::cout << "creating next GameBoard" << std::endl;
    std::cout << "nextGameBoard: alive size (start): " << alive->size() << std::endl;
    deadNeighbours->clear();
    std::cout << "alive size (after clearing deadNeighbours): " << alive->size() << std::endl;
    std::set<Point*, ptrComp>* next = new std::set<Point*, ptrComp>;
    std::cout << "alive size (after allocating next): " << alive->size() << std::endl;
    int neighbours;
    if (alive->begin() == alive->end()) {
        std::cout << "alive begin and end EQUAL, size: " << alive->size() << std::endl;
    }
    else {
        std::cout << "alive begin and end NOT EQUAL" << std::endl;
    }
    for (std::set<Point*, ptrComp>::iterator it = alive->begin(); it != alive->end(); ++it) {
        // Count the number of living neighbours and populate GameBoard::deadNeighbours
        neighbours = numNeighbours(*it, true);
        if (isAlive(*it)) {
            // Survival
            if (neighbours == 2 || neighbours == 3) {
                next->insert(*it);
            }

            // Death (underpopulation or overpopulation)
            else {
                std::cout << "cell died, removing: " << (*it)->toString() << std::endl;
                delete *it;
            }
        }
    }

    std::cout << "alive size: " << alive->size() << std::endl;
    std::cout << "completed alive cells -- testing deadNeighbours" << std::endl;
    for (std::set<Point*, ptrComp>::iterator it = deadNeighbours->begin(); it != deadNeighbours->end(); ++it) {
        std::cout << "dead neighbours: testing Point " << (*it)->toString() << std::endl;
        neighbours = numNeighbours(*it, false);
        if (neighbours == 3) {
            // Reproduction
            next->insert(*it);
        }
        else {
            delete *it;
        }
    }

    std::cout << "completed dead neighbours" << std::endl;
    std::cout << "nextGameBoard: alive size (end): " << alive->size() << std::endl;

    return next;
}

void GameBoard::advance () {
    std::set<Point*, ptrComp>* temp = alive;
    alive = nextGameBoard();
    delete temp;
    ++step;
}

std::string GameBoard::getString () {
    return getString(0, 0, 50, 50);
}

std::string GameBoard::getString (int startX, int startY, int width, int height) {
    std::string result = "";
    Point currPoint;
    for (int row = startX; row <= startX + width; ++ row) {
        for (int col = startY; col <= startY + height; ++ col) {
            currPoint = Point(row, col);
            if (alive->count(&currPoint) != 0) {
                result += "# ";
            }
            else {
                result += "- ";
            }
        }
        result += "\n";
    }
    return result;
}

int GameBoard::getStep () { return step; }

void GameBoard::addInitPoint (int x, int y) {
    if (step == 0) {
        alive->insert(new Point(x, y));
    }
}

void GameBoard::deallocateSet (std::set<Point*, ptrComp>* points) {
    for (std::set<Point*, ptrComp>::iterator it = points->begin(); it != points->end(); ++it) {
        delete *it;
    }
    delete points;
}