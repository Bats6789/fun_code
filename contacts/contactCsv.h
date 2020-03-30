/*
 * Name: contactCsv.h
 * Desc: The csv manager for contacts.
 * Auth: Blake Wingard
 * Vers: 1.0.1 03/28/2020 CBW - Changed structure elements to static arrays.
 * Vers: 1.0.0 02/13/2020 CBW - Original code.
 */

#ifndef _CONTACT_CSV_H_
#define _CONTACT_CSV_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#define FIRST_NAME_SIZE 150
#define MIDDLE_NAME_SIZE 150
#define LAST_NAME_SIZE 150
#define PHONE_NUMBER_SIZE 26
#define ADDRESS_SIZE 100
#define STATE_SIZE 100
#define ZIPCODE_SIZE 20

typedef struct contactsType {
	char firstName[ FIRST_NAME_SIZE ];
	char middleName[ MIDDLE_NAME_SIZE ];
	char lastName[ LAST_NAME_SIZE ];
	char phoneNumber[ PHONE_NUMBER_SIZE ];
	char address[ ADDRESS_SIZE ];
	char state[ STATE_SIZE ];
	char zipcode[ ZIPCODE_SIZE ];
	struct contactsType *nextContact;
	struct contactsType *prevContact;
} contactsType;

typedef enum sortType {
	ascending, decending
} sortType;

typedef enum sortColumnType {
	firstName, middleName, lastName, phoneNumber, address, state, zipcode
} columnType;

int importContact( contactsType **headContact, char *fileName );

int exportContact( contactsType *headContact, char *fileName );

int addContact( contactsType *headContact, contactsType *contact );

int removeContact( contactsType *headContact, contactsType *contact );

int sortContact( contactsType **headContact, sortType sort, columnType column );

#endif
