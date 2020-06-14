/*
File: main.cpp
*/

#include "Control.h"
#include "FileIO.h"
#include "constants.h"

#include <exception>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return Control::start("data.txt", 0, 0, 25, 25);
    }
    else if (argc == 2) {
        return Control::start(argv[1], 0, 0, 25, 25);
    }

    try {
        if (argc == 4) {
            return Control::start(argv[1], 0, 0, std::stoi(argv[2]), std::stoi(argv[3]));
        }
        else if (argc == 6) {
            return Control::start(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]));
        }
    }
    catch (std::exception e) {
        if (SHOW_CRITICAL_MESSAGES) { std::cout << "main: INVALID ARGUMENT TYPE(S)" << std::endl; }
    }

    std::cout << "Usage: ./main" << std::endl;
    std::cout << "       ./main <filename>" << std::endl;
    std::cout << "       ./main <filename> <height> <width>" << std::endl;
    std::cout << "       ./main <filename> <top row> <top column> <height> <width>" << std::endl;
    return 0;
}