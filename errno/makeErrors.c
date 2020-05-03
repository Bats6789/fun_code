/*
 * Name: makeErrors.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Prints a bunch of error messages found in strerror. 
 * Vers: 1.0.0 05/03/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ( int argc, char **argv ){
        for( int i = 0; i < 44; ++i ){
                fprintf( stdout, "%d = %s\n", i, strerror( i ));
        }
        return( EXIT_SUCCESS );
}
