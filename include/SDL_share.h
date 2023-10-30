#ifndef SDL_SHARE_H
#define SDL_SHARE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WIN_TITLE "window title"
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define WIN_TAGS SDL_WINDOW_SHOWN

#define CRASHSTUB fprintf(stderr, "add crash condition here (line %d)\n", __LINE__)
#define LOG_DEBUG(...) printf(__VA_ARGS__)
#define LOG_PERROR(msg) fprintf(stderr, "%s: %s\n", msg, SDL_GetError())


// init.c - sets up enviroment
extern SDL_Window *gameWin;
extern SDL_Renderer *gameRender;
extern SDL_PixelFormat *pixFormat;
void SDLinit(void);

// create.c - creating new objects
char *resolveAssetPath( const char *path );
SDL_Surface *loadBMPsurface( const char *path );
SDL_Texture *loadBMPtexture( const char *path );

// input.c - input and event handles
extern uint32_t mouseClick;		// held
extern uint32_t mouseClickInstant;	// changed this frame
extern uint32_t mouseX;
extern uint32_t mouseY;
void eventProc(void);
bool overlapTest( SDL_Rect target, int x, int y );
// returns true if mouse is over it
bool buttonColor( SDL_Renderer *render, SDL_Rect loc, int r, int g, int b, int a );
bool textureColor( SDL_Renderer *render, SDL_Rect loc, SDL_Texture *base, SDL_Texture *hovered );

#endif
