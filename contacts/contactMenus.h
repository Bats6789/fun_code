/*
 * Name: contactMenus.h
 * Desc: Contact's display menus.
 * Auth: Blake Wingard
 * Vers: 1.0.0 02/13/2020 CBW - Original code.
 */

#ifndef _CONTACT_MENUS_H_
#define _CONTACT_MENUS_H_

#include <curses.h>

typedef struct displayInfoType {
    int maxX;
    int maxY;
    char *inputChar;
    int x;
    int y;
    MEVENT event;
} displayInfoType;

typedef struct boxType {
    int startX;
    int startY;
    int endX;
    int endY;
} boxType;

int addMenu( displayInfoType displayInfo );

int removeMenu( displayInfoType displayInfo );

int displayMenu( displayInfoType displayInfo );

int exportMenu( displayInfoType displayInfo );

#endif
