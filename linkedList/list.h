/*
 * Name: list.h
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A file containing linked List functions. 
 * Vers: 1.0.0 09/18/2020 CBW - Original code.
 */

#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int data;
    struct list *next;
} list;

typedef struct doubleList {
    int data;
    struct doubleList *next;
    struct doubleList *prev;
} doubleList;

/* 
 * Name: createList
 * Desc: Creates a singley-linked list. 
 * Args: 
 * 	int num[] - an array of integers to convert to a linked list.
 * 	int size - the size of the array.
 */
list *createList( int num[], int size );

/* 
 * Name: printList
 * Desc: Prints a singley-linked list. 
 * Args: 
 * 	list *headNode - the start of the list.
 */
void printList( list *headNode );

/* 
 * Name: createDoubleList
 * Desc: Creates doubley-linked list.
 * Args: 
 * 	int num[] - an array of integers to convert to a linked list.
 * 	int size - the size of the array.
 */
doubleList *createDoubleList( int num[], int size );

/* 
 * Name: printDoubleList
 * Desc: Prints a doubley-linked list.
 * Args: 
 * 	doubleList *headNode - the start of the list.
 */
void printDoubleList( doubleList *headNode );

#endif
