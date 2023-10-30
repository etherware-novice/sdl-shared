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

bool buttonColor( SDL_Rect loc, int r, int g, int b, int a );
{
	bool hover = false;

	if( mouseX < loc.x || mouseX > loc.bx )
		hover = true;
	if( mouseY < loc.y || mouseY > loc.by )
		hover = true;

	if(hover)
		SDL_SetRenderDrawColor(gameRender, r, g, b, a);

	SDL_RenderFillRect(gameRender, &loc);
	return hover;
}
