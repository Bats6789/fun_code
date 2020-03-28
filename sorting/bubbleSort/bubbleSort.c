/*
 * Name: bubbleSort.c
 * Auth: Blake Wingard
 * Desc: Performs a live demonstration of a bubble sort.
 * Vers: 1.0.1 03/13/2020 CBW - Added circles.
 * Vers: 1.0.0 03/10/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define RADIUS 50
#define DELAY 25
#define BOX_DELAY 10

typedef struct {
	SDL_Texture *numberTexture;
	SDL_Rect numberRect;
	SDL_Rect dst;
	SDL_Color color;
	int radius;
	int number;
} circlePropType;

int drawCircle( circlePropType circleProp, SDL_Renderer *renderer );
int assignCircles( circlePropType circleProp[ 7 ], SDL_Renderer * renderer, TTF_Font *font, int circleX, int circleY );
int setCircleNum( circlePropType *circleProp, SDL_Renderer *renderer, TTF_Font *font, int num );
int circleEqual( circlePropType *dstCircle, circlePropType *srcCircle );

int main( int argc, char **argv ){
	int quit;
	int showBox;
	int boxCompareNum;
	int boxDelay;
	int swap;
	int swapStep;
	int stopIndex;
	int run;
	int circleX;
	int circleY;
	int lctrl;
	int rctrl;
	int delay;

	SDL_DisplayMode mode;
	SDL_Color graphColor;
	SDL_Color backgroundColor;
	SDL_Color boxColor;
	SDL_Rect box;
	SDL_Rect tmpBox;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
	TTF_Font *font;
	circlePropType circleProp[ 7 ];
	circlePropType tmpCircle;

	// start SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ){
		SDL_Log( "Unable to initialize SDL: %s", SDL_GetError());
		return( EXIT_FAILURE );
	}
	//SDL_Log( "Initialized successfully" );
	atexit( SDL_Quit );

	// start TTF
	if(TTF_Init() != 0 ) {
		SDL_Log("TTF_Init: %s\n", TTF_GetError());
		return( EXIT_FAILURE );
	}
	//SDL_Log( "TTF initialized successfully" );
	atexit( TTF_Quit );

	// basic SDL setup
	if( SDL_GetDesktopDisplayMode( 0, &mode ) != 0 ){
		SDL_Log( "Failed to get displayMode: %s", SDL_GetError());
		return( EXIT_FAILURE );
	}
	//SDL_Log( "Got the desktop mode " );

	if( SDL_CreateWindowAndRenderer( mode.w, mode.h, 
				SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer )){
		SDL_Log( "Couldn't create window and renderer: %s", SDL_GetError());
		return( EXIT_FAILURE );
	}
	circleX = mode.w / 2 - 7 * RADIUS;
	circleY = mode.h / 2 - RADIUS;
	//SDL_Log( "window and renderer created successfully" );

	// set up text information.
	font = TTF_OpenFont( "times.ttf", 30 );
	if( font == NULL ){
		SDL_Log( "Couldn't open times.ttf font: %s", SDL_GetError());
		return( EXIT_FAILURE );
	}

	// set random number seed
	srand( time( 0 ));

	// assign circle properties
	assignCircles( circleProp, renderer, font, circleX, circleY );
	tmpCircle.dst.x = circleX + 2 * RADIUS * 3;
	tmpCircle.dst.y = circleY - 2 * 2 * RADIUS;
	tmpCircle.dst.w = circleProp[ 0 ].dst.w;
	tmpCircle.dst.h = circleProp[ 0 ].dst.h;
	setCircleNum( &(tmpCircle), renderer, font, 22 );
	tmpBox.x = tmpCircle.dst.x;
	tmpBox.y = tmpCircle.dst.y;
	tmpBox.w = tmpCircle.dst.w;
	tmpBox.h = tmpCircle.dst.h;

	// assign Box size
	box.w = 2 * 2 * RADIUS;
	box.h = 2 * RADIUS;

	// assign colors
	// black
	backgroundColor.r = 0;
	backgroundColor.g = 0;
	backgroundColor.b = 0;
	backgroundColor.a = 255;

	// grey
	boxColor.r = 128;
	boxColor.g = 128;
	boxColor.b = 128;
	boxColor.a = 255;

	quit = 0;
	showBox = 0;
	swap = 0;
	swapStep = 3;
	stopIndex = 7;
	boxCompareNum = 0;
	run = 0;
	boxDelay = BOX_DELAY;
	lctrl = 0;
	rctrl = 0;
	delay = DELAY;

	while( !quit ){
		// handles events
		while( SDL_PollEvent( &event )){
			if( event.type == SDL_QUIT ){
				quit = 1;
			} else if( event.type == SDL_KEYDOWN ){
				switch( event.key.keysym.sym ){
					case SDLK_q:
					case SDLK_ESCAPE:
						quit = 1;
						break;
					case SDLK_SPACE:
						if( run ){
							// ignore
						} else if( showBox == 0 && swap != 1 ){
							if( stopIndex == 1 ){
								// reset
								assignCircles( circleProp, renderer, font, circleX, circleY );
								showBox = 0;
								swap = 0;
								swapStep = 3;
								stopIndex = 7;
								boxCompareNum = 0;
								run = 0;
								delay = DELAY;
							} else {
								showBox = 1;
							}
						} else if( swap != 1 ){
							if( circleProp[ boxCompareNum ].number > circleProp[ boxCompareNum + 1 ].number || swapStep < 3 ){
								showBox = -1;
								swap = 1;
							} else {
								++boxCompareNum;
								if( boxCompareNum + 1 == stopIndex ){
									boxCompareNum = 0;
									--stopIndex;
								}
								showBox = 0;
							}
						}
						break;
					case SDLK_RETURN:
					case SDLK_KP_ENTER:
						run = 1;
						break;
					case SDLK_LCTRL:
						lctrl = 1;
						break;
					case SDLK_RCTRL:
						rctrl = 1;
						break;
					case SDLK_w:
						if( lctrl || rctrl ){
							quit = 1;
						}
						break;
					case SDLK_0:
						delay = 0;
						break;
					default:
						// do nothing
						break;
				}
			} else if( event.type == SDL_KEYUP ){
				switch( event.key.keysym.sym ){
					case SDLK_LCTRL:
						lctrl = 0;
						break;
					case SDLK_RCTRL:
						rctrl = 0;
						break;
					default:
						break;
				}
			} else {
			}
		}
		if( run ){
			// perform space action automatically
			if( showBox == 0 && swap != 1 ){
				if( stopIndex == 1 ){
					// stop
					run = 0;
				} else {
					showBox = 1;
				}
			} else if( swap != 1 ){
				if( circleProp[ boxCompareNum ].number > circleProp[ boxCompareNum + 1 ].number || swapStep < 3 ){
					showBox = -1;
					swap = 1;
				} else {
					++boxCompareNum;
					if( boxCompareNum + 1 == stopIndex ){
						boxCompareNum = 0;
						--stopIndex;
					}
					showBox = 0;
				}
			}
		}


		// draw box
		if( showBox == 1 ){
			if( SDL_SetRenderDrawColor( renderer, boxColor.r, boxColor.g, boxColor.b,
						boxColor.a ) != 0 ){
				SDL_Log( "Unable to change color of renderer to gray: %s", 
						SDL_GetError());
				return( EXIT_FAILURE );
			}
			box.x = circleProp[ boxCompareNum ].dst.x;
			box.y = circleProp[ boxCompareNum ].dst.y;
			if( SDL_RenderFillRect( renderer, &box ) != 0 ){
				SDL_Log( "Failed to draw box: %s", SDL_GetError());
				return( EXIT_FAILURE );
			}
			if( SDL_SetRenderDrawColor( renderer, backgroundColor.r, backgroundColor.g,
						backgroundColor.b, backgroundColor.a ) != 0 ){
				SDL_Log( "Unable to change color of renderer: %s", SDL_GetError());
				return( EXIT_FAILURE );
			}
		}
		if( SDL_SetRenderDrawColor( renderer, boxColor.r, boxColor.g, boxColor.b,
					boxColor.a ) != 0 ){
			SDL_Log( "Unable to change color of renderer to gray: %s", 
					SDL_GetError());
			return( EXIT_FAILURE );
		}
		if( SDL_RenderDrawRect( renderer, &tmpBox ) != 0 ){
			SDL_Log( "Failed to draw box: %s", SDL_GetError());
			return( EXIT_FAILURE );
		}
		if( SDL_SetRenderDrawColor( renderer, backgroundColor.r, backgroundColor.g,
					backgroundColor.b, backgroundColor.a ) != 0 ){
			SDL_Log( "Unable to change color of renderer: %s", SDL_GetError());
			return( EXIT_FAILURE );
		}

		// swap circles
		if( swap ){
			switch( swapStep ){
				case 3:
					--swapStep;
					circleEqual( &tmpCircle, &(circleProp[ boxCompareNum ]) );
					swap = 0;
					break;
				case 2:
					--swapStep;
					circleEqual( &(circleProp[ boxCompareNum ]), 
							&(circleProp[ boxCompareNum + 1 ]) );
					swap = 0;
					break;
				case 1:
					--swapStep;
					circleEqual( &(circleProp[ boxCompareNum + 1 ]), &tmpCircle );
					swap = 0;
					break;
				case 0:
					swapStep = 3;
					showBox = 0;
					swap = 0;
					++boxCompareNum;
					if( boxCompareNum + 1 == stopIndex ){
						boxCompareNum = 0;
						--stopIndex;
					}
					break;
				default:
					break;
			}
		}

		// draw circles
		for( int i = 0; i < 7; ++i ){
			if( SDL_SetRenderDrawColor( renderer, circleProp[ i ].color.r,
						circleProp[ i ].color.g, circleProp[ i ].color.b,
						circleProp[ i ].color.a ) != 0 ){
				SDL_Log( "Unable to change color of renderer to circleProp[ %d ]: %s"
						, i, SDL_GetError());
				return( EXIT_FAILURE );
			}
			drawCircle( circleProp[ i ], renderer );
		}
		if( showBox == -1 ){
			if( SDL_SetRenderDrawColor( renderer, tmpCircle.color.r,
						tmpCircle.color.g, tmpCircle.color.b,
						tmpCircle.color.a ) != 0 ){
				SDL_Log( "Unable to change color of renderer to tmpCircle: %s"
						, SDL_GetError());
				return( EXIT_FAILURE );
			}
			drawCircle( tmpCircle, renderer );
		}

		// display and clear
		if( SDL_SetRenderDrawColor( renderer, backgroundColor.r, backgroundColor.g,
					backgroundColor.b, backgroundColor.a ) != 0 ){
			SDL_Log( "Unable to change color of renderer to background: %s",
					SDL_GetError());
			return( EXIT_FAILURE );
		}
		SDL_RenderPresent( renderer );
		if( delay != 0 ){
			SDL_Delay( delay );
		}
		SDL_RenderClear( renderer );
	}

	return( EXIT_SUCCESS );
}

int drawCircle( circlePropType circleProp, SDL_Renderer *renderer ){
	int centerX;
	int centerY;

	centerX = circleProp.dst.x + circleProp.dst.w / 2;
	centerY = circleProp.dst.y + circleProp.dst.h / 2;

	for( double angle = 0; angle < 360; angle += 0.5 ){
		SDL_RenderDrawLine( renderer, centerX, centerY,
				centerX + RADIUS * cos( angle * M_PI / 180.0 ),
				centerY + RADIUS * sin( angle * M_PI / 180.0 ));
	}
	if( SDL_RenderCopy( renderer, circleProp.numberTexture, NULL, &(circleProp.numberRect)) < 0 ){
		SDL_Log( "Failed to renderCopy: %s", SDL_GetError());
	}
	return( 0 );
}

int setCircleNum( circlePropType *circleProp, SDL_Renderer *renderer, TTF_Font *font, int num ){
	SDL_Surface *tmpSurface;
	SDL_Color color;
	double shift;
	double scale;
	char number[ 3 ];

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;

	if( num >= 100 ){
		return( -1 );
	} else if( num >= 10 ){
		shift = 0.0;
		scale = 1.0;
	} else {
		shift = 0.15;
		scale = 0.5;
	}

	sprintf( number, "%d", num );
	tmpSurface = TTF_RenderText_Solid( font, number, color );
	if( tmpSurface == NULL ){
		SDL_Log( "tmpSurface failed to create for number %d: %s", num, SDL_GetError());
		return( -1 );
	}
	circleProp->numberTexture = SDL_CreateTextureFromSurface( renderer, tmpSurface );
	if( circleProp->numberTexture == NULL ){
		SDL_Log( "Failed to create Texture for number %d: %s" );
	}
	circleProp->numberRect.x = circleProp->dst.x + 2 * RADIUS * ( 0.25 + shift );
	circleProp->numberRect.y = circleProp->dst.y + 2 * RADIUS * 0.175;
	circleProp->numberRect.w = 2 * RADIUS * 0.5 * scale;
	circleProp->numberRect.h = 2 * RADIUS * 0.6;
	circleProp->number = num;

	free( tmpSurface );
	return( 0 );
}

int circleEqual( circlePropType *dstCircle, circlePropType *srcCircle ){
	dstCircle->numberTexture = 
		srcCircle->numberTexture;
	/*
	   dstCircle->dst.x =
	   srcCircle->dst.x;
	   dstCircle->dst.y =
	   srcCircle->dst.y;
	   dstCircle->dst.w =
	   srcCircle->dst.w;
	   dstCircle->dst.h =
	   srcCircle->dst.h;
	   */
	dstCircle->color.r = 
		srcCircle->color.r;
	dstCircle->color.g = 
		srcCircle->color.g;
	dstCircle->color.b = 
		srcCircle->color.b;
	dstCircle->color.a = 
		srcCircle->color.a;
	/*
	   dstCircle->numberRect.x =
	   srcCircle->numberRect.x;
	   dstCircle->numberRect.y =
	   srcCircle->numberRect.y;
	   */
	if( srcCircle->number < 10 && dstCircle->number >= 10 ){
		dstCircle->numberRect.x = dstCircle->numberRect.x + 2 * RADIUS * 0.15;
	} else if( srcCircle->number >= 10 && dstCircle->number < 10 ){
		dstCircle->numberRect.x = dstCircle->numberRect.x - 2 * RADIUS * 0.15;
	}
	dstCircle->numberRect.w =
		srcCircle->numberRect.w;
	dstCircle->numberRect.h =
		srcCircle->numberRect.h;
	dstCircle->number =
		srcCircle->number;
	return( 0 );
}

int assignCircles( circlePropType circleProp[ 7 ], SDL_Renderer * renderer, TTF_Font *font, int circleX, int circleY ){
	// location
	for( int i = 0; i < 7; ++i ){
		circleProp[ i ].dst.x = circleX + 2 * RADIUS * i;
		circleProp[ i ].dst.y = circleY;
		circleProp[ i ].dst.h = 2 * RADIUS;
		circleProp[ i ].dst.w = 2 * RADIUS;
		circleProp[ i ].radius = RADIUS;
	}

	// colors
	// red
	circleProp[ 0 ].color.r = 255;
	circleProp[ 0 ].color.g = 0;
	circleProp[ 0 ].color.b = 0;
	circleProp[ 0 ].color.a = 255;
	setCircleNum( &(circleProp[ 0 ]), renderer, font, rand() % 100 );

	// orange
	circleProp[ 1 ].color.r = 255;
	circleProp[ 1 ].color.g = 165;
	circleProp[ 1 ].color.b = 0;
	circleProp[ 1 ].color.a = 255;
	setCircleNum( &(circleProp[ 1 ]), renderer, font, rand() % 100 );

	// yellow
	circleProp[ 2 ].color.r = 255;
	circleProp[ 2 ].color.g = 255;
	circleProp[ 2 ].color.b = 0;
	circleProp[ 2 ].color.a = 255;
	setCircleNum( &(circleProp[ 2 ]), renderer, font, rand() % 100 );

	// green
	circleProp[ 3 ].color.r = 0;
	circleProp[ 3 ].color.g = 255;
	circleProp[ 3 ].color.b = 0;
	circleProp[ 3 ].color.a = 255;
	setCircleNum( &(circleProp[ 3 ]), renderer, font, rand() % 100 );

	// blue
	circleProp[ 4 ].color.r = 0;
	circleProp[ 4 ].color.g = 0;
	circleProp[ 4 ].color.b = 255;
	circleProp[ 4 ].color.a = 255;
	setCircleNum( &(circleProp[ 4 ]), renderer, font, rand() % 100 );

	// indigo
	circleProp[ 5 ].color.r = 75;
	circleProp[ 5 ].color.g = 0;
	circleProp[ 5 ].color.b = 130;
	circleProp[ 5 ].color.a = 255;
	setCircleNum( &(circleProp[ 5 ]), renderer, font, rand() % 100 );

	// voilet
	circleProp[ 6 ].color.r = 128;
	circleProp[ 6 ].color.g = 0;
	circleProp[ 6 ].color.b = 128;
	circleProp[ 6 ].color.a = 255;
	setCircleNum( &(circleProp[ 6 ]), renderer, font, rand() % 100 );

	return( 0 );
}
