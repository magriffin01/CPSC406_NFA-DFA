# A simple Makefile for CPSC 406
# Assumes the following directory hierarchy:
# Assignment X
# 	src
#       include

#this Makefile goes in the src directory

#change this to the correct assignment #
EXECUTABLE := courseproject

# the source files to be built
SOURCES := *.cpp

#stuff you don't need to worry about
INCLUDES := -I ../include
EXT := out
CC := g++

all:
	$(CC) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE).$(EXT)

realclean:
	find . -type f -name "*.o" -exec rm '{}' \;
	find . -type f -name "*.out" -exec rm '{}' \;
	find . -type f -name "*.exe" -exec rm '{}' \;
	find . -type f -name "*.nfa" -exec rm '{}' \;
	find . -type f -name "*.dfa" -exec rm '{}' \;

# this line required by make - don't delete
