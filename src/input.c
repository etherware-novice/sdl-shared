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
	if( x < target.x || x > target.x + target.w )
		return false;
	if( y < target.y || y > target.y + target.h )
		return false;

	return true;
}

bool buttonColor( SDL_Renderer *render, SDL_Rect loc, int r, int g, int b, int a )
{
	bool hover = overlapTest(loc, mouseX, mouseY);

	if(hover)
		SDL_SetRenderDrawColor(render, r, g, b, a);

	SDL_RenderFillRect(render, &loc);
	return hover;
}

bool textureColor( SDL_Renderer *render, SDL_Rect loc, SDL_Texture *base, SDL_Texture *hovered )
{
	bool hover = overlapTest(loc, mouseX, mouseY);

	SDL_RenderCopy(render, hover ? hovered : base, NULL, &loc);
	return hover;
}
