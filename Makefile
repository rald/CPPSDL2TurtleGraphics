CPPFLAGS=-Wall -g
LDFLAGS=-lm -lSDL2

game: game.o Turtle.o

game.o: game.cpp

Turtle.o: Turtle.cpp