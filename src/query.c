#include "SDL_share.h"


// https://stackoverflow.com/questions/53033971/how-to-get-the-color-of-a-specific-pixel-from-sdl-surface
void getSurfacePixel( SDL_Surface *src, unsigned x, unsigned y, unsigned *r, unsigned *g, unsigned *b, unsigned *a )
{
	if(!src) return;

	int bpp = src->format->BytesPerPixel;
	uint32_t pix;
	uint8_t *raw = src->pixels;
	raw += x * bpp;
	raw += y * src->pitch;

	switch(bpp)
	{
		case 1:
		pix = *raw;
		break;

		case 2:
		pix = *(uint16_t *) raw;
		break;

		case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			pix = raw[0] << 16 | raw[1] << 8 | raw[2];
		else
			pix = raw[0] | raw[1] << 8 | raw[2] << 16;
		break;

		case 4:
		pix = *(uint32_t *) raw;
	}

	SDL_GetRGBA(pix, src->format, r, g, b, a);
}

void getRenderPixel( SDL_Renderer *rend, unsigned x, unsigned y, unsigned *r, unsigned *g, unsigned *b, unsigned *a )
{
	if(!rend) return;

	static const SDL_PixelFormatEnum fmt = SDL_PIXELFORMAT_RGBA32;

	uint32_t exp;
	SDL_Rect pix = { x, y, 1, 1 };
	if(SDL_RenderReadPixels(rend, &pix, fmt,
				&exp, 1) != 0)
	{
		LOG_PWARN("Unable to get render pixel data");
		return;
	}

	SDL_PixelFormat *alofmt = SDL_AllocFormat(fmt);
	SDL_GetRGBA(exp, SDL_AllocFormat(fmt),
			r, g, b, a);

	SDL_FreeFormat(alofmt);
}
