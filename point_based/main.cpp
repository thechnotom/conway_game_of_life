/*
File: main.cpp
*/

#include "Control.h"
#include "FileIO.h"

int main(int argc, char* argv[]) {
    //FileIO::importData("test.txt");
    return Control::start("data.txt", 0, 0, 20, 20);
}