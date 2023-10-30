#include "steno.h"
#include <stdlib.h>
#include <stdbool.h>


static void mainloop(void)	/* emscript is weird */
{
	SDL_SetRenderDrawColor(gameRender, 0x50, 0x50, 0x50, 0xFF);
	SDL_RenderClear(gameRender);

	eventProc();

	static SDL_Texture* rf = NULL;
       	if(!rf) rf = loadBMPtexture("rf.bmp");

	static double angle = 0;
	if(!(mouseClick & SDL_BUTTON_LMASK)) angle += 0.05;
	if(angle >= 360) angle = 0;

	SDL_RenderCopyEx(gameRender, rf, NULL, NULL, angle, NULL, SDL_FLIP_NONE);

	int mx, my;
	SDL_GetMouseState(&mx, &my);
	SDL_Rect mousecurse = { mx - 10, my - 10, 20, 20 };
	SDL_SetRenderDrawColor(gameRender, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gameRender, &mousecurse);

	if(buttonColor(20, 20, 100, 40, 0, 255, 0, 100) && mouseClick & SDL_BUTTON_LMASK)
		exit(0);

	SDL_RenderPresent(gameRender);
}

int main()
{
	SDLinit();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(mainloop, 0, 1);
#else
	while(1) { mainloop(); }
#endif

}