/*
 * Name: list.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A file containing linked List functions.  
 * Vers: 1.0.0 09/18/2020 CBW - Original code.
 */

#include "list.h"

void printList( list *headNode ){
    list *currentNode;

    currentNode = headNode;

    while( currentNode != NULL ){
        printf( "node location = %p\n data = %d, next = %p\n", currentNode, currentNode->data, currentNode->next );
        currentNode = currentNode->next;
    }
}

list *createList( int num[], int size ){
    list *headNode;
    list *currentNode;

    headNode = NULL;

    for( int i = 0; i < size; ++i ){
        if( i == 0 ){
            headNode = (list *)malloc( sizeof( list ));
            currentNode = headNode;
        } else {
            currentNode->next = (list *)malloc( sizeof( list ));
            currentNode = currentNode->next;
        }
        currentNode->data = num[ i ];
        currentNode->next = NULL;
    }

    return( headNode );
}

doubleList *createDoubleList( int num[], int size ){
    doubleList *headNode;
    doubleList *currentNode;

    headNode = NULL;

    for( int i = 0; i < size; ++i ){
        if( i == 0 ){
            headNode = (doubleList *)malloc( sizeof( doubleList ));
            currentNode = headNode;
            currentNode->prev = NULL;
        } else {
            currentNode->next = (doubleList *)malloc( sizeof( doubleList ));
            currentNode->next->prev = currentNode;
            currentNode = currentNode->next;
        }
        currentNode->data = num[ i ];
        currentNode->next = NULL;
    }

    return( headNode );
}

void printDoubleList( doubleList *headNode ){
    doubleList *currentNode;

    currentNode = headNode;

    while( currentNode != NULL ){
        printf( "node location = %p\n prev = %p data = %d, next = %p\n", currentNode, currentNode->prev, currentNode->data, currentNode->next );
        currentNode = currentNode->next;
    }
}
