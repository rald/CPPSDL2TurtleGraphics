#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <ctime>

const char *GAME_TITLE="Turtle Graphics";

const int SCREEN_WIDTH=1024;
const int SCREEN_HEIGHT=768;

SDL_Window *window=NULL;
SDL_Renderer *renderer=NULL;
SDL_Texture *texture=NULL;
SDL_Event event;

bool quit=false;

void die(const char *fmt, ...) {
	va_list args;
	va_start(args,fmt);
	vprintf(fmt,args);
	va_end(args);
	exit(EXIT_FAILURE);
}

double rad(double deg) {
	return deg*M_PI/180.0;
}

double sgn(double x) {
	return x<0?-1:x>0?1:0;
}

void Events(SDL_Event *event) {
	while(SDL_PollEvent(event)!=0) {
		switch(event->type) {
			case SDL_QUIT: quit=true; break;
			case SDL_KEYDOWN:
				switch(event->key.keysym.sym) {
					case SDLK_ESCAPE: quit=true; break;
				}
			break;
		}
	}
}

class Turtle {
public:
	Turtle(double x,double y,double heading);
	void move(double distance);
	void turn(double angle);
	void setPenColor(Uint32 color);
	void penUp(void);
	void penDown(void);
private:
	double x,y;
	double heading;
	int r=0xFF,g=0xFF,b=0xFF,a=0xFF;
	bool isPenDown=true;
};

Turtle::Turtle(double x,double y,double heading) {
	this->x=x;
	this->y=y;
	this->heading=heading;
}

void Turtle::move(double distance) {
	if(isPenDown) {
		while(abs(distance)>=0.01) {	

			x+=cos(rad(heading))*sgn(distance);
			y+=sin(rad(heading))*sgn(distance);

			if(isPenDown) {
				SDL_SetRenderTarget(renderer,texture);
				
				SDL_SetRenderDrawColor(renderer,r,g,b,a);
				SDL_RenderDrawPoint(renderer,x,y);
	
				SDL_SetRenderTarget(renderer,NULL);
				SDL_Rect rect={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};	
				SDL_RenderCopy(renderer,texture,NULL,&rect);
				SDL_RenderPresent(renderer);
			}
									
			distance-=sgn(distance);	
			
			Events(&event);
		}		
	}
}

void Turtle::turn(double angle) {
	heading+=angle;	
}

void Turtle::setPenColor(Uint32 color) {
	r=(color >> 24) & 255;
	g=(color >> 16) & 255;
	b=(color >>  8) & 255;
	a= color        & 255;	
} 

void Turtle::penUp() {
	isPenDown=false;	
}

void Turtle::penDown() {
	isPenDown=true;
}

int main(void) {

	SDL_Rect rect={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

	srand(time(NULL));

	if(SDL_Init(SDL_INIT_VIDEO)<0) {
		die("SDL_Error: %s\n",SDL_GetError());
	}

	window=SDL_CreateWindow(
			GAME_TITLE,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
	);

	if(window==NULL) {
		die("SDL_Error: %s\n",SDL_GetError());
	}

	renderer=SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_TARGETTEXTURE);

	if(renderer==NULL) {
		die("SDL_Error: %s\n",SDL_GetError());
	}

	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

	texture=SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			SCREEN_WIDTH,
			SCREEN_HEIGHT
	);

	SDL_SetRenderTarget(renderer,texture);
			
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
	SDL_RenderDrawRect(renderer,&rect);

	Turtle *turtle=new Turtle(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0);

	int size=1;

	turtle->setPenColor(0xFFFFFFFF);
	for(int i=0;i<100;i++) {
		turtle->move(size);
		turtle->turn(91);
		size+=5;
	}

	SDL_SetRenderTarget(renderer,NULL);
	SDL_RenderCopy(renderer,texture,NULL,&rect);	
	SDL_RenderPresent(renderer);

	while(!quit) {
		Events(&event);
	}

	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}