/*
 * Name: contactMenus.h
 * Desc: Contact's display menus.
 * Auth: Blake Wingard
 * Vers: 1.0.3 04/10/2020 CBW - Implemented displayMenu.
 * Vers: 1.0.2 04/08/2020 CBW - Implemeted removeMenu.
 * Vers: 1.0.1 03/28/2020 CBW - Moved print functions to here.
 * Vers: 1.0.0 02/13/2020 CBW - Original code.
 */

#ifndef _CONTACT_MENUS_H_
#define _CONTACT_MENUS_H_

#include <curses.h>
#include "contactCsv.h"
#include <stdlib.h>
#include <stdlib.h>

#define BOX_WIDTH 20
#define BOX_HEIGHT 5

typedef struct displayInfoType {
	int maxX;
	int maxY;
	char *inputChar;
	int x;
	int y;
	int *contactCount;
	MEVENT event;
	WINDOW *window;
} displayInfoType;

typedef struct boxType {
	int startX;
	int startY;
	int endX;
	int endY;
} boxType;

typedef enum selectedType {
	None, Add, Remove, Display, Export, Exit
} selectedType;

/*
 * Name: addMenu
 * Auth Blake Wingard
 * Desc: The display for the add option.
 * Args:
 * 	displayInfoType displayInfo - the info of the current display
 * 	contactsType *headContact - the head node for the contact list.
 */
int addMenu( displayInfoType displayInfo, contactsType *headContact );

/*
 * Name: removeMenu
 * Auth Blake Wingard
 * Desc: The display for the remove option.
 * Args:
 * 	displayInfoType displayInfo - the info of the current display
 * 	contactsType *headContact - the head node for the contact list.
 */
int removeMenu( displayInfoType displayInfo, contactsType *headContact );

/*
 * Name: displayMenu
 * Auth Blake Wingard
 * Desc: The display for the display option.
 * Args:
 * 	displayInfoType displayInfo - the info of the current display
 * 	contactsType *headContact - the head node for the contact list.
 */
int displayMenu( displayInfoType displayInfo, contactsType *headContact );

/*
 * Name: exportMenu
 * Auth Blake Wingard
 * Desc: The display for the export option.
 * Args:
 * 	displayInfoType displayInfo - the info of the current display
 * 	contactsType *headContact - the head node for the contact list.
 */
int exportMenu( displayInfoType displayInfo, contactsType *headContact );

/*
 * Name: printAdd
 * Auth Blake Wingard
 * Desc: prints the add button
 * Args:
 *	int startY - the first Y value
 * 	int startX - the first X value
 */
int printAdd( int startY, int startX );

/*
 * Name: printRemove
 * Auth Blake Wingard
 * Desc: prints the remove button
 * Args:
 *	int startY - the first Y value
 * 	int startX - the first X value
 */
int printRemove( int startY, int startX );

/*
 * Name: printDisplay
 * Auth Blake Wingard
 * Desc: prints the display button
 * Args:
 *	int startY - the first Y value
 * 	int startX - the first X value
 */
int printDisplay( int startY, int startX );

/*
 * Name: printExport
 * Auth Blake Wingard
 * Desc: prints the export button
 * Args:
 *	int startY - the first Y value
 * 	int startX - the first X value
 */
int printExport( int startY, int startX );

/*
 * Name: printExit
 * Auth Blake Wingard
 * Desc: prints the exit button
 * Args:
 *	int startY - the first Y value
 * 	int startX - the first X value
 */
int printExit( int startY, int startX );

/*
 * Name: mouseOver
 * Auth Blake Wingard
 * Desc: Determines if the mouse is over a region.
 * Args:
 * 	displayInfoType displayInfo - the info of the current display
 * 	boxType box - box info
 */
int mouseOver( displayInfoType displayInfo, boxType box );

/* 
 * Name: printPrev
 * Desc: Prints the prev button. 
 * Args: 
 * 	int startY - the first Y value
 * 	int startX - the first X value
 */
int printPrev( int startY, int startX );

/* 
 * Name: printNext
 * Desc: Prints the next button. 
 * Args: 
 * 	int startY - the first Y value
 * 	int startX - the first X value
 */
int printNext( int startY, int startX );
#endif
