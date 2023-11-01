#include "SDL_share.h"


// https://stackoverflow.com/questions/53033971/how-to-get-the-color-of-a-specific-pixel-from-sdl-surface
void getSurfacePixel( SDL_PixelFormat *fmt, void *pixels, unsigned offset, unsigned *r, unsigned *g, unsigned *b, unsigned *a )
{
	if(!fmt || !pixels) return;

	int bpp = fmt->BytesPerPixel;
	uint32_t pix;
	uint8_t *raw = (uint8_t *)pixels + offset * bpp;

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

	SDL_GetRGB(pix, fmt, r, g, b);
}
