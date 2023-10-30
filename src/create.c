#include "steno.h"
#include <string.h>


char *resolveAssetPath( const char *path )
{
	if(!path) return NULL;
	size_t len = strlen(path) + 2;
	char *resolved = NULL;

	len += strlen(ASSET_PATH);
	resolved = malloc(sizeof(char) * len);
	snprintf(resolved, len, "%s/%s", ASSET_PATH, path);

	LOG_DEBUG("resolved asset %s to %s\n", path, resolved);

	return resolved;
}

SDL_Surface *loadBMPsurface( const char *path )
{
	char *rp = resolveAssetPath(path);
	SDL_Surface *loaded = SDL_LoadBMP(rp);
	if(!loaded)
		LOG_PERROR("Unable to load BMP");

	free(rp);

	if(!pixFormat)
		pixFormat = loaded->format;	// spagetti

	return loaded;
}

SDL_Texture *loadBMPtexture( const char *path )
{
	SDL_Surface *median = loadBMPsurface(path);
	if(!median) return NULL;

	SDL_Texture *loaded = SDL_CreateTextureFromSurface(gameRender, median);
	if(!loaded)
		LOG_PERROR("Unable to convert surface to texture");

	SDL_FreeSurface(median);
	return loaded;
}
