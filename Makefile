#
# Makefile for HW6
#
CXX      = clang++
CXXFLAGS = -g -Wall -Wextra
LDFLAGS  = -g

hw6degrees: main.cpp HashTable.cpp HashTable.h hashfunc.cpp hashfunc.h Graph.cpp Graph.h
	${CXX} ${CXXFLAGS} -o hw6degrees main.cpp HashTable.cpp hashfunc.cpp Graph.cpp

clean:
	rm -f hw6degrees

provide:
	provide comp15 hw6 main.cpp Makefile ReadMe.md hashfunc.cpp hashfunc.h HashTable.cpp HashTable.h HashTable.h HashTable.cpp Graph.h Graph.cpp 
