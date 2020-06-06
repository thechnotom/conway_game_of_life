/*
File: Grid.cpp
*/

#include "Grid.h"

Grid::Grid () {
    init(10, 10);
}

Grid::Grid (int columns, int rows) {
    init(columns, rows);
}

Grid::~Grid () {
    deleteGrid();
}

void Grid::init (int columns, int rows) {
    Grid::rows = rows;
    Grid::columns = columns;
    grid = createEmpty();
}

void Grid::set (int row, int col) {
    if (!verifyPoint(row, col)) {
        if (DEBUG) { std::cout << "failed to set" << std::endl; }
        return;
    }
    set(grid, row, col);
}

void Grid::clear (int row, int col) {
    if (!verifyPoint(row, col)) {
        if (DEBUG) { std::cout << "failed to clear" << std::endl; }
        return;
    }
    clear(grid, row, col);
}

int Grid::get (int row, int col) {
    if (!verifyPoint(row, col)) {
        if (DEBUG) { std::cout << "failed to get" << std::endl; }
        return -1;
    }
    return get(grid, row, col);
}

void Grid::set (int** grid, int row, int col) {
    grid[row][col] = SET;
}

void Grid::clear (int** grid, int row, int col) {
    grid[row][col] = CLEAR;
}

int Grid::get (int** grid, int row, int col) {
    return grid[row][col];
}

bool Grid::verifyPoint (int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= columns) { return false; }
    return true;
}

std::string Grid::getString () {
    std::string result = "";
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            result += std::to_string(get(row, col));
            if (col != columns - 1) { result += " "; }
        }
        if (row != rows - 1) { result += "\n"; }
    }
    return result;
}

int** Grid::createEmpty () {
    int** grid = new int*[Grid::rows];
    for (int i = 0; i < Grid::rows; ++i) {
        grid[i] = new int[Grid::columns];
    }

    for (int row = 0; row < Grid::rows; ++row) {
        for (int col = 0; col < Grid::columns; ++col) {
            grid[row][col] = CLEAR;
        }
    }

    return grid;
}

void Grid::replace (int** grid) {
    deleteGrid();
    Grid::grid = grid;
}

void Grid::deleteGrid () {
    for (int i = 0; i < rows; ++i) {
        delete [] grid[i];
    }
    delete [] grid;
}