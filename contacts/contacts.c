/*
 * Name: contacts.c
 * Desc: A contact manager written in ncurses.
 * Auth: Blake Wingard
 * Vers: 1.0.1 03/28/2020 CBW - Added other menu functions.
 * Vers: 1.0.0 02/13/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <curses.h>
#include <unistd.h>
#include "contactCsv.h"
#include "contactMenus.h"

int main( int argc, char **argv ){
	int quit;
	int chunk;
	contactsType *headContact;
	displayInfoType displayInfo;
	boxType addBox;
	boxType removeBox;
	boxType displayBox;
	boxType exportBox;
	boxType exitBox;
	selectedType selected;

	// initialize
	quit = 0;
	chunk = '\0';
	headContact = NULL;

	// start ncurses stuff
	displayInfo.window = initscr();
	raw();
	noecho();
	nocbreak();
	start_color();
	if( has_colors() == FALSE ) {
		endwin();
		printf( "ERROR: No colors\n" );
		return( 1 );
	}
	curs_set( 0 );
	keypad( stdscr, TRUE );
	init_pair( 1, COLOR_WHITE, COLOR_RED );
	mouse_on(1);
	mousemask( ALL_MOUSE_EVENTS, NULL );
	getmaxyx( stdscr, displayInfo.maxY, displayInfo.maxX );

	// set box properties
	addBox.startX = displayInfo.maxX / 2 - BOX_WIDTH;
	addBox.startY = displayInfo.maxY / 2 - ( 3 * BOX_HEIGHT / 2 );
	addBox.endX = addBox.startX + BOX_WIDTH - 1;
	addBox.endY = addBox.startY + BOX_HEIGHT - 1;
	removeBox.startX = displayInfo.maxX / 2;
	removeBox.startY = displayInfo.maxY / 2 - ( 3 * BOX_HEIGHT / 2 );
	removeBox.endX = removeBox.startX + BOX_WIDTH - 1;
	removeBox.endY = removeBox.startY + BOX_HEIGHT - 1;
	displayBox.startX = displayInfo.maxX / 2 - BOX_WIDTH;
	displayBox.startY = displayInfo.maxY / 2 - BOX_HEIGHT / 2;
	displayBox.endX = displayBox.startX + BOX_WIDTH - 1;
	displayBox.endY = displayBox.startY + BOX_HEIGHT - 1;
	exportBox.startX = displayInfo.maxX / 2;
	exportBox.startY = displayInfo.maxY / 2 - BOX_HEIGHT / 2;
	exportBox.endX = exportBox.startX + BOX_WIDTH - 1;
	exportBox.endY = exportBox.startY + BOX_HEIGHT - 1;
	exitBox.startX = displayInfo.maxX / 2 - BOX_WIDTH / 2;
	exitBox.startY = displayInfo.maxY / 2 + BOX_HEIGHT / 2 + 1;
	exitBox.endX = exitBox.startX + BOX_WIDTH - 1;
	exitBox.endY = exitBox.startY + BOX_HEIGHT - 1;

	// import list
	if( importContact( &headContact, "contact.csv" ) < 0 ){
		endwin();
		printf( "ERROR: Failed to create HeadNode\n" );
		return( -1 );
	}

	while( quit != 1 ){
		// display menu
		if( selected == Add ){
			attron( COLOR_PAIR( 1 ));
		}
		printAdd( addBox.startY, addBox.startX );
		if( selected == Add ){
			attroff( COLOR_PAIR( 1 ));
		}
		if( selected == Remove ){
			attron( COLOR_PAIR( 1 ));
		}
		printRemove( removeBox.startY, removeBox.startX );
		if( selected == Remove ){
			attroff( COLOR_PAIR( 1 ));
		}
		if( selected == Display ){
			attron( COLOR_PAIR( 1 ));
		}
		printDisplay( displayBox.startY, displayBox.startX );
		if( selected == Display ){
			attroff( COLOR_PAIR( 1 ));
		}
		if( selected == Export ){
			attron( COLOR_PAIR( 1 ));
		}
		printExport( exportBox.startY, exportBox.startX );
		if( selected == Export ){
			attroff( COLOR_PAIR( 1 ));
		}
		if( selected == Exit ){
			attron( COLOR_PAIR( 1 ));
		}
		printExit( exitBox.startY, exitBox.startX );
		if( selected == Exit ){
			attroff( COLOR_PAIR( 1 ));
		}
		refresh();

		// collect info
		chunk = wgetch( displayInfo.window );
		erase();

		// determine what to do with collected info
		if( chunk == 'q' ){
			quit = 1;
		} else if( chunk == 'a' ){
			selected = Add;
		} else if( chunk == 'r' ){
			selected = Remove;
		} else if( chunk == 'd' ){
			selected = Display;
		} else if( chunk == 'e' ){
			selected = Export;
		} else if( chunk == 'x' ){
			selected = Exit;
		} else if( chunk == KEY_MOUSE ){
			/*
			request_mouse_pos();
			wmouse_position( displayInfo.window, &(displayInfo.y), &(displayInfo.x));
			*/
			// used nc_getmouse to check if the mouse was clicked
			nc_getmouse( &(displayInfo.event));
			displayInfo.y = displayInfo.event.y;
			displayInfo.x = displayInfo.event.x;
			if( displayInfo.event.bstate & BUTTON1_PRESSED ){
				if( mouseOver( displayInfo, addBox )){
					selected = Add;
					addMenu( displayInfo, headContact );
					chunk = '\0';
				} else if( mouseOver( displayInfo, removeBox )){
					selected = Remove;
					removeMenu( displayInfo, headContact );
					chunk = '\0';
				} else if( mouseOver( displayInfo, displayBox )){
					selected = Display;
					displayMenu( displayInfo, headContact );
					chunk = '\0';
				} else if( mouseOver( displayInfo, exportBox )){
					selected = Export;
					exportMenu( displayInfo, headContact );
					chunk = '\0';
				} else if( mouseOver( displayInfo, exitBox )){
					selected = Exit;
				}
			}
		} else {
			selected = None;
		}

		switch( selected ){
			case Add:
				break;
			case Remove:
				break;
			case Display:
				break;
			case Export:
				break;
			case Exit:
				quit = 1;
				break;
			default:
				break;
		}
	}

	// export list
	exportContact( headContact, "contact.csv" );
	refresh();

	endwin();

	return( EXIT_SUCCESS );
}

