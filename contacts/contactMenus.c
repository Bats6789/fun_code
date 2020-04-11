/*
 * Name: contactMenus.c
 * Desc: Contact's display menus.
 * Auth: Blake Wingard
 * Vers: 1.0.4 04/10/2020 CBW - Implemented exportMenu.
 * Vers: 1.0.3 04/10/2020 CBW - Implemented displayMenu.
 * Vers: 1.0.2 04/08/2020 CBW - Implemeted removeMenu.
 * Vers: 1.0.1 03/28/2020 CBW - Implemented addMenu.
 * Vers: 1.0.0 02/13/2020 CBW - Original code.
 */

#include "contactMenus.h"

int addMenu( displayInfoType displayInfo, contactsType *headContact ){
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
					*displayInfo.contactCount = *displayInfo.contactCount + 
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
	int notFound;
	boxType exitBox;
	boxType removeBox;
	selectedType selected;
	contactsType *currentContact;
	char currentPhoneNumber[ PHONE_NUMBER_SIZE ];

	removeBox.startX = displayInfo.maxX / 2 - BOX_WIDTH;
	removeBox.startY = displayInfo.maxY / 2 + BOX_HEIGHT / 2 + 1;
	removeBox.endX = removeBox.startX + BOX_WIDTH - 1;
	removeBox.endY = removeBox.startY + BOX_HEIGHT - 1;
	exitBox.startX = displayInfo.maxX / 2;
	exitBox.startY = displayInfo.maxY / 2 + BOX_HEIGHT / 2 + 1;
	exitBox.endX = exitBox.startX + BOX_WIDTH - 1;
	exitBox.endY = exitBox.startY + BOX_HEIGHT - 1;
	currentPhoneNumber[ 0 ] = '\0';
	quit = 0;
	index = 0;
	notFound = 0;

	while( !quit ){
		mvprintw( 4, displayInfo.maxX / 2 - 50, "PhoneNumber: %s",
				currentPhoneNumber );
		if( notFound ){
			attron( COLOR_PAIR( 1 ));
			mvprintw( 5, displayInfo.maxX / 2 - 50, "Phone number not found" );
			attroff( COLOR_PAIR( 1 ));
		}
		printRemove( removeBox.startY, removeBox.startX );
		printExit( exitBox.startY, exitBox.startX );
		refresh();
		chunk = wgetch( displayInfo.window );
		erase();

		if( chunk == KEY_MOUSE ){
			request_mouse_pos();
			wmouse_position( displayInfo.window, &(displayInfo.y), &(displayInfo.x));
			if( mouseOver( displayInfo, exitBox )){
				quit = 1;
			} else if( mouseOver( displayInfo, removeBox )){
				selected = Remove;
				if( currentPhoneNumber[ 0 ] != '\0' ){
					currentContact = getContact( headContact, currentPhoneNumber, phoneNumber );
					if( currentContact != NULL ){ 
						notFound = !removeContact( &headContact, currentContact );
					} else {
						notFound = 1;
					}
					currentPhoneNumber[ 0 ] = '\0';
					index = 0;
				}
			}
		} else {
			if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
				if( currentPhoneNumber[ 0 ] != '\0' ){
					currentContact = getContact( headContact, currentPhoneNumber, phoneNumber );
					if( currentContact != NULL ){ 
						notFound = !removeContact( &headContact, currentContact );
						*displayInfo.contactCount = *displayInfo.contactCount - 1;
					} else {
						notFound = 1;
					}
					currentPhoneNumber[ 0 ] = '\0';
					index = 0;
				}
			} else if( chunk == '\b' && index > 0 ){
				--index;
				currentPhoneNumber[ index ] = '\0';
			} else if( index + 1 < PHONE_NUMBER_SIZE ){
				currentPhoneNumber[ index ] = chunk;
				++index;
				currentPhoneNumber[ index ] = '\0';
			}
		}
	}
	free( currentContact );

	return( 0 );
}

int displayMenu( displayInfoType displayInfo, contactsType *headContact ){
	int quit;
	int chunk;
	int index;
	int notFound;
	int page;
	int pageSize;
	boxType exitBox;
	boxType nextBox;
	boxType prevBox;
	selectedType selected;
	contactsType *currentContact;
	contactsType *loopContact;

	nextBox.startX = displayInfo.maxX / 2 - BOX_WIDTH * 1.5;
	nextBox.startY = displayInfo.maxY - BOX_HEIGHT - 5;
	nextBox.endX = nextBox.startX + BOX_WIDTH - 1;
	nextBox.endY = nextBox.startY + BOX_HEIGHT - 1;
	prevBox.startX = displayInfo.maxX / 2 + BOX_WIDTH * 0.5;
	prevBox.startY = displayInfo.maxY - BOX_HEIGHT - 5;
	prevBox.endX = prevBox.startX + BOX_WIDTH - 1;
	prevBox.endY = prevBox.startY + BOX_HEIGHT - 1;
	exitBox.startX = displayInfo.maxX / 2 - BOX_WIDTH * 0.5;
	exitBox.startY = displayInfo.maxY - BOX_HEIGHT - 5;
	exitBox.endX = exitBox.startX + BOX_WIDTH - 1;
	exitBox.endY = exitBox.startY + BOX_HEIGHT - 1;
	quit = 0;
	index = 0;
	notFound = 0;
	page = 0;
	pageSize = ( displayInfo.maxY - BOX_HEIGHT - 8 ) / 8;
	currentContact = headContact;

	while( !quit ){
		printNext( nextBox.startY, nextBox.startX );
		printPrev( prevBox.startY, prevBox.startX );
		printExit( exitBox.startY, exitBox.startX );
		loopContact = currentContact;
		for( int i = 0; i < pageSize && ( page * pageSize + i < *displayInfo.contactCount ); ++i ){
			mvprintw( i * 8 + 3, 5, "FirstName: %s", loopContact->firstName );
			mvprintw( i * 8 + 4, 5, "MiddleName: %s", loopContact->middleName );
			mvprintw( i * 8 + 5, 5, "LastName: %s", loopContact->lastName );
			mvprintw( i * 8 + 6, 5, "PhoneNumber: %s", loopContact->phoneNumber );
			mvprintw( i * 8 + 7, 5, "Address: %s", loopContact->address );
			mvprintw( i * 8 + 8, 5, "State: %s", loopContact->state );
			mvprintw( i * 8 + 9, 5, "Zipcode: %s", loopContact->zipcode );
			loopContact = loopContact->nextContact;
		}
		refresh();
		chunk = wgetch( displayInfo.window );
		erase();

		if( chunk == KEY_MOUSE ){
			nc_getmouse( &(displayInfo.event));
			request_mouse_pos();
			wmouse_position( displayInfo.window, &(displayInfo.y), &(displayInfo.x));
			if( displayInfo.event.bstate & BUTTON1_PRESSED ){ 
				if( mouseOver( displayInfo, exitBox )){
					quit = 1;
				} else if( mouseOver( displayInfo, nextBox )){
					if(( page + 1 ) * pageSize < *displayInfo.contactCount ){
						++page;
						for( int i = 0; i < pageSize; ++i ){
							currentContact = currentContact->nextContact;
						}
					}
				} else if( mouseOver( displayInfo, prevBox )){
					if( page > 0 ){
						--page;
						for( int i = 0; i < pageSize; ++i ){
							currentContact = currentContact->prevContact;
						}
					}
				}
			}
		}
	}

	return( 0 );
}

int exportMenu( displayInfoType displayInfo, contactsType *headContact ){
	printw( "exportMenu function entered" );
	int quit;
	int chunk;
	int phoneIndex;
	int fileIndex;
	int notFound;
	int step;
	int fileFound;
	boxType exitBox;
	boxType exportBox;
	selectedType selected;
	contactsType *currentContact;
	char currentPhoneNumber[ PHONE_NUMBER_SIZE ];
	char filename[ 50 ];

	exportBox.startX = displayInfo.maxX / 2 - BOX_WIDTH;
	exportBox.startY = displayInfo.maxY / 2 + BOX_HEIGHT / 2 + 1;
	exportBox.endX = exportBox.startX + BOX_WIDTH - 1;
	exportBox.endY = exportBox.startY + BOX_HEIGHT - 1;
	exitBox.startX = displayInfo.maxX / 2;
	exitBox.startY = displayInfo.maxY / 2 + BOX_HEIGHT / 2 + 1;
	exitBox.endX = exitBox.startX + BOX_WIDTH - 1;
	exitBox.endY = exitBox.startY + BOX_HEIGHT - 1;
	currentPhoneNumber[ 0 ] = '\0';
	filename[ 0 ] = '\0';
	quit = 0;
	phoneIndex = 0;
	fileIndex = 0;
	notFound = 0;
	step = 0;
	fileFound = 0;

	while( !quit ){
		mvprintw( 4, displayInfo.maxX / 2 - 50, "PhoneNumber: %s", currentPhoneNumber );
		mvprintw( 5, displayInfo.maxX / 2 - 50, "filename: %s", filename );
		if( notFound ){
			attron( COLOR_PAIR( 1 ));
			mvprintw( 6, displayInfo.maxX / 2 - 50, "Phone number not found" );
			attroff( COLOR_PAIR( 1 ));
		}
		if( fileFound == NO_FILE ){
			attron( COLOR_PAIR( 1 ));
			mvprintw( 6, displayInfo.maxX / 2 - 50, "File %s was unable to open", filename );
			attroff( COLOR_PAIR( 1 ));
		}
		printExport( exportBox.startY, exportBox.startX );
		printExit( exitBox.startY, exitBox.startX );
		refresh();
		chunk = wgetch( displayInfo.window );
		erase();

		if( chunk == KEY_MOUSE ){
			request_mouse_pos();
			wmouse_position( displayInfo.window, &(displayInfo.y), &(displayInfo.x));
			if( mouseOver( displayInfo, exitBox )){
				quit = 1;
			} else if( mouseOver( displayInfo, exportBox )){
				selected = Remove;
				if( filename[ 0 ] != '\0' && currentPhoneNumber[ 0 ] != '\0' ){
					currentContact = getContact( headContact, currentPhoneNumber, phoneNumber );
					if( currentContact != NULL ){ 
						fileFound = exportContact( *currentContact, filename );
						if( fileFound == 0 ){
							phoneIndex = 0;
							currentPhoneNumber[ 0 ] = '\0';
							fileIndex = 0;
							filename[ 0 ] = '\0';
						}
						notFound = 0;
					} else {
						notFound = 1;
					}
				}
			}
		} else {
			switch( step ){
				case 0:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						step = 1;
					} else if( chunk == '\b' && phoneIndex > 0 ){
						--phoneIndex;
						currentPhoneNumber[ phoneIndex ] = '\0';
					} else if( phoneIndex + 1 < PHONE_NUMBER_SIZE ){
						currentPhoneNumber[ phoneIndex ] = chunk;
						++phoneIndex;
						currentPhoneNumber[ phoneIndex ] = '\0';
					}
					break;
				case 1:
					if( chunk == '\n' || chunk == KEY_ENTER || chunk == 13 ){
						step = 0;
					} else if( chunk == '\b' && fileIndex > 0 ){
						--fileIndex;
						filename[ fileIndex ] = '\0';
					} else if( fileIndex + 1 < 50 ){
						filename[ fileIndex ] = chunk;
						++fileIndex;
						filename[ fileIndex ] = '\0';
					}
					break;
			}
		}
	}

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

int printNext( int startY, int startX ){
	mvprintw( startY + 0, startX, "+------------------+" );
	mvprintw( startY + 1, startX, "|                  |" );
	mvprintw( startY + 2, startX, "|       next       |" );
	mvprintw( startY + 3, startX, "|                  |" );
	mvprintw( startY + 4, startX, "+------------------+" );
	return( 0 );
}

int printPrev( int startY, int startX ){
	mvprintw( startY + 0, startX, "+------------------+" );
	mvprintw( startY + 1, startX, "|                  |" );
	mvprintw( startY + 2, startX, "|       PREV       |" );
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
