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

bool overlapTest( SDL_Rect target, int x, int y )
{
	if( x < target.x || x > target.w )
		return true;
	if( y < target.y || y > target.h )
		return true;

	return false;
}

bool buttonColor( SDL_Rect loc, int r, int g, int b, int a );
{
	bool hover = overlapTest(loc, mouseX, mouseY);

	if(hover)
		SDL_SetRenderDrawColor(gameRender, r, g, b, a);

	SDL_RenderFillRect(gameRender, &loc);
	return hover;
}

bool textureColor( SDL_Rect loc, SDL_Texture *base, SDL_Texture *hovered )
{
	bool hover = overlapTest(loc, mouseX, mouseY);

	SDL_RenderCopy(gameRender, hover ? hovered : base, NULL, &loc);
	return hover;
}
