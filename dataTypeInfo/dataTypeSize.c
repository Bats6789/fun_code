/*
 * Name: dataTypeSize.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Displays the size of multiple data types. 
 * Vers: 1.0.0 08/26/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ){
    printf( "+===========================================+\n" );
    printf( "|                    INT                    |\n" );
    printf( "+-------------------------------------------+\n" );
    printf( "| short int   %29d |\n", sizeof( short int ));
    printf( "| int         %29d |\n", sizeof( int ));
    printf( "| long int    %29d |\n", sizeof( long int ));
    printf( "+-------------------------------------------+\n" );
    printf( "|                   CHAR                    |\n" );
    printf( "+-------------------------------------------+\n" );
    printf( "| char        %29d |\n", sizeof( char ));
    printf( "+-------------------------------------------+\n" );
    printf( "|                   FLOAT                   |\n" );
    printf( "+-------------------------------------------+\n" );
    printf( "| float       %29d |\n", sizeof( float ));
    printf( "+-------------------------------------------+\n" );
    printf( "|                  DOUBLE                   |\n" );
    printf( "+-------------------------------------------+\n" );
    printf( "| double      %29d |\n", sizeof( double ));
    printf( "| long double %29d |\n", sizeof( long double ));
    printf( "+===========================================+\n" );
    return( EXIT_SUCCESS );
}
