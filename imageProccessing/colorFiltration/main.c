/*
 * Name: main.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Filters out the colors in a certain range.
 * Vers: 1.0.0 04/25/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sdl.h>

int main( int argc, char **argv ){ 
        SDL_Surface *surface;
        Uint32 pixel;
        Uint8 r;
        Uint8 g;
        Uint8 b;

        printf( "Loading image\n" );
        surface = SDL_LoadBMP( "images.bmp" );
        //printf( "%d\n", surface->format->BytesPerPixel );
        printf( "Locking surface.\n" );
        if( SDL_LockSurface( surface ) != 0 ){
                printf( "ERROR: Failed to lock surface.\n" );
                return( -1 );
        }
        printf( "Modifying image.\n" );
        for( int i = 0; i < surface->clip_rect.w * surface->clip_rect.h; ++i ){
                pixel = *(((Uint8 *)surface->pixels) + i * surface->format->BytesPerPixel);
                SDL_GetRGB( pixel, surface->format, &r, &g, &b );
                if( r > 0 && g == 0 && b == 0 ){
                        r = 0;
                        b = 255;
                }
                pixel = SDL_MapRGB( surface->format, r, g, b );
                *(((Uint8 *)surface->pixels) + i * surface->format->BytesPerPixel) = pixel;
        }
        printf( "Unlocking surface.\n" );
        SDL_UnlockSurface( surface );
        printf( "Saving image to output.bmp.\n" );
        SDL_SaveBMP( surface, "output.bmp" );
        printf( "Done\n" );

        return( EXIT_SUCCESS );
}
