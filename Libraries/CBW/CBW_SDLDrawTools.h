/*
 * Name: CBW_SDLDrawTools.h
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A collection of tools to help draw shapes in SDL.  
 * Vers: 1.0.0 10/19/2020 CBW - Original code.
 */

#ifndef __CBW_SDL_DRAW_TOOLS_H__
#define __CBW_SDL_DRAW_TOOLS_H__

#include <SDL2/SDL.h>

void CBW_SDLRenderDrawCircle( SDL_Renderer *renderer, SDL_Point point, unsigned int radius );

void CBW_SDLRenderFillCircle( SDL_Renderer *renderer, SDL_Point point, unsigned int radius );

#endif
