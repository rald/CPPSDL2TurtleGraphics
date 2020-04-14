#include "Turtle.h"

void spiral(Turtle * t)
{
	int size = 1;
	for (int i = 0; i < 50; i++)
	{
		t->move(size);
		t->turn(91);
		size += 5;
	}
}

int main(void)
{
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	Turtle::world(SCREEN_WIDTH, SCREEN_HEIGHT);

	Turtle::start();

	Turtle *t1 = new Turtle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);

	t1->setPenColor(0x00FF00FF);
	spiral(t1);

	Turtle::end();

	return 0;
}