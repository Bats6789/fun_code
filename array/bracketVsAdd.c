/*
 * Name: bracketVsAdd.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Compares indexing with brackets vs adding. 
 * Vers: 1.0.0 10/20/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10


int main ( int argc, char **argv ){
    int array[ SIZE ];

    for( int i = 0; i < SIZE; ++i ){
        array[ i ] = i;
    }

    printf( "VALUES:\n" );
    for( int i = 0; i < SIZE; ++i ){
        printf( "=====================================\n" );
        printf( "array[ %d ]                      = %d\n",i, array[ i ] );
        printf( "*(array + %d)                    = %d\n",i, *(array + i ));
        printf( "*(array + %d * sizeof( int ))    = %d\n",i, *(array + i * sizeof( int )));
    }
    printf( "=====================================\n" );
    printf( "ADDRESS:\n" );
    for( int i = 0; i < SIZE; ++i ){
        printf( "=====================================\n" );
        printf( "&array[ %d ]                     = %p\n",i, &array[ i ] );
        printf( "(array + %d)                     = %p\n",i, (array + i ));
        printf( "(array + %d * sizeof( int ))     = %p\n",i, (array + i * sizeof( int )));
    }
    printf( "=====================================\n" );
    return( EXIT_SUCCESS );
}
