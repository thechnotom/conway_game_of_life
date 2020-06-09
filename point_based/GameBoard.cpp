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
}

GameBoard::~GameBoard () {
    std::cout << "~GameBoard: destroying GameBoard" << std::endl;
    deallocateSet(alive, true);
}

int GameBoard::numNeighbours (Point* point) {
    int result = 0;
    Point* currNeighbour;
    for (int xOffset = -1; xOffset <= 1; ++xOffset) {
        for (int yOffset = -1; yOffset <= 1; ++yOffset) {
            if (xOffset == 0 && yOffset == 0) {
                continue;
            }
            currNeighbour = new Point(point->getX() + xOffset, point->getY() + yOffset);
            if (isAlive(currNeighbour)) {
                //std::cout << "numNeighbours: found living neighbour" << std::endl;
                result += 1;
            }
            std::cout << "numNeighbours: attempting to delete temp Point --- ";
            deletePoint(currNeighbour);
        }
    }
    //std::cout << "numNeighbours: living neighbours found: " << result << std::endl;
    return result;
}

void GameBoard::addNewNeighbours (Point* point, std::set<Point*, ptrComp>* points) {
    Point* currPoint;
    std::cout << "addNewNeighbours: adding new neighbours around Point " << point->toString() << std::endl;
    for (int xOffset = -1; xOffset <= 1; ++xOffset) {
        for (int yOffset = -1; yOffset <= 1; ++yOffset) {
            if (xOffset == 0 && yOffset == 0) {
                continue;
            }
            currPoint = new Point(point->getX() + xOffset, point->getY() + yOffset);
            // Resurrection
            if (!isAlive(currPoint) && numNeighbours(currPoint) == 3) {
                std::cout << "addNewNeighbours: adding new neighbour Point " << currPoint->toString() << std::endl;
                if (points->count(currPoint) == 0) {
                    currPoint->addUse();  // CHECK HERE TO SEE IF DUPLICATES ARE ALSO BEING COUTNED (or see if this happens elsewhere)
                }
                points->insert(currPoint);
            }
            else {
                std::cout << "addNewNeighbours: already alive or no revive, attempting to delete temp Point --- ";
                deletePoint(currPoint);
            }
        }
    }
}

bool GameBoard::isAlive (Point* point) {
    if (alive->count(point) == 1) {
        return true;
    }
    return false;
}

std::set<Point*, ptrComp>* GameBoard::nextGameBoard () {
    std::set<Point*, ptrComp>* next = new std::set<Point*, ptrComp>;
    //std::cout << "alive size (after allocating next): " << alive->size() << std::endl;
    int neighbours;
    for (std::set<Point*, ptrComp>::iterator it = alive->begin(); it != alive->end(); ++it) {
        // Count the number of living neighbours and populate GameBoard::deadNeighbours
        neighbours = numNeighbours(*it);
        if (isAlive(*it)) {
            // Survival
            if (neighbours == 2 || neighbours == 3) {
                (*it)->addUse();
                next->insert(*it);
            }

            // Death (underpopulation or overpopulation)
            else {
                //std::cout << "cell died, removing: " << (*it)->toString() << std::endl;
                (*it)->removeUse();
            }
        }

        // Add the neighbours of the current Point that will be resurrected
        std::cout << "nextGameBoard: beginning to add new neighbours for Point " << (*it)->toString() << std::endl;
        addNewNeighbours(*it, next);
        std::cout << "nextGameBoard: finished the addition of new neighbours for Point " << (*it)->toString() << std::endl;
    }

    std::cout << "nextGameBoard: alive size (end): " << alive->size() << std::endl;

    return next;
}

void GameBoard::advance () {
    std::set<Point*, ptrComp>* temp = alive;
    alive = nextGameBoard();
    std::cout << "advance: deallocating temp" << std::endl;
    deallocateSet(temp, true);
    std::cout << "advance: deallocated temp" << std::endl;
    //delete temp;
    ++step;
}

std::string GameBoard::getString () {
    return getString(0, 0, 10, 10);
}

std::string GameBoard::getString (int startX, int startY, int width, int height) {
    std::string result = "";
    Point* currPoint;
    for (int row = startX; row <= startX + width; ++ row) {
        for (int col = startY; col <= startY + height; ++ col) {
            currPoint = new Point(row, col);
            if (alive->count(currPoint) != 0) {
                result += "# ";
            }
            else {
                result += "- ";
            }
            std::cout << "getString: destroying Point --- ";
            deletePoint(currPoint);
        }
        result += "\n";
    }
    return result;
}

int GameBoard::getStep () { return step; }

void GameBoard::addInitPoint (int x, int y) {
    if (step == 0) {
        Point* newPoint = new Point(x, y);
        newPoint->addUse();
        alive->insert(newPoint);
    }
}

bool GameBoard::clearSet (std::set<Point*, ptrComp>* points) {
    return clearSet(points, false);
}

bool GameBoard::clearSet (std::set<Point*, ptrComp>* points, bool decrementUses) {
    bool cleanDelete = true;
    for (std::set<Point*, ptrComp>::iterator it = points->begin(); it != points->end(); ++it) {
        std::cout << "clearSet: attempting to delete Point " << (*it)->toString() << " --- ";
        cleanDelete = deletePoint(*it, decrementUses);
    }
    points->clear();
    if (!cleanDelete) { std::cout << "clearSet: UANBLE TO PREFORM A CLEAN DELETE" << std::endl; }
    return cleanDelete;
}

bool GameBoard::deallocateSet (std::set<Point*, ptrComp>* points) {
    return deallocateSet (points, false);
}

bool GameBoard::deallocateSet (std::set<Point*, ptrComp>* points, bool decrementUses) {
    bool cleanDelete;
    cleanDelete = clearSet(points, decrementUses);
    delete points;
    if (!cleanDelete) { std::cout << "deallocateSet: UANBLE TO PREFORM A CLEAN DELETE" << std::endl; }
    return cleanDelete;
}

bool GameBoard::deletePoint (Point* point) {
    return deletePoint(point, false);
}

bool GameBoard::deletePoint (Point* point, bool decrementUses) {
    if (decrementUses) { point->removeUse(); }
    if (point->getUses() == 0) {
        delete point;
        return true;
    }
    std::cout << "FAILED (remaining uses: " << point->getUses() << ")" << std::endl;
    return false;
}