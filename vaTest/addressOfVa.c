/*
 * Name: addressOfVa.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Test how addresses work in va_start. 
 * Vers: 1.0.0 08/24/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int sum( int count, ... );

int main( void ){
    printf( "%d\n", sum( 4, 1, 2, 3, 4 ));
    return( 0 );
}

int sum( int count, ... ){
    int total = 0;
    int *tmp;
    va_list ap;

    va_start( ap, count );
    for( int i = 0; i < count; ++i ){
        tmp = &va_arg( ap, int );
        printf( "%p\n", tmp );
        total += *tmp;
    }
}
