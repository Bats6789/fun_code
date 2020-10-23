/*
 * Name: linkedList.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A linked list example. 
 * Vers: 1.0.0 09/18/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#define ARRAY_SIZE 9

int main ( int argc, char **argv ){
    doubleList *headNode;
    int array[ ARRAY_SIZE ];

    srand( time(NULL) );

    for( int i = 0; i < ARRAY_SIZE; ++i ){
        array[ i ] = rand() % ARRAY_SIZE;
    }

    printf( "%zu\n", sizeof( doubleList ));
    headNode = createDoubleList( array, ARRAY_SIZE );
    // headNode = (struct doubleDoubleList *)malloc( sizeof( struct doubleList ));   

    // (*headNode).data = 3;   
    // headNode->data = 3;   
    // headNode->next = NULL;   

    // headNode->next = (struct doubleDoubleList *)malloc( sizeof( struct doubleList ));   
    // headNode->next->data = 4;   
    // headNode->next->next = NULL;        

    printDoubleList( headNode );


    return( EXIT_SUCCESS );
}



