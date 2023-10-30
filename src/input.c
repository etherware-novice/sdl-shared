#include "SDL_share.h"

uint32_t mouseClick;
uint32_t mouseClickInstant;
uint32_t mouseX;
uint32_t mouseY;


void eventProc(void)
{
	mouseClickInstant = 0;

	SDL_Event e;
	while(SDL_PollEvent(&e) != 0)
	{
		switch(e.type)
		{
			case SDL_QUIT:
			exit(0);
			break;

			case SDL_MOUSEBUTTONDOWN:
			mouseClickInstant |= SDL_BUTTON(e.button.button);
			break;

			case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				e.type = SDL_QUIT;
				e.quit.timestamp = 0;	// dont feel like importing <time.h> for this
				SDL_PushEvent(&e);
			}
		}
	}

	mouseClick = SDL_GetMouseState(&mouseX, &mouseY);
}

bool buttonColor( int x, int y, int w, int h, int r, int g, int b, int a )
{
	int bx = x + w;
	int by = y + h;
	SDL_Rect fill = { x, y, w, h };
	SDL_RenderFillRect(gameRender, &fill);

	if( mouseX < x || mouseX > bx )
	{
		SDL_RenderFillRect(gameRender, &fill);
		return false;
	}
	if( mouseY < y || mouseY > by )
	{
		SDL_RenderFillRect(gameRender, &fill);
		return false;
	}


	SDL_SetRenderDrawColor(gameRender, r, g, b, a);
	SDL_RenderFillRect(gameRender, &fill);
	return true;
}
