/*
 * Name: CBW_SDLTools.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A library of tools to manipulate SDL. 
 * Vers: 1.0.0 07/15/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "CBW_SDLTools.h"

/**
 * @brief Checks if the cursor is over a rectangle.
 *
 * @param x The x location.
 * @param y The y location.
 * @param rect The rectangle to check.
 *
 * @return 1 if true and 0 if not.
 */
int CBW_MouseOver( int x, int y, SDL_Rect rect ){
    int results;

    results = ( x >= rect.x ) && ( x < rect.x + rect.w ) &&
              ( y >= rect.y ) && ( y < rect.y + rect.h );

    return( results );
}
