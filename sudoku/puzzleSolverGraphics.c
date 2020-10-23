/*
 * Name: puzzleSolverGraphics.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A GUI for the puzzleSolver.exe 
 * Vers: 1.0.0 05/02/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <SDL2/sdl.h>
#include <string.h>
#include <process.h>

#define BOARD_START_X 65
#define BOARD_START_Y 50
#define TILE_SIZE 41
#define BORDER_WIDTH 1

typedef struct {
        SDL_Rect gridProp;
        int value;
} boardType;

int clearBoard( boardType board[ 81 ] );
int setBoardGrid( boardType board[ 81 ] );
int mouseOver( int x, int y, SDL_Rect box );
int writeBoard( char *filename, boardType box[ 81 ] );
int readBoard( char *filename, boardType box[ 81 ] );

int main( int argc, char **argv ){
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Color white;
        SDL_Color black;
        SDL_Color highlightColor;
        SDL_Event event;
        SDL_Rect outerBorder;
        SDL_Rect innerBorder;
        SDL_Rect numSrc[ 10 ];
        SDL_Surface *surface;
        SDL_Texture *numbers;
        SDL_Texture *boardGrid;
        boardType highlight;
        boardType board[ 81 ];
        int quit;
        int mousex;
        int mousey;
        int spaceSelected;
        int debug;

        if( argc > 1 ){
                debug = 1;
        } else {
                debug = 0;
        }

        white.r = 255;
        white.g = 255;
        white.b = 255;
        white.a = 255;

        black.r = 0;
        black.g = 0;
        black.b = 0;
        black.a = 255;

        highlightColor.r = 0;
        highlightColor.g = 0;
        highlightColor.b = 245;
        highlightColor.a = 65;

        highlight.gridProp.x = BOARD_START_X + 2 * BORDER_WIDTH;
        highlight.gridProp.y = BOARD_START_Y + 2 * BORDER_WIDTH;
        highlight.gridProp.w = TILE_SIZE + 1 * BORDER_WIDTH;
        highlight.gridProp.h = TILE_SIZE + 1 * BORDER_WIDTH;

        outerBorder.x = BOARD_START_X;
        outerBorder.y = BOARD_START_Y;
        outerBorder.w = BORDER_WIDTH + 9 * ( TILE_SIZE + 2 * BORDER_WIDTH );
        outerBorder.h = BORDER_WIDTH + 9 * ( TILE_SIZE + 2 * BORDER_WIDTH );

        setBoardGrid( board );
        clearBoard( board );
        for( int i = 0; i < 10; ++i ){
                numSrc[ i ].x = ( i % 10 ) * 34;
                numSrc[ i ].y = 0;
                numSrc[ i ].w = 33;
                numSrc[ i ].h = 37;
        }
        window = SDL_CreateWindow( "Sudoku Solver",
                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        640, 480,
                        0 );
        renderer = SDL_CreateRenderer( window, -1, 0 );
        SDL_SetRenderDrawColor( renderer, white.r, white.g, white.b, white.a );
        SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );

        // load numbers
        surface = SDL_LoadBMP( "numbers.bmp" );
        SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ));
        numbers = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_FreeSurface( surface );

        // load grid
        surface = SDL_LoadBMP( "board.bmp" );
        boardGrid = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_FreeSurface( surface );
        
        quit = 0;
        highlight.value = 0;
        while( !quit ){
                while( SDL_PollEvent( &event )){
                        if( event.type == SDL_QUIT ){
                                quit = 1;
                        } else if( event.type == SDL_KEYDOWN ){
                                if( debug ){
                                        switch( event.key.keysym.sym ){
                                                case SDLK_q:
                                                case SDLK_ESCAPE:
                                                        quit = 1;
                                                        break;
                                                case SDLK_PLUS:
                                                case SDLK_EQUALS:
                                                        highlight.gridProp.w += 1;
                                                        highlight.gridProp.h += 1;
                                                        break;
                                                case SDLK_MINUS:
                                                        highlight.gridProp.w -= 1;
                                                        highlight.gridProp.h -= 1;
                                                        break;
                                                case SDLK_UP:
                                                        highlight.gridProp.y -= 1;
                                                        break;
                                                case SDLK_DOWN:
                                                        highlight.gridProp.y += 1;
                                                        break;
                                                case SDLK_RIGHT:
                                                        highlight.gridProp.x += 1;
                                                        break;
                                                case SDLK_LEFT:
                                                        highlight.gridProp.x -= 1;
                                                        break;
                                                case SDLK_p:
                                                        printf( "%d, %d, %d, %d\n", 
                                                                        highlight.gridProp.x,
                                                                        highlight.gridProp.y,
                                                                        highlight.gridProp.w,
                                                                        highlight.gridProp.h );
                                                        break;
                                        }
                                } else {
                                        switch( event.key.keysym.sym ){
                                                case SDLK_q:
                                                case SDLK_ESCAPE:
                                                        quit = 1;
                                                        break;
                                                case SDLK_x:
                                                        clearBoard( board );
                                                        break;
                                                case SDLK_DELETE:
                                                case SDLK_KP_PERIOD:
                                                case SDLK_BACKSPACE:
                                                        if( spaceSelected >= 0 ){
                                                                board[ spaceSelected ].value = 0;
                                                        }
                                                        break;
                                                case SDLK_SPACE:
                                                        writeBoard( "input.board", board );
                                                        system( "puzzleSolver.exe input.board answer.board" );
                                                        readBoard( "answer.board", board );
                                                        break;
                                                case SDLK_1:
                                                case SDLK_KP_1:
                                                        if( spaceSelected >= 0 ){
                                                                board[ spaceSelected ].value = 1;
                                                        }
                                                        break;
                                                case SDLK_2:
                                                case SDLK_KP_2:
                                                        if( spaceSelected >= 0 ){
                                                                board[ spaceSelected ].value = 2;
                                                        }
                                                        break;
                                                case SDLK_3:
                                                case SDLK_KP_3:
                                                        if( spaceSelected >= 0 ){
                                                                board[ spaceSelected ].value = 3;
                                                        }
                                                        break;
                                                case SDLK_4:
                                                case SDLK_KP_4:
                                                        if( spaceSelected >= 0 ){
                                                                board[ spaceSelected ].value = 4;
                                                        }
                                                        break;
                                                case SDLK_5:
                                                case SDLK_KP_5:
                                                        if( spaceSelected >= 0 ){
                                                                board[ spaceSelected ].value = 5;
                                                        }
                                                        break;
                                                case SDLK_6:
                                                case SDLK_KP_6:
                                                        if( spaceSelected >= 0 ){
                                                                board[ spaceSelected ].value = 6;
                                                        }
                                                        break;
                                                case SDLK_7:
                                                case SDLK_KP_7:
                                                        if( spaceSelected >= 0 ){
                                                                board[ spaceSelected ].value = 7;
                                                        }
                                                        break;
                                                case SDLK_8:
                                                case SDLK_KP_8:
                                                        if( spaceSelected >= 0 ){
                                                                board[ spaceSelected ].value = 8;
                                                        }
                                                        break;
                                                case SDLK_9:
                                                case SDLK_KP_9:
                                                        if( spaceSelected >= 0 ){
                                                                board[ spaceSelected ].value = 9;
                                                        }
                                                        break;
                                                case SDLK_UP:
                                                        if( spaceSelected >= 9 ){
                                                                spaceSelected -= 9;
                                                                highlight.gridProp.x 
                                                                        = board[ spaceSelected ].gridProp.x;
                                                                highlight.gridProp.y 
                                                                        = board[ spaceSelected ].gridProp.y;
                                                        }
                                                        break;
                                                case SDLK_DOWN:
                                                        if( spaceSelected < 72 ){
                                                                spaceSelected += 9;
                                                                highlight.gridProp.x 
                                                                        = board[ spaceSelected ].gridProp.x;
                                                                highlight.gridProp.y 
                                                                        = board[ spaceSelected ].gridProp.y;
                                                        }
                                                        break;
                                                case SDLK_RIGHT:
                                                        if( spaceSelected % 9 < 8 ){
                                                                spaceSelected += 1;
                                                                highlight.gridProp.x 
                                                                        = board[ spaceSelected ].gridProp.x;
                                                                highlight.gridProp.y 
                                                                        = board[ spaceSelected ].gridProp.y;
                                                        }
                                                        break;
                                                case SDLK_LEFT:
                                                        if( spaceSelected % 9 > 0 ){
                                                                spaceSelected -= 1;
                                                                highlight.gridProp.x 
                                                                        = board[ spaceSelected ].gridProp.x;
                                                                highlight.gridProp.y 
                                                                        = board[ spaceSelected ].gridProp.y;
                                                        }
                                                        break;
                                        }
                                }
                        } else if( event.type == SDL_MOUSEBUTTONDOWN ){
                                mousex = event.button.x;
                                mousey = event.button.y;
                                for( int i = 0; i < 81; ++i ){
                                        if( mouseOver( mousex, mousey, board[ i ].gridProp )){
                                                highlight.gridProp.x = board[ i ].gridProp.x;
                                                highlight.gridProp.y = board[ i ].gridProp.y;
                                                highlight.gridProp.w = board[ i ].gridProp.w;
                                                highlight.gridProp.h = board[ i ].gridProp.h;
                                                highlight.value = 1;
                                                spaceSelected = i;
                                                break;
                                        } else {
                                                highlight.value = 0;
                                                spaceSelected = -1;
                                        }
                                }
                        }
                }
                SDL_RenderClear( renderer );
                //SDL_SetRenderDrawColor( renderer, black.r, black.g, black.b, black.a );
                //SDL_RenderFillRect( renderer, &outerBorder );
                SDL_SetRenderDrawColor( renderer, white.r, white.g, white.b, white.a );
                SDL_RenderCopy( renderer, boardGrid, NULL, &outerBorder );
                for( int i = 0; i < 81; ++i ){
                        //SDL_RenderFillRect( renderer, &(board[ i ].gridProp) );
                        if( board[ i ].value > 0 ){
                           SDL_RenderCopy( renderer, numbers, &(numSrc[ board[ i ].value ]),
                           &(board[ i ].gridProp));
                        }
                }
                if( highlight.value == 1 ){
                        SDL_SetRenderDrawColor( renderer, highlightColor.r, 
                                        highlightColor.g, highlightColor.b, highlightColor.a );
                        SDL_RenderFillRect( renderer, &highlight.gridProp );
                }
                SDL_SetRenderDrawColor( renderer, white.r, white.g, white.b, white.a );
                SDL_RenderPresent( renderer );
                SDL_Delay( 100 );
        }

        return( EXIT_SUCCESS );
}

int clearBoard( boardType board[ 81 ] ){
        for( int i = 0; i < 81; ++i ){
                board[ i ].value = 0;
                //board[ i ].value = ( i + 1) % 10;
        }
}

int setBoardGrid( boardType board[ 81 ] ){
        for( int i = 0; i < 81; ++i ){
                board[ i ].gridProp.x = BOARD_START_X + 2 + 
                        ( i % 9 ) * ( TILE_SIZE + 1 * BORDER_WIDTH ) + 
                        3 * (( i % 9 ) / 3 ) + 2 * (( i % 9 ) / 4 ) - 1 * ( i % 9 / 8 );
                board[ i ].gridProp.y = BOARD_START_Y + 2 + 
                        ( i / 9 ) * ( TILE_SIZE + 1 * BORDER_WIDTH ) + 
                        1 * ( i / 18 ) + 1 * ( i / 45 ) + 2 * ( i / 54 );
                board[ i ].gridProp.w = TILE_SIZE - 0 * BORDER_WIDTH;
                board[ i ].gridProp.h = TILE_SIZE - 0 * BORDER_WIDTH;
        }
        return( 0 );
}

int mouseOver( int x, int y, SDL_Rect box ){
        int results;

        results = 0;
        if( x <= box.x + box.w && x >= box.x && 
                        y <= box.y + box.h && y >= box.y ){
                results = 1;
        }

        return( results );
}

int writeBoard( char *filename, boardType board[ 81 ] ){
        FILE *file;

        file = fopen( filename, "w" );
        for( int i = 0; i < 81; ++i ){
                fprintf( file, "%d", board[ i ].value );
                if(( i + 1 ) % 9 == 0 ){
                        fprintf( file, "\n" );
                } else {
                        fprintf( file, "," );
                }
        }

        fclose( file );
        return( 0 );
}

int readBoard( char *filename, boardType board[ 81 ] ){
        FILE *file;

        file = fopen( filename, "r" );
        for( int i = 0; i < 81; ++i ){
                fscanf( file, "%d%*c", &(board[ i ].value));
        }
        fclose( file );

        return( 0 );
}
