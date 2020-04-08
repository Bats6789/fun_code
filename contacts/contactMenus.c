/*
 * Name: contactMenus.c
 * Desc: Contact's display menus.
 * Auth: Blake Wingard
 * Vers: 1.0.1 03/28/2020 CBW - Implemented addMenu.
 * Vers: 1.0.0 02/13/2020 CBW - Original code.
 */

#include "contactMenus.h"

int addMenu( displayInfoType displayInfo, contactsType *headContact ){
	printw( "addMenu function entered" );
	int quit;
	int chunk;
	int index;
	boxType exitBox;
	boxType addBox;
	selectedType selected;
	contactsType *currentContact;
	columnType element;

	addBox.startX = displayInfo.maxX / 2 - BOX_WIDTH;
	addBox.startY = displayInfo.maxY / 2 + BOX_HEIGHT / 2 + 1;
	addBox.endX = addBox.startX + BOX_WIDTH - 1;
	addBox.endY = addBox.startY + BOX_HEIGHT - 1;
	exitBox.startX = displayInfo.maxX / 2;
	exitBox.startY = displayInfo.maxY / 2 + BOX_HEIGHT / 2 + 1;
	exitBox.endX = exitBox.startX + BOX_WIDTH - 1;
	exitBox.endY = exitBox.startY + BOX_HEIGHT - 1;
	quit = 0;
	index = 0;
	element = firstName;
	currentContact = malloc( sizeof( contactsType ));
	if( currentContact == NULL ){
		printw( "Failed to create Contact struct.\n" );
		return( -1 );
	}
	currentContact->firstName[ 0 ] = '\0';
	currentContact->middleName[ 0 ] = '\0';
	currentContact->lastName[ 0 ] = '\0';
	currentContact->phoneNumber[ 0 ] = '\0';
	currentContact->address[ 0 ] = '\0';
	currentContact->state[ 0 ] = '\0';
	currentContact->zipcode[ 0 ] = '\0';

	while( !quit ){
		mvprintw( 4, displayInfo.maxX / 2 - 50, "FirstName: %s",
				currentContact->firstName );
		mvprintw( 6, displayInfo.maxX / 2 - 50, "MiddleName: %s",
				currentContact->middleName );
		mvprintw( 8, displayInfo.maxX / 2 - 50, "LastName: %s",
				currentContact->lastName );
		mvprintw( 10, displayInfo.maxX / 2 - 50, "PhoneNumber: %s",
				currentContact->phoneNumber );
		mvprintw( 12, displayInfo.maxX / 2 - 50, "Address: %s",
				currentContact->address );
		mvprintw( 14, displayInfo.maxX / 2 - 50, "State: %s",
				currentContact->state );
		mvprintw( 16, displayInfo.maxX / 2 - 50, "Zipcode: %s",
				currentContact->zipcode );
		printAdd( addBox.startY, addBox.startX );
		printExit( exitBox.startY, exitBox.startX );
		refresh();
		chunk = wgetch( displayInfo.window );
		erase();

		if( chunk == KEY_MOUSE ){
			request_mouse_pos();
			wmouse_position( displayInfo.window, &(displayInfo.y), &(displayInfo.x));
			if( mouseOver( displayInfo, exitBox )){
				quit = 1;
			} else if( mouseOver( displayInfo, addBox )){
				selected = Add;
				if( currentContact->phoneNumber[ 0 ] != '\0' ){
					addContact( headContact, currentContact );
					if( currentContact == NULL ){
						printw( "Failed to create Contact struct.\n" );
						return( -1 );
					}
					currentContact = malloc( sizeof( contactsType ));
					currentContact->firstName[ 0 ] = '\0';
					currentContact->middleName[ 0 ] = '\0';
					currentContact->lastName[ 0 ] = '\0';
					currentContact->phoneNumber[ 0 ] = '\0';
					currentContact->address[ 0 ] = '\0';
					currentContact->state[ 0 ] = '\0';
					currentContact->zipcode[ 0 ] = '\0';
					element = firstName;
					index = 0;
				}
			}
		} else {
			switch( element ){
				case firstName:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = middleName;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->firstName[ index ] = '\0';
					} else if( index + 1 < FIRST_NAME_SIZE ){
						currentContact->firstName[ index ] = chunk;
						++index;
						currentContact->firstName[ index ] = '\0';
					}
					break;
				case middleName:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = lastName;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->middleName[ index ] = '\0';
					} else if( index + 1 < MIDDLE_NAME_SIZE ){
						currentContact->middleName[ index ] = chunk;
						++index;
						currentContact->middleName[ index ] = '\0';
					}
					break;
				case lastName:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = phoneNumber;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->lastName[ index ] = '\0';
					} else if( index + 1 < LAST_NAME_SIZE ){
						currentContact->lastName[ index ] = chunk;
						++index;
						currentContact->lastName[ index ] = '\0';
					}
					break;
				case phoneNumber:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = address;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->phoneNumber[ index ] = '\0';
					} else if( index + 1 < PHONE_NUMBER_SIZE ){
						currentContact->phoneNumber[ index ] = chunk;
						++index;
						currentContact->phoneNumber[ index ] = '\0';
					}
					break;
				case address:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = state;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->address[ index ] = '\0';
					} else if( index + 1 < ADDRESS_SIZE ){
						currentContact->address[ index ] = chunk;
						++index;
						currentContact->address[ index ] = '\0';
					}
					break;
				case state:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = zipcode;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->state[ index ] = '\0';
					} else if( index + 1 < STATE_SIZE ){
						currentContact->state[ index ] = chunk;
						++index;
						currentContact->state[ index ] = '\0';
					}
					break;
				case zipcode:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = firstName;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->zipcode[ index ] = '\0';
					} else if( index + 1 < ZIPCODE_SIZE ){
						currentContact->zipcode[ index ] = chunk;
						++index;
						currentContact->zipcode[ index ] = '\0';
					}
					break;
				default:
					break;
			}
		}
	}
	free( currentContact );

	return( 0 );
}

int removeMenu( displayInfoType displayInfo, contactsType *headContact ){
	printw( "removeMenu function entered" );
	int quit;
	int chunk;
	int index;
	boxType exitBox;
	boxType addBox;
	selectedType selected;
	contactsType *currentContact;
	columnType element;

	addBox.startX = displayInfo.maxX / 2 - BOX_WIDTH;
	addBox.startY = displayInfo.maxY / 2 + BOX_HEIGHT / 2 + 1;
	addBox.endX = addBox.startX + BOX_WIDTH - 1;
	addBox.endY = addBox.startY + BOX_HEIGHT - 1;
	exitBox.startX = displayInfo.maxX / 2;
	exitBox.startY = displayInfo.maxY / 2 + BOX_HEIGHT / 2 + 1;
	exitBox.endX = exitBox.startX + BOX_WIDTH - 1;
	exitBox.endY = exitBox.startY + BOX_HEIGHT - 1;
	quit = 0;
	index = 0;
	element = firstName;
	currentContact = malloc( sizeof( contactsType ));
	if( currentContact == NULL ){
		printw( "Failed to create Contact struct.\n" );
		return( -1 );
	}
	currentContact->firstName[ 0 ] = '\0';
	currentContact->middleName[ 0 ] = '\0';
	currentContact->lastName[ 0 ] = '\0';
	currentContact->phoneNumber[ 0 ] = '\0';
	currentContact->address[ 0 ] = '\0';
	currentContact->state[ 0 ] = '\0';
	currentContact->zipcode[ 0 ] = '\0';

	while( !quit ){
		mvprintw( 4, displayInfo.maxX / 2 - 50, "FirstName: %s",
				currentContact->firstName );
		mvprintw( 6, displayInfo.maxX / 2 - 50, "MiddleName: %s",
				currentContact->middleName );
		mvprintw( 8, displayInfo.maxX / 2 - 50, "LastName: %s",
				currentContact->lastName );
		mvprintw( 10, displayInfo.maxX / 2 - 50, "PhoneNumber: %s",
				currentContact->phoneNumber );
		mvprintw( 12, displayInfo.maxX / 2 - 50, "Address: %s",
				currentContact->address );
		mvprintw( 14, displayInfo.maxX / 2 - 50, "State: %s",
				currentContact->state );
		mvprintw( 16, displayInfo.maxX / 2 - 50, "Zipcode: %s",
				currentContact->zipcode );
		printAdd( addBox.startY, addBox.startX );
		printExit( exitBox.startY, exitBox.startX );
		refresh();
		chunk = wgetch( displayInfo.window );
		erase();

		if( chunk == KEY_MOUSE ){
			request_mouse_pos();
			wmouse_position( displayInfo.window, &(displayInfo.y), &(displayInfo.x));
			if( mouseOver( displayInfo, exitBox )){
				quit = 1;
			} else if( mouseOver( displayInfo, addBox )){
				selected = Add;
				if( currentContact->phoneNumber[ 0 ] != '\0' ){
					addContact( headContact, currentContact );
					if( currentContact == NULL ){
						printw( "Failed to create Contact struct.\n" );
						return( -1 );
					}
					currentContact = malloc( sizeof( contactsType ));
					currentContact->firstName[ 0 ] = '\0';
					currentContact->middleName[ 0 ] = '\0';
					currentContact->lastName[ 0 ] = '\0';
					currentContact->phoneNumber[ 0 ] = '\0';
					currentContact->address[ 0 ] = '\0';
					currentContact->state[ 0 ] = '\0';
					currentContact->zipcode[ 0 ] = '\0';
					element = firstName;
					index = 0;
				}
			}
		} else {
			switch( element ){
				case firstName:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = middleName;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->firstName[ index ] = '\0';
					} else if( index + 1 < FIRST_NAME_SIZE ){
						currentContact->firstName[ index ] = chunk;
						++index;
						currentContact->firstName[ index ] = '\0';
					}
					break;
				case middleName:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = lastName;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->middleName[ index ] = '\0';
					} else if( index + 1 < MIDDLE_NAME_SIZE ){
						currentContact->middleName[ index ] = chunk;
						++index;
						currentContact->middleName[ index ] = '\0';
					}
					break;
				case lastName:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = phoneNumber;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->lastName[ index ] = '\0';
					} else if( index + 1 < LAST_NAME_SIZE ){
						currentContact->lastName[ index ] = chunk;
						++index;
						currentContact->lastName[ index ] = '\0';
					}
					break;
				case phoneNumber:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = address;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->phoneNumber[ index ] = '\0';
					} else if( index + 1 < PHONE_NUMBER_SIZE ){
						currentContact->phoneNumber[ index ] = chunk;
						++index;
						currentContact->phoneNumber[ index ] = '\0';
					}
					break;
				case address:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = state;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->address[ index ] = '\0';
					} else if( index + 1 < ADDRESS_SIZE ){
						currentContact->address[ index ] = chunk;
						++index;
						currentContact->address[ index ] = '\0';
					}
					break;
				case state:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = zipcode;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->state[ index ] = '\0';
					} else if( index + 1 < STATE_SIZE ){
						currentContact->state[ index ] = chunk;
						++index;
						currentContact->state[ index ] = '\0';
					}
					break;
				case zipcode:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						index = 0;
						element = firstName;
					} else if( chunk == '\b' && index > 0 ){
						--index;
						currentContact->zipcode[ index ] = '\0';
					} else if( index + 1 < ZIPCODE_SIZE ){
						currentContact->zipcode[ index ] = chunk;
						++index;
						currentContact->zipcode[ index ] = '\0';
					}
					break;
				default:
					break;
			}
		}
	}
	free( currentContact );

	return( 0 );
}

int displayMenu( displayInfoType displayInfo, contactsType *headContact ){
	printw( "displayMenu function entered" );
	return( 0 );
}

int exportMenu( displayInfoType displayInfo, contactsType *headContact ){
	printw( "exportMenu function entered" );
	return( 0 );
}

// Print buttons
int printAdd( int startY, int startX ){
	mvprintw( startY + 0, startX, "+------------------+" );
	mvprintw( startY + 1, startX, "|                  |" );
	mvprintw( startY + 2, startX, "|       ADD        |" );
	mvprintw( startY + 3, startX, "|                  |" );
	mvprintw( startY + 4, startX, "+------------------+" );
	return( 0 );
}

int printRemove( int startY, int startX ){
	mvprintw( startY + 0, startX, "+------------------+" );
	mvprintw( startY + 1, startX, "|                  |" );
	mvprintw( startY + 2, startX, "|      REMOVE      |" );
	mvprintw( startY + 3, startX, "|                  |" );
	mvprintw( startY + 4, startX, "+------------------+" );
	return( 0 );
}

int printDisplay( int startY, int startX ){
	mvprintw( startY + 0, startX, "+------------------+" );
	mvprintw( startY + 1, startX, "|                  |" );
	mvprintw( startY + 2, startX, "|      DISPLAY     |" );
	mvprintw( startY + 3, startX, "|                  |" );
	mvprintw( startY + 4, startX, "+------------------+" );
	return( 0 );
}

int printExport( int startY, int startX ){
	mvprintw( startY + 0, startX, "+------------------+" );
	mvprintw( startY + 1, startX, "|                  |" );
	mvprintw( startY + 2, startX, "|      EXPORT      |" );
	mvprintw( startY + 3, startX, "|                  |" );
	mvprintw( startY + 4, startX, "+------------------+" );
	return( 0 );
}

int printExit( int startY, int startX ){
	mvprintw( startY + 0, startX, "+------------------+" );
	mvprintw( startY + 1, startX, "|                  |" );
	mvprintw( startY + 2, startX, "|       EXIT       |" );
	mvprintw( startY + 3, startX, "|                  |" );
	mvprintw( startY + 4, startX, "+------------------+" );
	return( 0 );
}

int mouseOver( displayInfoType displayInfo, boxType box ){
	int exitCode;
	if( displayInfo.x >= box.startX && displayInfo.x < box.endX &&
			displayInfo.y >= box.startY && displayInfo.y < box.endY ){
		exitCode = 1;
	} else {
		exitCode = 0;
	}
	return( exitCode );
}
