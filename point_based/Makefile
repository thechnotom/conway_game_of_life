CXX = g++
CXXFLAGS = -Wall -g -std=c++11

main:	main.o Point.o GameBoard.o Control.o operators.o
	$(CXX) $(CXXFLAGS) -o main main.o Point.o GameBoard.o Control.o operators.o

main.o:	main.cpp Point.h GameBoard.h Control.o operators.o

Point.o:	Point.h constants.h

GameBoard.o:	GameBoard.h Point.h operators.cpp constants.h

Control.o:	Control.h GameBoard.h

operators.o:	operators.cpp