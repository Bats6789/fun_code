#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

#define DELAY 30000
#define SCALE 1000

char ch;

void *getUserInput( void *args );

int main( int argc, char **argv ){
	int x;
	int y;
	int n;
	int maxY;
	int maxX;
	int nextX;
	int direction;
	int quit;
	int scale;
	char *string;
	pthread_t thread;

	x = 0;
	y = 0;
	n = 0;
	maxY = 0;
	maxX = 0;
	nextX = 0;
	direction = 1;
	ch = ' ';
	quit = 0;
	scale = 1;
	string = malloc( sizeof( char ) * SCALE * scale );
	string[ 0 ] = '\0';

	initscr();
	noecho();
	curs_set(FALSE);
	getmaxyx( stdscr, maxY, maxX );
	mvprintw(( maxY - 1 )/2, ( maxX - 20 )/2, "Please enter a word: " );
	refresh();
	while( ch != '\n' ){
		mvprintw(( maxY - 1 )/2, ( maxX - 20 )/2, "Please enter a word: %s", string );
		refresh();
		ch = getch();
		++n;
		if( ch != '\n' ){
			string[ n - 1 ] = ch;
		}
		if( n % 1000 == 0 ){
			++scale;
			string = realloc( string, sizeof( char ) * scale * SCALE );
		}
		if( ch != '\n' ){
			string[ n ] = '\0';
		}

	}
	--n;
	ch = ' ';

	pthread_create( &thread, NULL, getUserInput, NULL );

	while( !quit ){
		getmaxyx( stdscr, maxY, maxX );

		clear();
		mvprintw( y, x, "%s", string );
		refresh();

		usleep( DELAY );
		switch( ch ){
			case 'w':
				if( y > 0 ){
					--y;
				}
				break;
			case 's':
				if( y < maxY - 1 ){
					++y;
				}
				break;
			case 'a':
				if( x > 0 ){
					x -= 2;
				}
				break;
			case 'd':
				if( x < maxX - 1 - n ){
					x += 2;
				}
				break;
			case 'q':
				quit = 1;
				break;
		}
	}

	endwin();
	return( 0 );
}

void *getUserInput( void *args ){
	while( 1 ){
		ch = getch();
	}
}
