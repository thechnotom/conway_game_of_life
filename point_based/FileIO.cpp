/*
File: FileIO.cpp
*/

#include "FileIO.h"

std::vector<std::string>* FileIO::importData (std::string filename) {
    std::string line;
    std::vector<std::string>* data = new std::vector<std::string>;
    std::ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        if (SHOW_CRITICAL_MESSAGES) { std::cout << "importData: UNABLE TO OPEN FILE FOR IMPORT" << std::endl; }
        exit(FILE_IO_FAILED);
    }
    while (getline(fileStream, line)) {
        if (SHOW_IMPORT_MESSAGES) { std::cout << "importData: imported line \"" << line << "\"" << std::endl; }
        data->push_back(line);
    }
    fileStream.close();
    return data;
}

std::vector<Point*>* FileIO::parseData (std::vector<std::string>* data) {
    std::vector<Point*>* points = new std::vector<Point*>;
    std::string currString;
    Point* currPoint;
    int currX, currY;
    int currDelimiterPos;

    for (unsigned i = 0; i < data->size(); ++i) {
        currString = data->at(i);
        try {
            currDelimiterPos = currString.find(",");
            currX = std::stoi(currString.substr(0, currDelimiterPos));
            currY = std::stoi(currString.substr(currDelimiterPos + 1, currString.length() - (currDelimiterPos + 1)));
        }
        catch (std::exception& e) {
            if (SHOW_CRITICAL_MESSAGES) { std::cout << "parseData: UNABLE TO PARSE POINT \"" << currString << "\"" << std::endl; }
            exit(PARSE_FAILED);
        }
        currPoint = new Point(currX, currY);
        if (SHOW_PARSE_MESSAGES) { std::cout << "parsedData: parsed Point " << currPoint->toString() << std::endl; }
        points->push_back(currPoint);
    }

    return points;
}

std::vector<Point*>* FileIO::getData (std::string filename) {
    std::vector<std::string>* rawData = importData(filename);
    std::vector<Point*>* points = parseData(rawData);
    delete rawData;
    return points;
}