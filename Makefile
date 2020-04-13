CC=g++
CPPFLAGS=-Wall -g
LDFLAGS=-lm -lSDL2
EXE=game
OBJS=game.o Turtle.o

$(EXE): $(OBJS)

game.o: game.cpp

Turtle.o: Turtle.cpp

clean:
	rm $(OBJS) $(EXE)
