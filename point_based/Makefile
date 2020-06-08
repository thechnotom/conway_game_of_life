CXX = g++
CXXFLAGS = -Wall -g -std=c++11

main:	main.o Point.o GameBoard.o Control.o
	$(CXX) $(CXXFLAGS) -o main main.o Point.o GameBoard.o Control.o

main.o:	main.cpp Point.h GameBoard.h Control.o

Point.o:	Point.h

GameBoard.o:	GameBoard.h Point.h

Control.o:	Control.h GameBoard.h