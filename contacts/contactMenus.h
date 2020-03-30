/*
 * Name: contactMenus.h
 * Desc: Contact's display menus.
 * Auth: Blake Wingard
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

int addMenu( displayInfoType displayInfo, contactsType *headContact );

int removeMenu( displayInfoType displayInfo, contactsType *headContact );

int displayMenu( displayInfoType displayInfo, contactsType *headContact );

int exportMenu( displayInfoType displayInfo, contactsType *headContact );

int printAdd( int startY, int startX );

int printRemove( int startY, int startX );

int printDisplay( int startY, int startX );

int printExport( int startY, int startX );

int printExit( int startY, int startX );

int mouseOver( displayInfoType displayInfo, boxType box );

#endif
