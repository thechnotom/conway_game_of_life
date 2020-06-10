CXX = g++
CXXFLAGS = -Wall -g -std=c++11

main:	main.o Point.o GameBoard.o Control.o operators.o FileIO.o
	$(CXX) $(CXXFLAGS) -o main main.o Point.o GameBoard.o Control.o operators.o FileIO.o

main.o:	main.cpp Point.h GameBoard.h Control.o operators.o FileIO.o

Point.o:	Point.h constants.h

GameBoard.o:	GameBoard.h Point.h operators.cpp constants.h

Control.o:	Control.h GameBoard.h FileIO.h

operators.o:	operators.cpp

FileIO.o:	FileIO.h