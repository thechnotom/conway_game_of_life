CXX = g++
CXXFLAGS = -Wall -g -std=c++11

main:	main.o Grid.o GameBoard.o Control.o
	$(CXX) $(CXXFLAGS) -o main main.o Grid.o GameBoard.o Control.o

main.o:	main.cpp Grid.h GameBoard.h Control.h

Grid.o:	Grid.h

GameBoard.o: GameBoard.h

Control.o: Control.h GameBoard.h