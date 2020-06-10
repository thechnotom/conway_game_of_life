#ifndef FILEIO_H
#define FILEIO_H

/*
File: FileIO.h
Purpose: Provide file I/O functionality
*/

#include "Point.h"
#include "constants.h"

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <exception>

#define FILE_IO_FAILED 1
#define PARSE_FAILED 2

class FileIO {
    public:
        static std::vector<std::string>* importData (std::string filename);
        static std::vector<Point*>* parseData (std::vector<std::string>* data);
        static std::vector<Point*>* getData (std::string filename);

    private:
        FileIO ();
};

#endif