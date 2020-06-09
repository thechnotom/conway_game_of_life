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
    if (SHOW_DEBUG_MESSAGES) { std::cout << "~GameBoard: destroying GameBoard" << std::endl; }
    if (!deallocateSet(alive, true)) {
        if (SHOW_CRITICAL_MESSAGES) { std::cout << "~GameBoard: UNABLE TO PERFORM A CLEAN DEALLOCATION" << std::endl; }
    }
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
                result += 1;
            }
            if (SHOW_DEBUG_MESSAGES) { std::cout << "numNeighbours: attempting to delete temp Point --- "; }
            deletePoint(currNeighbour, true);
        }
    }
    return result;
}

void GameBoard::addNewNeighbours (Point* point, std::set<Point*, ptrComp>* points) {
    Point* currPoint;
    if (SHOW_DEBUG_MESSAGES) { std::cout << "addNewNeighbours: adding new neighbours around Point " << point->toString() << std::endl; }
    for (int xOffset = -1; xOffset <= 1; ++xOffset) {
        for (int yOffset = -1; yOffset <= 1; ++yOffset) {
            if (xOffset == 0 && yOffset == 0) {
                continue;
            }
            currPoint = new Point(point->getX() + xOffset, point->getY() + yOffset);
            // Resurrection
            if (!isAlive(currPoint) && numNeighbours(currPoint) == 3) {
                if (SHOW_DEBUG_MESSAGES) { std::cout << "addNewNeighbours: adding new neighbour Point " << currPoint->toString() << std::endl; }
                addPoint(currPoint, points);
            }
            else {
                if (SHOW_DEBUG_MESSAGES) { std::cout << "addNewNeighbours: already alive or no revive, attempting to delete temp Point --- "; }
                deletePoint(currPoint, true);
            }
        }
    }
}

bool GameBoard::isAlive (Point* point) {
    if (alive->count(point) != 0) {
        return true;
    }
    return false;
}

std::set<Point*, ptrComp>* GameBoard::nextGameBoard () {
    std::set<Point*, ptrComp>* next = new std::set<Point*, ptrComp>;
    int neighbours;
    for (std::set<Point*, ptrComp>::iterator it = alive->begin(); it != alive->end(); ++it) {
        // Count the number of living neighbours and populate GameBoard::deadNeighbours
        neighbours = numNeighbours(*it);
        if (isAlive(*it)) {
            // Survival
            if (neighbours == 2 || neighbours == 3) {
                addPoint(*it, next);
            }

            // Death (underpopulation or overpopulation)
            else {
                (*it)->removeUse();
            }
        }

        // Add the neighbours of the current Point that will be resurrected
        if (SHOW_DEBUG_MESSAGES) { std::cout << "nextGameBoard: beginning to add new neighbours for Point " << (*it)->toString() << std::endl; }
        addNewNeighbours(*it, next);
        if (SHOW_DEBUG_MESSAGES) { std::cout << "nextGameBoard: finished the addition of new neighbours for Point " << (*it)->toString() << std::endl; }
    }

    if (SHOW_DEBUG_MESSAGES) { std::cout << "nextGameBoard: alive size (end): " << alive->size() << std::endl; }

    return next;
}

void GameBoard::advance () {
    std::set<Point*, ptrComp>* temp = alive;
    alive = nextGameBoard();
    if (SHOW_DEBUG_MESSAGES) { std::cout << "advance: deallocating temp" << std::endl; }
    deallocateSet(temp, true);
    if (SHOW_DEBUG_MESSAGES) { std::cout << "advance: deallocated temp" << std::endl; }
    //delete temp;
    ++step;
}

std::string GameBoard::getString () {
    return getString(0, 0, 10, 10);
}

std::string GameBoard::getString (int startX, int startY, int width, int height) {
    std::string result = "";
    Point* currPoint;
    for (int row = startX; row <= startX + height; ++ row) {
        for (int col = startY; col <= startY + width; ++ col) {
            currPoint = new Point(row, col);
            if (alive->count(currPoint) != 0) {
                result += "#";
            }
            else {
                result += "-";
            }
            if (col < startY + width) { result += " "; }
            if (SHOW_DEBUG_MESSAGES) { std::cout << "getString: destroying Point --- "; }
            deletePoint(currPoint, true);
        }
        if (row < startX + height) { result += "\n"; }
    }
    return result;
}

int GameBoard::getStep () { return step; }

void GameBoard::addInitPoint (int x, int y) {
    if (step == 0) {
        Point* newPoint = new Point(x, y);
        addPoint(newPoint, alive);
    }
}

bool GameBoard::clearSet (std::set<Point*, ptrComp>* points) {
    return clearSet(points, false);
}

bool GameBoard::clearSet (std::set<Point*, ptrComp>* points, bool decrementUses) {
    bool cleanDelete = true;
    for (std::set<Point*, ptrComp>::iterator it = points->begin(); it != points->end(); ++it) {
        if (SHOW_DEBUG_MESSAGES) { std::cout << "clearSet: attempting to delete Point " << (*it)->toString() << " --- "; }
        cleanDelete = deletePoint(*it, decrementUses);
    }
    points->clear();
    if (SHOW_DEBUG_MESSAGES) { if (!cleanDelete) { std::cout << "clearSet: UANBLE TO PREFORM A CLEAN DELETE" << std::endl; } }
    return cleanDelete;
}

bool GameBoard::deallocateSet (std::set<Point*, ptrComp>* points) {
    return deallocateSet (points, false);
}

bool GameBoard::deallocateSet (std::set<Point*, ptrComp>* points, bool decrementUses) {
    bool cleanDelete;
    if (SHOW_DEBUG_MESSAGES) {
        for (std::set<Point*, ptrComp>::iterator it = points->begin(); it != points->end(); ++it) {
            std::cout << "--- deallocateSet: BEFORE clear - elements: " << (*it)->toString() << " - uses: " << (*it)->getUses() << std::endl;
        }
    }
    cleanDelete = clearSet(points, decrementUses);
    if (SHOW_DEBUG_MESSAGES) {
        for (std::set<Point*, ptrComp>::iterator it = points->begin(); it != points->end(); ++it) {
            std::cout << "--- deallocateSet: AFTER clear - elements: " << (*it)->toString() << " - uses: " << (*it)->getUses() << std::endl;
        }
    }
    delete points;
    if (SHOW_DEBUG_MESSAGES) { if (!cleanDelete) { std::cout << "deallocateSet: UANBLE TO PREFORM A CLEAN DELETE" << std::endl; } }
    return cleanDelete;
}

bool GameBoard::deletePoint (Point* point) {
    return deletePoint(point, false);
}

bool GameBoard::deletePoint (Point* point, bool decrementUses) {
    if (decrementUses) { point->removeUse(); }
    if (point->getUses() <= 0) {
        delete point;
        return true;
    }
    if (SHOW_DEBUG_MESSAGES) { std::cout << "FAILED (remaining uses: " << point->getUses() << ")" << std::endl; }
    return false;
}

bool GameBoard::addPoint (Point* point, std::set<Point*, ptrComp>* points) {
    // If the element is added to points for the first time
    if (points->count(point) == 0) {
        point->addUse();
        points->insert(point);
        return true;
    }
    if (SHOW_DEBUG_MESSAGES) { std::cout << "addPoint: UNABLE TO ADD POINT (deleting)" << std::endl; }
    deletePoint(point, true);
    return false;
}