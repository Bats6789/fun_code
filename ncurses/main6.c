#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

#define DELAY 30000
#define SCALE 1000
#define ESC   27
#define DEL   127

char ch;
int wait = 0;

void *getUserInput( void *args );
void moveWord( int **location[ 2 ], int n );

int main( int argc, char **argv ){
	int x;
	int y;
	int n;
	int color;
	int maxY;
	int maxX;
	int nextX;
	int direction;
	int quit;
	int scale;
	int printHelp;
	int cycle;
	int **location;
	char *string;
	char lastChar;
	pthread_t thread;

	x = 0;
	y = 0;
	n = 0;
	color = 0;
	maxY = 0;
	maxX = 0;
	nextX = 0;
	direction = 1;
	ch = ' ';
	quit = 0;
	scale = 1;
	printHelp = 1;
	lastChar = ' ';
	cycle = 0;
	string = malloc( sizeof( char ) * SCALE * scale );
	string[ 0 ] = '\0';

	initscr();
	if( has_colors() == FALSE ){
		endwin();
		printf( "No color :(\n" );
		return( 1 );
	}
	start_color();
	init_pair( 1, COLOR_RED, COLOR_BLACK );
	init_pair( 2, COLOR_BLUE, COLOR_YELLOW );
	init_pair( 3, COLOR_WHITE, COLOR_MAGENTA );
	noecho();
	curs_set(FALSE);
	getmaxyx( stdscr, maxY, maxX );
	mvprintw(( maxY - 1 )/2, ( maxX - 20 )/2, "Please enter a word: " );
	refresh();
	while( ch != '\n' && !quit ){
		clear();
		mvprintw(( maxY - 1 )/2, ( maxX - 20 )/2, "Please enter a word: %s", string );
		refresh();
		ch = getch();
		if( ch == DEL ){
			if( n > 0 ){
				--n;
				string[ n ] = '\0';
			}
		} else if( ch == ESC ){
			quit = 1;
		} else if( ch != '\n' ){
			string[ n ] = ch;
			++n;
		}
		if( n % SCALE == 0 ){
			++scale;
			string = realloc( string, sizeof( char ) * scale * SCALE );
		}
		if( ch != '\n' ){
			string[ n ] = '\0';
		}

	}
	location = malloc( sizeof( int * ) * n );
	for( int i = 0; i < n; ++i ){
		location[ i ] = malloc( sizeof( int ) * 2 );
		if( i / maxX % 2 == 0 ){
			location[ i ][ 0 ] = i % maxX;
		} else {
			location[ i ][ 0 ] = maxX - ( i % maxX ) - 1;
		}
		location[ i ][ 1 ] = i / ( maxX );
	}
	ch = ' ';

	pthread_create( &thread, NULL, getUserInput, NULL );

	while( !quit ){
		getmaxyx( stdscr, maxY, maxX );

		clear();
		if( printHelp ){
			mvprintw(( maxY - 1 )/2, ( maxX - 20 )/2, "Use WASD to move and q to quit." );
			mvprintw(( maxY - 1 )/2 + 1, ( maxX - 20 )/2, "Press space to stop moving." );
			mvprintw(( maxY - 1 )/2 + 2, ( maxX - 20 )/2, "1-4 changes color." );
			if( ch != ' ' ){
				printHelp = 0;
			}
		}
		if( color == 4 ){
			for( int i = 0; i < n; ++i ){
				attron( COLOR_PAIR((( cycle / 5 ) + i ) % 3 + 1 ) );
				mvprintw( location[ i ][ 1 ], location[ i ][ 0 ], "%c", string[ i ] );
			}
			cycle = ( cycle + 1 ) % 15;
		} else {
			for( int i = 0; i < n; ++i ){
				mvprintw( location[ i ][ 1 ], location[ i ][ 0 ], "%c", string[ i ] );
			}
		}
		refresh();

		usleep( DELAY );
		switch( ch ){
			case 'w':
				wait = 1;
				if( location[ n - 1 ][ 1 ] > 0 ){
					moveWord( &location, n );
					--location[ n - 1 ][ 1 ];
				}
				lastChar = 'w';
				break;
			case 's':
				wait = 1;
				if( location[ n - 1 ][ 1 ] < maxY - 1 ){
					moveWord( &location, n );
					location[ n - 1 ][ 1 ] += 1;
				}
				lastChar = 's';
				break;
			case 'a':
				wait = 1;
				if( location[ n - 1 ][ 0 ] > 0 ){
					moveWord( &location, n );
					location[ n - 1 ][ 0 ] -= 1;
				}
				lastChar = 'a';
				break;
			case 'd':
				wait = 1;
				if( location[ n - 1 ][ 0 ] < maxX - 1 ){
					moveWord( &location, n );
					++location[ n - 1 ][ 0 ];
				}
				lastChar = 'd';
				break;
			case DEL:
				wait = 1;
				--n;
				if( n == 0 ){
					quit = 1;
				}
				ch = lastChar;
				break;
			case '1':
				if( color == 1 ){
					attroff( COLOR_PAIR( 1 ) );
					color = 0;
				} else {
					attron( COLOR_PAIR( 1 ) );
					color = 1;
				}
				ch = lastChar;
				break;
			case '2':
				if( color == 2 ){
					attroff( COLOR_PAIR( 2 ) );
					color = 0;
				} else {
					attron( COLOR_PAIR( 2 ) );
					color = 2;
				}
				ch = lastChar;
				break;
			case '3':
				if( color == 3 ){
					attroff( COLOR_PAIR( 3 ) );
					color = 0;
				} else {
					attron( COLOR_PAIR( 3 ) );
					color = 3;
				}
				ch = lastChar;
				break;
			case '4':
				if( color == 4 ){
					// we have to set a color pair to insure we turn it off
					attron( COLOR_PAIR( 1 ) );
					attroff( COLOR_PAIR( 1 ) );
					color = 0;
				} else {
					color = 4;
				}
				ch = lastChar;
				break;
			case 'q':
			case ESC:
				quit = 1;
				break;
			default:
				lastChar = ' ';
				break;
		}
		wait = 0;
	}

	endwin();
	return( 0 );
}

void *getUserInput( void *args ){
	while( 1 ){
		if( !wait ){
			ch = getch();
		}
	}
}

void moveWord( int **location[ 2 ], int n ){
	for( int i = 1; i < n; ++i ){
		(*location)[ i - 1 ][ 0 ] = (*location)[ i ][ 0 ];
		(*location)[ i - 1 ][ 1 ] = (*location)[ i ][ 1 ];
	}
}
