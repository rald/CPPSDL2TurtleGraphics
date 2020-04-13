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

	Turtle::quit=false;
	
	Turtle::width=w;
	Turtle::height=h;
	
	Turtle::window=NULL;
	Turtle::renderer=NULL;
	Turtle::texture=NULL;
				
	srand(time(NULL));

	if(SDL_Init(SDL_INIT_VIDEO)<0) {
		die("SDL_Error: %s\n",SDL_GetError());
	}

	Turtle::window=SDL_CreateWindow(
			"Turtle Graphics",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			Turtle::width,
			Turtle::height,
			SDL_WINDOW_SHOWN
	);

	if(Turtle::window==NULL) {
		die("SDL_Error: %s\n",SDL_GetError());
	}

	Turtle::renderer=SDL_CreateRenderer(
			Turtle::window,
			-1,
			SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_TARGETTEXTURE);

	if(Turtle::renderer==NULL) {
		die("SDL_Error: %s\n",SDL_GetError());
	}

	SDL_SetRenderDrawBlendMode(Turtle::renderer,SDL_BLENDMODE_BLEND);

	Turtle::texture=SDL_CreateTexture(
			Turtle::renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			Turtle::width,
			Turtle::height
	);

}

void Turtle::events() {
	while(SDL_PollEvent(&Turtle::event)!=0) {
		switch(Turtle::event.type) {
			case SDL_QUIT: Turtle::quit=true; break;
			case SDL_KEYDOWN:
				switch(Turtle::event.key.keysym.sym) {
					case SDLK_ESCAPE: quit=true; break;
				}
			break;
		}
	}
}

void Turtle::start() {
	SDL_SetRenderTarget(Turtle::renderer,Turtle::texture);
			
	SDL_SetRenderDrawColor(Turtle::renderer,0x00,0x00,0x00,0xFF);
	SDL_RenderClear(Turtle::renderer);
	
	SDL_SetRenderDrawColor(Turtle::renderer,0xFF,0xFF,0xFF,0xFF);
	
	SDL_Rect rect={0,0,Turtle::width,Turtle::height};
	SDL_RenderDrawRect(Turtle::renderer,&rect);
}

void Turtle::end() {
	SDL_SetRenderTarget(Turtle::renderer,NULL);
	
	SDL_Rect rect={0,0,Turtle::width,Turtle::height};
	
	SDL_RenderCopy(Turtle::renderer,Turtle::texture,NULL,&rect);	
	SDL_RenderPresent(Turtle::renderer);

	while(!Turtle::quit) {
		events();
	}

	SDL_DestroyTexture(Turtle::texture);
	SDL_DestroyRenderer(Turtle::renderer);
	SDL_DestroyWindow(Turtle::window);

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
				SDL_SetRenderTarget(Turtle::renderer,Turtle::texture);
				
				SDL_SetRenderDrawColor(Turtle::renderer,r,g,b,a);
				SDL_RenderDrawPoint(Turtle::renderer,x,y);
	
				SDL_SetRenderTarget(Turtle::renderer,NULL);
				SDL_Rect rect={0,0,Turtle::width,Turtle::height};	
				SDL_RenderCopy(Turtle::renderer,Turtle::texture,NULL,&rect);
				SDL_RenderPresent(Turtle::renderer);
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
