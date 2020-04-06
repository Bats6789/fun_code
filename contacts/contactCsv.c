/*
 * Name: contactCsv.c
 * Desc: The csv manager for contacts.
 * Auth: Blake Wingard
 * Vers: 1.0.1 03/28/2020 CBW - Implemented import, export, and add.
 * Vers: 1.0.0 02/13/2020 CBW - Original code.
 */

#include "contactCsv.h"

int importContact( contactsType **headContact, char *fileName ){
	printw( "importContact function entered" );
	FILE *file;
	char chunk;
	int index;
	contactsType *currentContact;
	columnType element;

	file = fopen( fileName, "r" );
	if( file == NULL ){
		printw( "ERROR: Failed to open %s", fileName );
		return( -1 );
	}
	currentContact = malloc( sizeof( contactsType ));
	if( currentContact == NULL ){
		printw( "ERROR: Failed to create headContact." );
		fclose( file );
		return( -1 );
	}
	currentContact->nextContact = currentContact;
	currentContact->prevContact = currentContact;
	*headContact = currentContact;
	element = firstName;
	index = 0;

	while( fscanf( file, "%c", &chunk ) != EOF ){ 
		switch( element ){
			case firstName:
				if( chunk == ',' ){
					currentContact->firstName[ index ] = '\0';
					index = 0;
					element = middleName;
				} else if( index + 1 < FIRST_NAME_SIZE ){
					currentContact->firstName[ index ] = chunk;
					++index;
					currentContact->firstName[ index ] = '\0';
				}
				break;
			case middleName:
				if( chunk == ',' ){
					currentContact->middleName[ index ] = '\0';
					index = 0;
					element = lastName;
				} else if( index + 1 < MIDDLE_NAME_SIZE ){
					currentContact->middleName[ index ] = chunk;
					++index;
					currentContact->middleName[ index ] = '\0';
				}
				break;
			case lastName:
				if( chunk == ',' ){
					currentContact->lastName[ index ] = '\0';
					index = 0;
					element = phoneNumber;
				} else if( index + 1 < LAST_NAME_SIZE ){
					currentContact->lastName[ index ] = chunk;
					++index;
					currentContact->lastName[ index ] = '\0';
				}
				break;
			case phoneNumber:
				if( chunk == ',' ){
					currentContact->phoneNumber[ index ] = '\0';
					index = 0;
					element = address;
				} else if( index + 1 < PHONE_NUMBER_SIZE ){
					currentContact->phoneNumber[ index ] = chunk;
					++index;
					currentContact->phoneNumber[ index ] = '\0';
				}
				break;
			case address:
				if( chunk == ',' ){
					currentContact->address[ index ] = '\0';
					index = 0;
					element = state;
				} else if( index + 1 < ADDRESS_SIZE ){
					currentContact->address[ index ] = chunk;
					++index;
					currentContact->address[ index ] = '\0';
				}
				break;
			case state:
				if( chunk == ',' ){
					currentContact->state[ index ] = '\0';
					index = 0;
					element = zipcode;
				} else if( index + 1 < STATE_SIZE ){
					currentContact->state[ index ] = chunk;
					++index;
					currentContact->state[ index ] = '\0';
				}
				break;
			case zipcode:
				if( chunk == '\n' ){
					currentContact->zipcode[ index ] = '\0';
					index = 0;
					element = firstName;
					currentContact->nextContact = malloc( sizeof( contactsType ));
					if( currentContact->nextContact == NULL ){
						printw( "ERROR: Failed to create new contact." );
						return( -1 );
					}
					if( currentContact->prevContact == currentContact ){
						currentContact->prevContact = NULL;
					}
					currentContact->nextContact->prevContact = currentContact;
					currentContact = currentContact->nextContact;
					currentContact->nextContact = NULL;
				} else if( index + 1 < ZIPCODE_SIZE ){
					currentContact->zipcode[ index ] = chunk;
					++index;
					currentContact->zipcode[ index ] = '\0';
				}
				break;
		}
	}
	if( currentContact->nextContact != currentContact ){
		currentContact->prevContact->nextContact = NULL;
		free( currentContact );
	}

	return( 0 );
}

int exportContact( contactsType *headContact, char *fileName ){
	printw( "exportContact function entered" );
	FILE *file;
	contactsType *currentContact;

	file = fopen( fileName, "w" );
	currentContact = headContact;

	while( currentContact != NULL ){
		fprintf( file, "%s,%s,%s,%s,%s,%s,%s\n", currentContact->firstName,
				currentContact->middleName, currentContact->lastName,
				currentContact->phoneNumber, currentContact->address,
				currentContact->state, currentContact->zipcode );
		currentContact = currentContact->nextContact;
	}
	return( 0 );
}

int addContact( contactsType *headContact, contactsType *contact ){
	printw( "addContact function entered" );
	contactsType *currentContact;
	int count;

	currentContact = headContact;
	count = 0;

	if( currentContact->nextContact == currentContact ){
		strcpy( currentContact->firstName, contact->firstName );
		strcpy( currentContact->middleName, contact->middleName );
		strcpy( currentContact->lastName, contact->lastName );
		strcpy( currentContact->phoneNumber, contact->phoneNumber );
		strcpy( currentContact->address, contact->address );
		strcpy( currentContact->state, contact->state );
		strcpy( currentContact->zipcode, contact->zipcode );
		currentContact->nextContact = NULL;
		currentContact->prevContact = NULL;
		count = 1;
	} else {
		while( currentContact->nextContact != NULL ){
			currentContact = currentContact->nextContact;
			++count;
		}
		currentContact->nextContact = contact;
		currentContact->nextContact->prevContact = currentContact;
		currentContact->nextContact->nextContact = NULL;
		++count;
	}

	return( count );
}

int removeContact( contactsType *headContact, contactsType *contact ){
	printw( "removeContact function entered" );
	return( 0 );
}

int sortContact( contactsType **headContact, sortType sort, columnType column ){
	printw( "sortContact function entered" );
	return( 0 );
}
