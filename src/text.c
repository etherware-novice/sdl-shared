#include "SDL_share.h" 

#ifndef MAXFONTC
#define MAXFONTC 16
#endif

#define INITCHECK if(TTF_WasInit() && TTF_Init()) return

static TTF_Font *defFont = NULL;
static int lastPTsize = 48;


static void initCheck(void)
{
	// TODO make the error macros better
	if(TTF_WasInit() && TTF_Init())
	{
		fprintf(stderr, "%s: %s", "Unable to init SDL_TTF\n", TTF_GetError());
		return;
	}

	if(defFont != NULL)
		return;

	char *fnt = resolveAssetPath("default.ttf");
	defFont = TTF_OpenFont(fnt, lastPTsize);
	free(fnt);
}

SDL_Surface *quickTextSurf( TTF_Font *font, SDL_Color fg, const char *text, int size, int width )
{
	initCheck();

	if(font)
		TTF_SetFontSize(font, size);
	else
	{
		if(size != lastPTsize)
			TTF_SetFontSize(defFont, size);
		lastPTsize = size;
		font = defFont;
	}

	SDL_Surface *tex = TTF_RenderText_Solid_Wrapped(font, text, fg, width);
	return tex;
}

void quickTextRender( SDL_Renderer *rend, TTF_Font *font, SDL_Color fg, const char *text, int size, int x, int y, int width )
{
	if(!rend) return;

	SDL_Surface *tex = quickTextSurf(font, fg, text, size, width);
	SDL_Texture *rntex = SDL_CreateTextureFromSurface(rend, tex);

	SDL_Rect box = {x, y, tex->w, tex->h};
	SDL_RenderCopy(rend, rntex, NULL, &box);
}
