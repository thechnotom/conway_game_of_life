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
    std::cout << "~GameBoard: destroying GameBoard" << std::endl;
    deallocateSet(alive, true);
    deallocateSet(deadNeighbours, true);
}

int GameBoard::numNeighbours (Point* point, bool trackDead) {
    int result = 0;
    Point* currNeighbour;
    for (int xOffset = -1; xOffset <= 1; ++xOffset) {
        for (int yOffset = -1; yOffset <= 1; ++yOffset) {
            if (xOffset == 0 && yOffset == 0) {
                std::cout << "numNeighbours: origin cell, doing nothing" << std::endl;
                continue;
            }
            currNeighbour = new Point(point->getX() + xOffset, point->getY() + yOffset);
            if (isAlive(currNeighbour)) {
                //std::cout << "numNeighbours: found living neighbour" << std::endl;
                result += 1;
                std::cout << "numNeighbours: living cell, attempting to delete temp Point --- ";
                deletePoint(currNeighbour);
            }
            // Mark neighbours that need to be checked
            else {
                if (trackDead) {
                    std::cout << "numNeighbours: adding dead neighbour at Point " << currNeighbour->toString() << std::endl;
                    currNeighbour->addUse();
                    deadNeighbours->insert(currNeighbour);
                }
                else {
                    std::cout << "numNeighbours: dead cell, no tracking, attempting to delete temp Point --- ";
                    deletePoint(currNeighbour);
                }
            }
        }
    }
    //std::cout << "numNeighbours: living neighbours found: " << result << std::endl;
    return result;
}

bool GameBoard::isAlive (Point* point) {
    if (alive->count(point) == 1) {
        return true;
    }
    return false;
}

std::set<Point*, ptrComp>* GameBoard::nextGameBoard () {
    //std::cout << "creating next GameBoard" << std::endl;
    //std::cout << "nextGameBoard: alive size (start): " << alive->size() << std::endl;
    std::cout << "clearing deadNeighbours (b)" << std::endl;
    clearSet(deadNeighbours, true);
    std::cout << "cleared deadNeighbours (b)" << std::endl;
    //std::cout << "alive size (after clearing deadNeighbours): " << alive->size() << std::endl;
    std::set<Point*, ptrComp>* next = new std::set<Point*, ptrComp>;
    std::set<Point*, ptrComp>* pergatory = new std::set<Point*, ptrComp>;
    //std::cout << "alive size (after allocating next): " << alive->size() << std::endl;
    int neighbours;
    for (std::set<Point*, ptrComp>::iterator it = alive->begin(); it != alive->end(); ++it) {
        // Count the number of living neighbours and populate GameBoard::deadNeighbours
        neighbours = numNeighbours(*it, true);
        if (isAlive(*it)) {
            // Survival
            if (neighbours == 2 || neighbours == 3) {
                // Do not add to Point use as it is only being re-added to the next game
                next->insert(*it);
            }

            // Death (underpopulation or overpopulation)
            else {
                //std::cout << "cell died, removing: " << (*it)->toString() << std::endl;
                pergatory->insert(*it);
            }
        }
    }

    //std::cout << "alive size: " << alive->size() << std::endl;
    std::cout << "completed alive cells -- testing deadNeighbours" << std::endl;
    for (std::set<Point*, ptrComp>::iterator it = deadNeighbours->begin(); it != deadNeighbours->end(); ++it) {
        std::cout << "dead neighbours: testing Point " << (*it)->toString() << std::endl;
        neighbours = numNeighbours(*it, false);
        //(*it)->addUse();
        if (neighbours == 3) {
            // Reproduction
            (*it)->addUse();
            next->insert(*it);
        }
        else {
            pergatory->insert(*it);
        }
    }

    std::cout << "deallocating pergatory" << std::endl;
    deallocateSet(pergatory, false);
    std::cout << "deallocated pergatory" << std::endl;
    std::cout << "clearing deadNeighbours (e)" << std::endl;
    clearSet(deadNeighbours, true);
    std::cout << "cleared deadNeighbours (e)" << std::endl;

    std::cout << "completed dead neighbours" << std::endl;
    std::cout << "nextGameBoard: alive size (end): " << alive->size() << std::endl;

    return next;
}

void GameBoard::advance () {
    std::set<Point*, ptrComp>* temp = alive;
    alive = nextGameBoard();
    std::cout << "advance: deallocating temp" << std::endl;
    deallocateSet(temp, false);
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