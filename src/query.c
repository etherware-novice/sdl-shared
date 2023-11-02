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
