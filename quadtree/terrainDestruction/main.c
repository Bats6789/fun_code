/*
 * Name: main.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Terrain destruction using a quad tree data structure. 
 * Vers: 1.0.0 04/25/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/sdl.h>
#include <errno.h>
#include <math.h>

#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 600
#define DELAY 100

typedef struct {
        Uint32 pixel;
        int health;
} environmentData;

typedef struct quadType{
        // location data
        int x;
        int y;
        int w;
        int h;
        // information data
        int health;
        // tree info
        struct quadType *Root;
        // children of the tree
        struct quadType *bottomLeft;
        struct quadType *bottomRight;
        struct quadType *topLeft;
        struct quadType *topRight;
} quadType;

int createTree( quadType *root, environmentData *data, int x, int y, int w, int h, int maxW, int maxH  );
int updateTree( quadType *root, environmentData *data, int x, int y, int w, int h, int maxW, int maxH  );
int updateSurface( quadType *root, environmentData *data, int x, int y, int w, int h, int maxW, int maxH, SDL_Surface *surface );
void freeTree( quadType *root );

int main ( int argc, char **argv ){ 
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Surface *surface;
        SDL_Event event;
        SDL_Texture *texture;
        int quit;
        int count;
        int health;
        int radius;
        int RADIUS_SCALE;
        Uint32 greenPixels[ 10 ];
        Uint32 bluePixel;
        environmentData data[ SCREEN_HEIGHT * SCREEN_WIDTH ];
        quadType *root;


        window = SDL_CreateWindow( "Quad Tree",
                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        SCREEN_WIDTH, SCREEN_HEIGHT,
                        /* SDL_WINDOW_BORDERLESS */0);
        if( window == NULL ){
                fprintf( stderr, "Could not create window: %s\n", SDL_GetError());
                return( -1 );
        }
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if( renderer == NULL ){
                fprintf( stderr, "Could not create renderer: %s\n", SDL_GetError());
                return( -1 );
        }
        surface = SDL_CreateRGBSurface( 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                        32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
        if( surface == NULL ){
                fprintf( stderr, "Failed to create surface: %s\n", SDL_GetError());
                return( -1 );
        }
        if( SDL_LockSurface( surface ) != 0 ){
                fprintf( stderr, "ERROR: Failed to lock surface: %s\n", SDL_GetError());
                return( -1 );
        }
        for( int i = 0; i < 10; ++i ){
                greenPixels[ 9 - i ] = SDL_MapRGBA( surface->format, 0, 255, 0, 255 - i * 15 );
        }
        bluePixel = SDL_MapRGB( surface->format, 0, 0, 255 );
        for( int i = 0; i < surface->clip_rect.w * surface->clip_rect.h; ++i ){
                if( i > surface->clip_rect.w * surface->clip_rect.h / 2 ){
                        *(((Uint32 *)surface->pixels) + i) = greenPixels[ 9 ];
                        data[ i ].pixel = greenPixels[ 9 ];
                        data[ i ].health = 10;
                } else {
                        *(((Uint32 *)surface->pixels) + i) = bluePixel;
                        data[ i ].pixel = bluePixel;
                        data[ i ].health = 0;
                }
        }
        // check for command line inputs
        if( argc > 1 ){
                RADIUS_SCALE = atoi( argv[ 1 ] );
                if( RADIUS_SCALE <= 0 ){
                        RADIUS_SCALE = 10;
                }
        } else {
                RADIUS_SCALE = 10;
        }
        SDL_UnlockSurface( surface );
        SDL_SaveBMP( surface, "stage2.bmp" );
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if( texture == NULL ){
                fprintf( stderr, "Failed to create texture: %s\n", SDL_GetError());
                return( -1 );
        }

        quit = 0;
        count = 0;
        root = malloc( sizeof( quadType ));
        createTree( root, data, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT );
        while( !quit ){
                while( SDL_PollEvent( &event )){
                        if( event.type == SDL_QUIT ){
                                quit = 1;
                        } else if( event.type == SDL_KEYDOWN ){
                                switch( event.key.keysym.sym ){
                                        case SDLK_UP:
                                                RADIUS_SCALE++;
                                                break;
                                        case SDLK_DOWN:
                                                if( RADIUS_SCALE > 0 ){
                                                        RADIUS_SCALE--;
                                                }
                                                break;
                                        case SDLK_q:
                                        case SDLK_ESCAPE:
                                                quit = 1;
                                                break;
                                }
                        } else if( event.type == SDL_MOUSEBUTTONDOWN ){
                                if( data[ event.button.y * SCREEN_WIDTH + event.button.x ].health > 0 ){
                                        for( int yValue = event.button.y - RADIUS_SCALE * 5; yValue < event.button.y + RADIUS_SCALE * 5; ++yValue ){
                                                for( int xValue = event.button.x - RADIUS_SCALE * 5; xValue < event.button.x + RADIUS_SCALE * 5 ; ++xValue ){
                                                        if( yValue >= 0 && yValue < SCREEN_HEIGHT && xValue >= 0 && xValue < SCREEN_WIDTH ){
                                                                health = data[ yValue * SCREEN_WIDTH + xValue ].health;
                                                                radius = (int)sqrt( pow( xValue - event.button.x, 2 ) + pow( yValue - event.button.y, 2 ));
                                                                if( radius <= RADIUS_SCALE ){
                                                                        health = 0;
                                                                } else if( radius <= RADIUS_SCALE * 2 ){
                                                                        health -= 8;
                                                                } else if( radius <= RADIUS_SCALE * 3 ){
                                                                        health -= 5;
                                                                } else if( radius <= RADIUS_SCALE * 4 ){
                                                                        health -= 2;
                                                                } else if( radius <= RADIUS_SCALE * 5 ){
                                                                        health -= 1;
                                                                } 
                                                                if( health < 0 ){
                                                                        health = 0;
                                                                }
                                                                data[ yValue * SCREEN_WIDTH + xValue ].health = health;
                                                                if( health > 0 ){
                                                                        data[ yValue * SCREEN_WIDTH + xValue ].pixel = greenPixels[ health - 1 ];
                                                                } else {
                                                                        data[ yValue * SCREEN_WIDTH + xValue ].pixel = bluePixel;
                                                                }
                                                        }
                                                }
                                        }
                                        updateTree( root, data, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT );
                                        updateSurface( root, data, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, surface );
                                        SDL_DestroyTexture( texture );
                                        texture = SDL_CreateTextureFromSurface( renderer, surface );
                                        if( texture == NULL ){
                                                fprintf( stderr, "Failed to recreate texture: %s\n", SDL_GetError());
                                                return( -1 );
                                        }
                                }
                        }
                }
                SDL_RenderCopy( renderer, texture, NULL, NULL );
                SDL_RenderPresent( renderer );
                SDL_Delay( DELAY );
                SDL_RenderClear( renderer );
        }
        return( EXIT_SUCCESS );
}

/* 
 * Name: createTree
 * Desc: Creates the quadtree 
 * Args: 
 * 	quadType *root - the root of the tree.
 * 	environmentData *data - the data of that pixel location.
 * 	int x - the starting x pixel.
 * 	int y - the starting y pixel.
 * 	int w - the width of the quad.
 * 	int h - the height of the quad.
 * 	int maxW - the max width of the environment;
 * 	int maxH - the max height of the environment;
 *
 */
int createTree( quadType *root, environmentData *data, int x, int y, int w, int h, int maxW, int maxH ){
        int count;
        int split;

        count = 0;
        split = 0;
        if( root == NULL ){
                return( -1 );
        } else {
                for( int yValue = 0; yValue < h; ++yValue ){
                        for( int xValue = 0; xValue < w - 1; ++xValue ){
                                if( data[ y * maxW + x + yValue * maxW + xValue ].health != data[ y * maxW + x + yValue * maxW + xValue + 1 ].health ){
                                        split = 1;
                                }
                        }
                }
                if( split == 0 ){
                        root->health = data[ y * maxW + x ].health;
                        root->topLeft = NULL;
                        root->bottomLeft = NULL;
                        root->topRight = NULL;
                        root->bottomRight = NULL;
                        count = 1;
                } else {
                        root->topLeft = malloc( sizeof( quadType ));
                        if( root->topLeft == NULL ){
                                perror( "ERROR" );
                                exit( -1 );
                        }
                        root->topLeft->topLeft = NULL;
                        root->topLeft->bottomLeft = NULL;
                        root->topLeft->topRight = NULL;
                        root->topLeft->bottomRight = NULL;
                        count += createTree( root->topLeft, data, x, y, w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        root->bottomLeft = malloc( sizeof( quadType ));
                        if( root->bottomLeft == NULL ){
                                perror( "ERROR" );
                                exit( -1 );
                        }
                        root->bottomLeft->topLeft = NULL;
                        root->bottomLeft->bottomLeft = NULL;
                        root->bottomLeft->topRight = NULL;
                        root->bottomLeft->bottomRight = NULL;
                        count += createTree( root->bottomLeft, data, x, y + ( h / 2 ), w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        root->topRight = malloc( sizeof( quadType ));
                        if( root->topRight == NULL ){
                                perror( "ERROR" );
                                exit( -1 );
                        }
                        root->topRight->topLeft = NULL;
                        root->topRight->bottomLeft = NULL;
                        root->topRight->topRight = NULL;
                        root->topRight->bottomRight = NULL;
                        count += createTree( root->topRight, data, x + ( w / 2 ), y, w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        root->bottomRight = malloc( sizeof( quadType ));
                        if( root->bottomRight == NULL ){
                                perror( "ERROR" );
                                exit( -1 );
                        }
                        root->bottomRight->topLeft = NULL;
                        root->bottomRight->bottomLeft = NULL;
                        root->bottomRight->topRight = NULL;
                        root->bottomRight->bottomRight = NULL;
                        count += createTree( root->bottomRight, data, x + ( w / 2 ), y + ( h / 2 ), w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        root->health = -1;
                }
        }

        return( count );
}

/* 
 * Name: updateTree
 * Desc: Updates the existing tree. 
 * Args: 
 * 	quadType *root - the root of the tree.
 */
int updateTree( quadType *root, environmentData *data, int x, int y, int w, int h, int maxW, int maxH ){
        int count;
        int split;

        count = 0;
        split = 0;
        if( root == NULL ){
                return( -1 );
        } else {
                for( int yValue = 0; yValue < h; ++yValue ){
                        for( int xValue = 0; xValue < w - 1; ++xValue ){
                                if( data[ y * maxW + x + yValue * maxW + xValue ].health !=
                                                data[ y * maxW + x + yValue * maxW + xValue + 1 ].health ){
                                        split = 1;
                                }
                        }
                }
                if( split == 0 ){
                        root->health = data[ y * maxW + x ].health;
                        if( root->topLeft != NULL ){
                                freeTree( root->topLeft );
                                root->topLeft = NULL;
                        }
                        if( root->bottomLeft != NULL ){
                                freeTree( root->bottomLeft );
                                root->bottomLeft = NULL;
                        }
                        if( root->topRight != NULL ){
                                freeTree( root->topRight );
                                root->topRight = NULL;
                        }
                        if( root->bottomRight != NULL ){
                                freeTree( root->bottomRight );
                                root->bottomRight = NULL;
                        }
                        count = 1;
                } else {
                        if( root->topLeft == NULL ){
                                root->topLeft = malloc( sizeof( quadType ));
                                if( root->topLeft == NULL ){
                                        perror( "ERROR" );
                                        exit( -1 );
                                }
                                root->topLeft->topLeft = NULL;
                                root->topLeft->bottomLeft = NULL;
                                root->topLeft->topRight = NULL;
                                root->topLeft->bottomRight = NULL;
                                count += createTree( root->topLeft, data, x, y, w / 2 + h % 2, h / 2 + h % 2, maxW, maxH );
                        } else {
                                count += updateTree( root->topLeft, data, x, y, w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        }
                        if( root->bottomLeft == NULL ){
                                root->bottomLeft = malloc( sizeof( quadType ));
                                if( root->bottomLeft == NULL ){
                                        perror( "ERROR" );
                                        exit( -1 );
                                }
                                root->bottomLeft->topLeft = NULL;
                                root->bottomLeft->bottomLeft = NULL;
                                root->bottomLeft->topRight = NULL;
                                root->bottomLeft->bottomRight = NULL;
                                count += createTree( root->bottomLeft, data, x, y + ( h / 2 ),
                                                w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        } else {
                                count += updateTree( root->bottomLeft, data, x, y + ( h / 2 ),
                                                w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        }
                        if( root->topRight == NULL ){
                                root->topRight = malloc( sizeof( quadType ));
                                if( root->topRight == NULL ){
                                        perror( "ERROR" );
                                        exit( -1 );
                                }
                                root->topRight->topLeft = NULL;
                                root->topRight->bottomLeft = NULL;
                                root->topRight->topRight = NULL;
                                root->topRight->bottomRight = NULL;
                                count += createTree( root->topRight, data, x + ( w / 2 ), y,
                                                w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        } else {
                                count += updateTree( root->topRight, data, x + ( w / 2 ), y,
                                                w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        }
                        if( root->bottomRight == NULL ){
                                root->bottomRight = malloc( sizeof( quadType ));
                                if( root->bottomRight == NULL ){
                                        perror( "ERROR" );
                                        exit( -1 );
                                }
                                root->bottomRight->topLeft = NULL;
                                root->bottomRight->bottomLeft = NULL;
                                root->bottomRight->topRight = NULL;
                                root->bottomRight->bottomRight = NULL;
                                count += createTree( root->bottomRight, data, x + ( w / 2 ),
                                                y + ( h / 2 ), w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        } else {
                                count += updateTree( root->bottomRight, data, x + ( w / 2 ),
                                                y + ( h / 2 ), w / 2 + w % 2, h / 2 + h % 2, maxW, maxH );
                        }
                        root->health = -1;
                }
        }

        return( count );
}

/* 
 * Name: updateSurface
 * Desc: Updates the surface pixel information 
 * Args: 
 * 	quadType *root - the root of the tree.
 * 	SDL_Surface *surface - the surface.
 */
int updateSurface( quadType *root, environmentData *data, int x, int y, int w, int h, int maxW, int maxH, SDL_Surface *surface ){
        int count;
        int split;

        count = 0;
        split = 0;
        if( root == NULL ){
                return( -1 );
        } else if( root->health == -1 ){
                if( root->topLeft != NULL ){
                        count += updateSurface( root->topLeft, data, x, y, w / 2 + w % 2, h / 2 + h % 2, maxW, maxH, surface );
                } 
                if( root->bottomLeft != NULL ){
                        count += updateSurface( root->bottomLeft, data, x, y + ( h / 2 ), w / 2 + w % 2, h / 2 + h % 2, maxW, maxH, surface );
                }
                if( root->topRight != NULL ){
                        count += updateSurface( root->topRight, data, x + ( w / 2 ), y, w / 2 + w % 2, h / 2 + h % 2, maxW, maxH, surface );
                }
                if( root->bottomRight != NULL ){
                        count += updateSurface( root->bottomRight, data, x + ( w / 2 ), y + ( h / 2 ), w / 2 + w % 2, h / 2 + h % 2, maxW, maxH, surface );
                }
                root->health = -1;
        } else {
                for( int yValue = 0; yValue < h; ++yValue ){
                        for( int xValue = 0; xValue < w; ++xValue ){
                                *(((Uint32 *)surface->pixels) + y * maxW + x + yValue * maxW + xValue) = 
                                        data[ y * maxW + x + yValue * maxW + xValue ].pixel;
                        }
                }
        }

        return( count );
}

void freeTree( quadType *root ){
        if( root != NULL ){
                freeTree( root->topLeft );
                freeTree( root->bottomLeft );
                freeTree( root->topRight );
                freeTree( root->bottomRight );
                free( root );
        }
}
