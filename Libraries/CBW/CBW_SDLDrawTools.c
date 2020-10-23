/*
 * Name: CBW_SDLDrawTools.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A collection of tools to help draw shapes in SDL. 
 * Vers: 1.0.0 10/19/2020 CBW - Original code.
 */

#include "CBW_SDLDrawTools.h"
#include <SDL2/SDL.h>

void CBW_SDLRenderDrawCircle( SDL_Renderer *renderer, SDL_Point point, unsigned int radius ){
    int x = radius - 1;
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = tx - 2 * radius;

	// draw the circle
    while( x >= y ){
        // Quad I
        SDL_RenderDrawPoint( renderer, point.x + x, point.y + y );
        SDL_RenderDrawPoint( renderer, point.x + y, point.y + x );
        // Quad II
        SDL_RenderDrawPoint( renderer, point.x - x, point.y + y );
        SDL_RenderDrawPoint( renderer, point.x - y, point.y + x );
        // Quad III
        SDL_RenderDrawPoint( renderer, point.x - x, point.y - y );
        SDL_RenderDrawPoint( renderer, point.x - y, point.y - x );
        // Quad IV
        SDL_RenderDrawPoint( renderer, point.x + x, point.y - y );
        SDL_RenderDrawPoint( renderer, point.x + y, point.y - x );

        if( error <= 0 ){
            ++y;
            error += ty;
            ty += 2;
        }

        if( error > 0 ){
            --x;
            tx += 2;
            error += tx - 2 * radius;
        }
    }
}

void CBW_SDLRenderFillCircle( SDL_Renderer *renderer, SDL_Point point, unsigned int radius ){
    int x = radius - 1;
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = tx - 2 * radius;

	// draw the circle
    while( x >= y ){
        SDL_RenderDrawLine( renderer, point.x - x, point.y - y, point.x + x, point.y - y );
        SDL_RenderDrawLine( renderer, point.x - x, point.y + y, point.x + x, point.y + y );
        SDL_RenderDrawLine( renderer, point.x - y, point.y - x, point.x + y, point.y - x );
        SDL_RenderDrawLine( renderer, point.x - y, point.y + x, point.x + y, point.y + x );

        if( error <= 0 ){
            ++y;
            error += ty;
            ty += 2;
        }

        if( error > 0 ){
            --x;
            tx += 2;
            error += tx - 2 * radius;
        }
    }
}
