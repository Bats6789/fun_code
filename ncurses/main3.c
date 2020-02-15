#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main( int argc, char **argv ){
	int x;
	int y;
	int maxY;
	int maxX;
	int nextX;
	int direction;

	x = 0;
	y = 0;
	maxY = 0;
	maxX = 0;
	nextX = 0;
	direction = 1;

	initscr();
	noecho();
	curs_set(FALSE);

	getmaxyx( stdscr, maxY, maxX );

	while( 1 ){
		clear();
		mvprintw( y, x, "o" );
		refresh();

		usleep( DELAY );
		nextX = x + direction;
		if( nextX >= maxX || nextX < 0 ){
			direction *= -1;
		} else {
			x += direction;
		}
	}

	endwin();
	return( 0 );
}
