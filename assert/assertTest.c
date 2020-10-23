/*
 * Name: assertTest.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Testing the assert function. 
 * Vers: 1.0.0 09/15/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main ( int argc, char **argv ){
    int trip;

    printf( "Enter 0 to trigger the assert:\n" );
    scanf( "%d", &trip );
    assert( trip );
    printf( "This occurs after the assert\n" );

    return( EXIT_SUCCESS );
}
