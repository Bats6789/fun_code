/*
 * Name: CBW_SDLTools.h
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A library of tools to manipulate SDL.  
 * Vers: 1.0.0 07/15/2020 CBW - Original code.
 */

#ifndef __CBW_SDL_TOOLS_H__
#define __CBW_SDL_TOOLS_H__

#include "../SDL2/SDL.h"

/**
 * @brief Checks if the cursor is over a rectangle.
 *
 * @param x The x location.
 * @param y The y location.
 * @param rect The rectangle to check.
 *
 * @return 1 if true and 0 if not.
 */
int CBW_MouseOver( int x, int y, SDL_Rect rect );

#endif
