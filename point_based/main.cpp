/*
File: main.cpp
*/

#include "Control.h"
#include "FileIO.h"

int main(int argc, char* argv[]) {
    if (argc == 2) {
        return Control::start(argv[1], 0, 0, 50, 50);
    }
    return Control::start("data.txt", 0, 0, 50, 50);
}