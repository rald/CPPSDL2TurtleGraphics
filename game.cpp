#include "Turtle.h"

void square(Turtle *t,int size) {
	for(int i=0;i<4;i++) {
		t->move(size);
		t->turn(90);
	}
}

int main(void)
{

	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	Turtle::world(SCREEN_WIDTH, SCREEN_HEIGHT);

	Turtle::start();

	Turtle *t1 = new Turtle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	Turtle *t2 = new Turtle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);

	t1->setPenColor(0xFF0000FF);
	square(t1,100);

	t2->setPenColor(0x00FF00FF);
	t2->turn(45);
	square(t2,100);

	Turtle::end();

	return 0;
}