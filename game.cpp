#include "Turtle.h"

int main(void)
{

	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	Turtle::world(SCREEN_WIDTH, SCREEN_HEIGHT);

	Turtle::start();

	Turtle *turtle = new Turtle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);

	int size = 1;

	turtle->setPenColor(0xFFFFFFFF);
	for (int i = 0; i < 100; i++)
	{
		turtle->move(size);
		turtle->turn(91);
		size += 5;
	}

	Turtle::end();

	return 0;
}