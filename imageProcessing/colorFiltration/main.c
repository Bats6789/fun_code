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
        Uint32 pixel; // the pixel index
        Uint8 r; // the red value
        Uint8 g; // the green value
        Uint8 b; // the blue value

        printf( "Loading image\n" );
        // read the "image.bmp" file into a surface
        surface = SDL_LoadBMP( "images.bmp" );
        printf( "Locking surface.\n" );
        // enable the surface to be modified
        if( SDL_LockSurface( surface ) != 0 ){
                printf( "ERROR: Failed to lock surface.\n" );
                return( -1 );
        }
        printf( "Modifying image.\n" );
        // moves through every pixel in the image.
        for( int i = 0; i < surface->clip_rect.w * surface->clip_rect.h; ++i ){
                // obtain the pixel index value.
                pixel = *(((Uint8 *)surface->pixels) + i * surface->format->BytesPerPixel);
                // convert the index to an rgb value.
                SDL_GetRGB( pixel, surface->format, &r, &g, &b );
                // if the pixel is bright red replace it with blue
                if( r > 0 && g == 0 && b == 0 ){
                        r = 0;
                        b = 255;
                }
                // map the rgb values to an index
                pixel = SDL_MapRGB( surface->format, r, g, b );
                // store the index back in the location.
                *(((Uint8 *)surface->pixels) + i * surface->format->BytesPerPixel) = pixel;
        }
        printf( "Unlocking surface.\n" );
        // disable the surface for modification
        SDL_UnlockSurface( surface );
        printf( "Saving image to output.bmp.\n" );
        // save the image to "output.bmp"
        SDL_SaveBMP( surface, "output.bmp" );
        printf( "Done\n" );

        return( EXIT_SUCCESS );
}
