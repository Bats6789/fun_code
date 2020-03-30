/*
 * Name: bubbleSort.c
 * Auth: Blake Wingard
 * Desc: Performs a live demonstration of a bubble sort.
 * Vers: 1.0.3 03/30/2020 CBW - Added comments for clarity.
 * Vers: 1.0.2 03/28/2020 CBW - Implemented numbers and swapping.
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

typedef struct {
	SDL_Texture *numberTexture;	// the image of the number
	SDL_Rect numberRect;		// the location and size of the number
	SDL_Rect dst;			// the location and size of the circle
	SDL_Color color;		// the color of the circle
	int radius;			// the radius of the circle
	int number;			// the number of the circle
} circlePropType;

int drawCircle( circlePropType circleProp, SDL_Renderer *renderer );
int assignCircles( circlePropType circleProp[ 7 ], SDL_Renderer * renderer, TTF_Font *font, int circleX, int circleY );
int setCircleNum( circlePropType *circleProp, SDL_Renderer *renderer, TTF_Font *font, int num );
int circleEqual( circlePropType *dstCircle, circlePropType *srcCircle );

int main( int argc, char **argv ){
	// standard C variables
	int quit; 			// quit flag
	int showBox; 			// box flag
	int boxCompareNum;		// the first index of the circle being compared
	int swap; 			// swap flag
	int swapStep;			// the current swap step ( 0 - 3 )
	int stopIndex;			// the last index before reset
	int run; 			// run flag
	int circleX;			// the center x value for the circle cluster
	int circleY;			// the center y value for the circle cluster
	int lctrl; 			// flag for left CTRL
	int rctrl; 			// flag for right CTRL
	int delay;			// delay value
	// SDL Variables
	SDL_DisplayMode mode;		// the display mode (used for screen size)
	SDL_Color backgroundColor;	// the background color (black)
	SDL_Color boxColor;		// the box color (gray)
	SDL_Rect box;			// the comparison box
	SDL_Rect tmpBox;		// the box where the temporary circle goes
	SDL_Window *window;		// the window
	SDL_Renderer *renderer;		// the renderer
	SDL_Event event;		// the events
	TTF_Font *font;			// the font
	// My structures
	circlePropType circleProp[ 7 ]; // the circles
	circlePropType tmpCircle;	// the temporary circle

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
	// Centers for the circles
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

	// assign circle properties (x, y, width, height)
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

	// initialize variables before entering the main loop
	quit = 0;
	showBox = 0;
	swap = 0;
	swapStep = 3;
	stopIndex = 7;
	boxCompareNum = 0;
	run = 0;
	lctrl = 0;
	rctrl = 0;
	delay = DELAY;

	// main loop
	while( !quit ){
		// handles events
		while( SDL_PollEvent( &event )){
			// user clicks x or presses alt-f4
			if( event.type == SDL_QUIT ){
				quit = 1;
			// user presses a key
			} else if( event.type == SDL_KEYDOWN ){
				switch( event.key.keysym.sym ){
					case SDLK_q:
					case SDLK_ESCAPE:
						quit = 1;
						break;
					case SDLK_SPACE:
						// pressing space starts next step
						if( run ){
							// ignore space bar
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
							// compares the values of two bubbles
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
					// pressing enter runs the program till finished sorting
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
			// user releases a key
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


		// draw compare box
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
		// draw temp box
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
				// step 1: copy first bubble to temporary bubble
				case 3:
					--swapStep;
					circleEqual( &tmpCircle, &(circleProp[ boxCompareNum ]) );
					swap = 0;
					break;
				// step 2: copy second bubble into first bubble
				case 2:
					--swapStep;
					circleEqual( &(circleProp[ boxCompareNum ]), 
							&(circleProp[ boxCompareNum + 1 ]) );
					swap = 0;
					break;
				// step 3: copy temporary bubble into second bubble
				case 1:
					--swapStep;
					circleEqual( &(circleProp[ boxCompareNum + 1 ]), &tmpCircle );
					swap = 0;
					break;
				// reset steps and increment the comparing index
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
		// draw temp circle
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

/*
 * Name: drawCircle
 * Auth: Blake Wingard
 * Desc: Draws a circle with number inside it.
 * Args:
 * 	circlePropType circleProp - the circle to be drawn.
 * 	SDL_Renderer *renderer - the renderer the circle will be drawn on.
 */
int drawCircle( circlePropType circleProp, SDL_Renderer *renderer ){
	int centerX;
	int centerY;

	centerX = circleProp.dst.x + circleProp.dst.w / 2;
	centerY = circleProp.dst.y + circleProp.dst.h / 2;

	// draw the circle
	for( double angle = 0; angle < 360; angle += 0.5 ){
		SDL_RenderDrawLine( renderer, centerX, centerY,
				centerX + RADIUS * cos( angle * M_PI / 180.0 ),
				centerY + RADIUS * sin( angle * M_PI / 180.0 ));
	}
	// draw the number
	if( SDL_RenderCopy( renderer, circleProp.numberTexture, NULL, &(circleProp.numberRect)) < 0 ){
		SDL_Log( "Failed to renderCopy: %s", SDL_GetError());
	}
	return( 0 );
}

/*
 * Name: setCircleNum
 * Auth: Blake Wingard
 * Desc: Sets the number of the circle
 * Args:
 * 	circlePropType *circleProp - the address of the circle receiving the number
 * 	SDL_Renderer *renderer - the renderer the texture is being applied to
 * 	TTF_Font *font - the font used for the number
 * 	int num - the number being assigned
 */
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

	// number must be less than 100
	if( num >= 100 ){
		return( -1 );
	} else if( num >= 10 ){
		// if the number has two digits than no shifting or scaling is needed
		shift = 0.0;
		scale = 1.0;
	} else {
		// if the number has one digit than shifting and scaling is needed
		shift = 0.15;
		scale = 0.5;
	}

	// render the number into a texture
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
	// assign the drawing properties for the number
	circleProp->numberRect.x = circleProp->dst.x + 2 * RADIUS * ( 0.25 + shift );
	circleProp->numberRect.y = circleProp->dst.y + 2 * RADIUS * 0.175;
	circleProp->numberRect.w = 2 * RADIUS * 0.5 * scale;
	circleProp->numberRect.h = 2 * RADIUS * 0.6;
	// set the circles number
	circleProp->number = num;

	free( tmpSurface );
	return( 0 );
}

/*
 * Name: circleEqual
 * Auth: Blake Wingard
 * Desc: Set srcCircle to dstCircle.
 * Args:
 * 	circlePropType *dstCircle - the destination for data
 * 	circlePropType *srcCircle - the source of data 
 */
int circleEqual( circlePropType *dstCircle, circlePropType *srcCircle ){
	dstCircle->numberTexture = 
		srcCircle->numberTexture;
	// don't copy the actual location of circle, just features.
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
	// x and y might need to be shifted. But not assigned.
	/*
	   dstCircle->numberRect.x =
	   srcCircle->numberRect.x;
	   dstCircle->numberRect.y =
	   srcCircle->numberRect.y;
	   */
	// shift x and y if needed.
	if( srcCircle->number < 10 && dstCircle->number >= 10 ){
		dstCircle->numberRect.x = dstCircle->numberRect.x + 2 * RADIUS * 0.15;
	} else if( srcCircle->number >= 10 && dstCircle->number < 10 ){
		dstCircle->numberRect.x = dstCircle->numberRect.x - 2 * RADIUS * 0.15;
	}
	dstCircle->numberRect.w =
		srcCircle->numberRect.w;
	dstCircle->numberRect.h =
		srcCircle->numberRect.h;
	// set number
	dstCircle->number =
		srcCircle->number;
	return( 0 );
}

/*
 * Name: assignCircles
 * Auth: Blake Wingard
 * Desc: Sets up the seven circles (location, width, height, color, and number)
 * Args:
 * 	circlePropType circleProp[ 7 ] - the circles being assigned to.
 * 	SDL_Renderer *renderer - the renderer the circles will be drawn on.
 * 	TTF_Font *font - the font for the numbers.
 * 	int circleX - the center x value for the circle cluster.
 * 	int circleY - the center y value for the circle cluster.
 */
int assignCircles( circlePropType circleProp[ 7 ], SDL_Renderer * renderer, TTF_Font *font, int circleX, int circleY ){
	// location
	for( int i = 0; i < 7; ++i ){
		// properties (location, height, width, radius )
		circleProp[ i ].dst.x = circleX + 2 * RADIUS * i;
		circleProp[ i ].dst.y = circleY;
		circleProp[ i ].dst.h = 2 * RADIUS;
		circleProp[ i ].dst.w = 2 * RADIUS;
		circleProp[ i ].radius = RADIUS;
		// numbers
		setCircleNum( &(circleProp[ i ]), renderer, font, rand() % 100 );
	}

	// colors
	// red
	circleProp[ 0 ].color.r = 255;
	circleProp[ 0 ].color.g = 0;
	circleProp[ 0 ].color.b = 0;
	circleProp[ 0 ].color.a = 255;

	// orange
	circleProp[ 1 ].color.r = 255;
	circleProp[ 1 ].color.g = 165;
	circleProp[ 1 ].color.b = 0;
	circleProp[ 1 ].color.a = 255;

	// yellow
	circleProp[ 2 ].color.r = 255;
	circleProp[ 2 ].color.g = 255;
	circleProp[ 2 ].color.b = 0;
	circleProp[ 2 ].color.a = 255;

	// green
	circleProp[ 3 ].color.r = 0;
	circleProp[ 3 ].color.g = 255;
	circleProp[ 3 ].color.b = 0;
	circleProp[ 3 ].color.a = 255;

	// blue
	circleProp[ 4 ].color.r = 0;
	circleProp[ 4 ].color.g = 0;
	circleProp[ 4 ].color.b = 255;
	circleProp[ 4 ].color.a = 255;

	// indigo
	circleProp[ 5 ].color.r = 75;
	circleProp[ 5 ].color.g = 0;
	circleProp[ 5 ].color.b = 130;
	circleProp[ 5 ].color.a = 255;

	// violet
	circleProp[ 6 ].color.r = 128;
	circleProp[ 6 ].color.g = 0;
	circleProp[ 6 ].color.b = 128;
	circleProp[ 6 ].color.a = 255;

	return( 0 );
}
