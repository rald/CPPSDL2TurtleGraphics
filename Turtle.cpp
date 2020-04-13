#include "Turtle.hpp"

bool Turtle::quit=false;

int Turtle::height=0;
int Turtle::width=0;

SDL_Window *Turtle::window=NULL;
SDL_Renderer *Turtle::renderer=NULL;
SDL_Texture *Turtle::texture=NULL;
SDL_Event Turtle::event;

static void die(const char *fmt, ...) {
	va_list args;
	va_start(args,fmt);
	vprintf(fmt,args);
	va_end(args);
	exit(EXIT_FAILURE);
}

static double rad(double deg) {
	return deg*M_PI/180.0;
}

static double sgn(double x) {
	return x<0?-1:x>0?1:0;
}

void Turtle::world(int w,int h) {

	quit=false;
	
	width=w;
	height=h;
	
	window=NULL;
	renderer=NULL;
	texture=NULL;
				
	srand(time(NULL));

	if(SDL_Init(SDL_INIT_VIDEO)<0) {
		die("SDL_Error: %s\n",SDL_GetError());
	}

	Turtle::window=SDL_CreateWindow(
			"Turtle Graphics",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_SHOWN
	);

	if(window==NULL) {
		die("SDL_Error: %s\n",SDL_GetError());
	}

	renderer=SDL_CreateRenderer(
			Turtle::window,
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
			width,
			height
	);

}

void Turtle::events() {
	while(SDL_PollEvent(&event)!=0) {
		switch(event.type) {
			case SDL_QUIT: quit=true; break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_ESCAPE: quit=true; break;
				}
			break;
		}
	}
}

void Turtle::start() {
	SDL_SetRenderTarget(renderer,Turtle::texture);
			
	SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
	
	SDL_Rect rect={0,0,width,height};
	SDL_RenderDrawRect(renderer,&rect);
}

void Turtle::end() {
	SDL_SetRenderTarget(renderer,NULL);
	
	SDL_Rect rect={0,0,width,height};
	
	SDL_RenderCopy(renderer,texture,NULL,&rect);	
	SDL_RenderPresent(renderer);

	while(!quit) {
		events();
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

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
				SDL_Rect rect={0,0,width,height};	
				SDL_RenderCopy(renderer,texture,NULL,&rect);
				SDL_RenderPresent(renderer);
			}
									
			distance-=sgn(distance);	
			
			events();
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
