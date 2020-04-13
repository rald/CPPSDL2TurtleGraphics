#ifndef TURTLE_HPP
#define TURTLE_HPP

#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <cmath>

class Turtle
{

  public:

	Turtle(double x, double y, double heading);

	static void world(int width, int height);
	static void start();
	static void end();
	static void events();

	void move(double distance);
	void turn(double angle);
	void setPenColor(Uint32 color);
	void penUp(void);
	void penDown(void);

  private:

	static bool quit;

	static int width, height;

	static SDL_Window *window;
	static SDL_Renderer *renderer;
	static SDL_Texture *texture;
	static SDL_Event event;

	double x, y;
	double heading;
	int r = 0xFF, g = 0xFF, b = 0xFF, a = 0xFF;
	bool isPenDown = true;
};

#endif