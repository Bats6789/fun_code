#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

#define DELAY 30000

char ch;

void *getUserInput( void *args );

int main( int argc, char **argv ){
	int x;
	int y;
	int maxY;
	int maxX;
	int nextX;
	int direction;
	int quit;
	pthread_t thread;

	x = 0;
	y = 0;
	maxY = 0;
	maxX = 0;
	nextX = 0;
	direction = 1;
	ch = ' ';
	quit = 0;

	initscr();
	noecho();
	curs_set(FALSE);

	pthread_create( &thread, NULL, getUserInput, NULL );

	while( !quit ){
		getmaxyx( stdscr, maxY, maxX );

		clear();
		mvprintw( y, x, "o" );
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
				if( x < maxX - 1 ){
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
