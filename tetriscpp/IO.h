#pragma once
#ifndef LINUX
#include "SDL/include/SDL.h"							
#include "SDL/SDL_GfxPrimitives/SDL_gfxPrimitives.h"
#else
#include <SDL/SDL.h>									
#include "SDL/SDL_GfxPrimitives/sdl_gfxprimitives.h"	
#endif
#pragma comment (lib, "SDL/lib/SDL.lib")
#pragma comment (lib, "SDL/SDL_GfxPrimitives/SDL_GfxPrimitives_Static.lib")
// ------ Enums -----

enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX}; // Colors
class IO
{
public:
    IO();
    void DrawRectangle(int x1, int y1, int x2, int y2, enum color c);
    void ClearScreen();
    int GetScreenHeight();
    int InitGraphics();
    int PollKey();
    int GetKey();
    int IsKeyDown(int key);
    void UpdateScreen();
};
