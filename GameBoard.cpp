/*
File: GameBaord.cpp
*/

#include "GameBoard.h"

GameBoard::GameBoard () :
    Grid{} {
}

GameBoard::GameBoard (int columns, int rows) :
    Grid{columns, rows} {
}

std::string GameBoard::getString (char dead, char alive) {
    std::string result = "";
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            if (isAlive(row, col)) { result += alive; }
            else { result += dead; }
            if (col != columns - 1) { result += " "; }
        }
        if (row != rows - 1) { result += "\n"; }
    }
    return result;
}

std::string GameBoard::getString () {
    return GameBoard::getString('-', '#');
}

bool GameBoard::isAlive (int row, int col) {
    if (!verifyPoint(row, col)) { return false; }
    if (get(row, col) > 0) { return true; }
    else { return false; }
}

int GameBoard::numNeighbours (int row, int col) {
    int result = 0;
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
        for (int colOffset = -1; colOffset <= 1; ++colOffset) {
            if (isAlive(row + rowOffset, col + colOffset) && !(rowOffset == 0 && colOffset == 0)) { result += 1; }
        }
    }
    return result;
}

int** GameBoard::nextGameBoard () {
    int** next = createEmpty();
    int neighbours;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            neighbours = numNeighbours(row, col);
            if (isAlive(row, col)) {
                // Survival
                if (neighbours == 2 || neighbours == 3) {
                    set(next, row, col);
                }

                // Death (underpopulation or overpopulation)
                else {
                    clear(next, row, col);
                }
            }
            else {
                // Reproduction
                if (neighbours == 2 || neighbours == 3) {
                    set(next, row, col);
                }
            }
        }
    }
    return next;
}

void GameBoard::advance () {
    replace(nextGameBoard());
}