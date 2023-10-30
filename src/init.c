#include "steno.h"

SDL_Window *gameWin;
SDL_Renderer *gameRender;
SDL_PixelFormat *pixFormat;

void SDLinit(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		CRASHSTUB;

	gameWin = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIN_WIDTH, WIN_HEIGHT, WIN_TAGS);
	if(!gameWin) CRASHSTUB;

	gameRender = SDL_CreateRenderer(gameWin, -1, SDL_RENDERER_ACCELERATED);
	if(!gameRender) CRASHSTUB;

	SDL_RendererInfo rin;
	if(SDL_GetRendererInfo(gameRender, &rin)) CRASHSTUB;

	SDL_SetRenderDrawColor(gameRender, 0x50, 0x50, 0x50, 0xFF);
}
