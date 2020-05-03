/*
 * Name: main.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Simulates a 2D card driving. 
 * Vers: 1.0.0 05/01/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/sdl.h>
#include <SDL2/SDL_image.h>

#define WIDTH 640
#define HEIGHT 480
#define DELAY 200

int main ( int argc, char **argv ){
        int quit;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        SDL_Color sky;
        SDL_Texture *texture;
        SDL_Texture *car;
        SDL_Surface *surface;
        SDL_Rect backGroundDst;
        SDL_Rect carDst;

        SDL_Init( SDL_INIT_EVERYTHING );
        IMG_Init( IMG_INIT_PNG );

        window = SDL_CreateWindow( "Car", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0 );
        renderer = SDL_CreateRenderer( window, -1, 0 );
        surface = IMG_Load( "Terrain.png" );
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_FreeSurface( surface );

        surface = IMG_Load( "Car.png" );
        car = SDL_CreateTextureFromSurface( renderer, surface );

        backGroundDst.x = 0;
        backGroundDst.y = HEIGHT / 2;
        backGroundDst.w = WIDTH;
        backGroundDst.h = HEIGHT / 2;

        carDst.x = WIDTH / 2;
        carDst.y = HEIGHT / 2;
        carDst.w = 100;
        carDst.h = 60;

        sky.r = 58;
        sky.g = 252;
        sky.b = 249;
        sky.a = 255;
        quit = 0;

        while( !quit ){
                while( SDL_PollEvent( &event )){
                        if( event.type == SDL_QUIT ){
                                quit = 1;
                        } else if( event.type == SDL_KEYDOWN ){
                                switch( event.key.keysym.sym ){
                                        case SDLK_ESCAPE:
                                        case SDLK_q:
                                                quit =  1;
                                                break;
                                }
                        }
                }
                if( SDL_SetRenderDrawColor( renderer, sky.r, sky.g, sky.b, sky.a ) != 0 ){
                        SDL_LogError( SDL_LOG_CATEGORY_ERROR, "ERROR: Renderer failed to set to sky: %s\n",
                                        SDL_GetError());
                }
                SDL_RenderClear( renderer );
                SDL_RenderCopy( renderer, texture, NULL, &backGroundDst );
                SDL_RenderCopy( renderer, car, NULL, &carDst );
                SDL_RenderPresent( renderer );
                SDL_Delay( DELAY );

        }

        return( EXIT_SUCCESS );
}
