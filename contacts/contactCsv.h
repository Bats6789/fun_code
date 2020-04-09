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
	firstName = 1 << 0,
	middleName = 1 << 1,
	lastName = 1 << 2,
	phoneNumber = 1 << 3,
	address = 1 << 4,
	state = 1 << 5,
	zipcode = 1 << 6
} columnType;

/* 
 * Name: importContact
 * Desc: Imports contacts from a list into a head node. 
 * Args: 
 * 	<+args+>
 */
int importContact( contactsType **headContact, char *fileName );

/* 
 * Name: exportContact
 * Desc: Exports the contacts to a file. (in csv format) 
 * Args: 
 * 	contactsType *headContact - the head node of the contact list.
 * 	char *fileName - the name of the file.
 */
int exportContact( contactsType *headContact, char *fileName );

/* 
 * Name: addContact
 * Desc: Adds a contact to the list. 
 * Args: 
 * 	contactsType *headContact - the head node of the contact list.
 * 	contactsType *contact - the contact being added.
 */
int addContact( contactsType *headContact, contactsType *contact );

/* 
 * Name: removeContact
 * Desc: Removes a contact from the list. 
 * Args: 
 * 	contactsType **headContact - the address head node of the contact list.
 * 	contactsType *contact - the contact being removed.
 */
int removeContact( contactsType **headContact, contactsType *contact );

/* 
 * Name: sortContact
 * Desc: Sorts the contacts by a specified column in a specified order.
 * Args: 
 * 	contactsType **headContact - the address of the head node.
 * 	sortType sort - the method of sorting (ascending descending)
 * 	columnType column - the column being sorted.
 */
int sortContact( contactsType **headContact, sortType sort, columnType column );

/* 
 * Name: compareContact
 * Desc: Compares Two contacts to each other. 
 * Args:
 * 	contactsType firstContact - the first contact
 * 	contactsType secondContact - the second contact
 * 	columnType column - the column being used for the comparison.
 */
int compareContact( contactsType firstContact, contactsType secondContact, columnType column );

/* 
 * Name: getContact
 * Desc: Gets a contact. 
 * Args:
 * 	contactsType *headContact - the head node of the contact list.
 * 	const char *columnName - the name of the column being obtiained.
 * 	columnType column - the column being compared.
 */
contactsType *getContact( contactsType *headContact, const char *columnName, columnType column );

/* 
 * Name: strcmpContact
 * Desc: Compares a contact to a string. 
 * Args:
 * 	contactsType contact - the contact being compared to.
 * 	const char *columnName - the name of the column.
 * 	columnType column - the column being compared.
 */
int strcmpContact( contactsType contact, const char *columnName, columnType column );
#endif
