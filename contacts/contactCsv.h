/*
 * Name: contactCsv.h
 * Desc: The csv manager for contacts.
 * Auth: Blake Wingard
 * Vers: 1.0.0 02/13/2020 CBW - Original code.
 */

#ifndef _CONTACT_CSV_H_
#define _CONTACT_CSV_H_

#include <string.h>
#include <curses.h>

typedef struct contactsType {
    char *firstName;
    char *middleName;
    char *lastName;
    char *phoneNumber;
    char *address;
    char *state;
    char *zipcode;
    struct contactsType *nextEvent;
    struct contactsType *prevEvent;
} contactsType;

typedef enum sortType {
    ascending, decending
} sortType;

typedef enum sortColumnType {
    firstName, middleName, lastName, phoneNumber, address, state, zipcode
} sortColumnType;

int importContact( contactsType **headContact, char *fileName );

int exportContact( contactsType *headContact, char *fileName );

int addContact( contactsType *headContact, contactsType *contact );

int removeContact( contactsType *headContact, contactsType *contact );

int sortContact( contactsType **headContact, sortType sort, sortColumnType column );

#endif
