#include "IO.h"

static SDL_Surface* mScreen;                    // Screen
static Uint32 mColors[COLOR_MAX] ={0x000000ff,	// Colors
                               0xff0000ff, 0x00ff00ff, 0x0000ffff,
                               0x00ffffff, 0xff00ffff, 0xffff00ff,
                               0xffffffff};

/**
 * Initialize
 */
IO::IO()
{
    InitGraphics();
}

/**
 * 
 * @param x1 X value of upper left corner of the rectangle
 * @param y1 Y value of upper left corner of the rectangle
 * @param x2 X value of lower right corner of the rectangle
 * @param y2 Y value of lower right corner of the rectangle
 * @param c Rectangel color
 */
void IO::DrawRectangle(int x1, int y1, int x2, int y2, enum color c)
{
    boxColor(mScreen,x1,y1,x2,y2-1,mColors[c]);
}

/**
 * Clears the screen by coloring it all black
 */
void IO::ClearScreen()
{
    boxColor(mScreen,0,0,mScreen->w-1,mScreen->h-1,mColors[BLACK]);
}

/**
 * Return the height of the screen
 * @return Screen height(int)
 */
int IO::GetScreenHeight()
{
    return mScreen->h;
}

/**
 * SDL Graphical initialization
 * @return Success code
 */
int IO::InitGraphics()
{
    const SDL_VideoInfo* info;
    Uint8 video_bpp;
    Uint32 videoflags;

    // Initalize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);

    //Alpha blending doesnt work well at 8 -bit color
    info = SDL_GetVideoInfo();
    if (info->vfmt->BitsPerPixel > 8)
    {
        video_bpp = info->vfmt->BitsPerPixel;
    }
    else
    {
        video_bpp = 16;
    }
    videoflags = SDL_SWSURFACE | SDL_DOUBLEBUF;

    //Set 640x480 video mode
    if ((mScreen = SDL_SetVideoMode(640,480,video_bpp,videoflags)) == NULL)
    {
        fprintf(stderr, "SDL_SetVideoMode Error: %s\n", SDL_GetError());
        return 2;
    }
    return 0;
}

/**
 * Keyboard input
 * @return key
 */
int IO::PollKey()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            return event.key.keysym.sym;
        case SDL_QUIT:
            exit(3);
        }
    }
    return -1;
}

/**
 * Keyboard input
 * @return key
 */
int IO::GetKey()
{
    SDL_Event event;
    while (true)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
            break;
        if (event.type == SDL_QUIT)
            exit(3);
    };
    return event.key.keysym.sym;
}

/**
 * Keyboard input
 * @param key Keypress value
 * @return key
 */
int IO::IsKeyDown(int key)
{
    Uint8* mKeytable;
    int mNumkeys;
    SDL_PumpEvents();
    mKeytable = SDL_GetKeyState(&mNumkeys);
    return mKeytable[key];
    
}


/**
 * Update screen
 */
void IO::UpdateScreen()
{
    SDL_Flip(mScreen);
}
