/*
 * Name: intToBinaryString.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc:  
 * Vers: 1.0.0 08/13/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>

char *intToBinaryString( int num );

int main ( int argc, char **argv ){
    int num;
    char *data;

    if( argc < 2 ){
        printf( "Please enter a int:\n" );
        scanf( "%d", &num );
    } else {
        num = atoi( argv[ 1 ] );
    }

    data = intToBinaryString( num );
    printf( "%d = ", num );
    for( int i = 0; i < 33; ++i ){
        if( i % 4 == 0 ){
            printf( " " );
        }
        printf( "%c", data[ i ] );
        /*
           if(( i + 1 ) % 8 == 0 ){
           printf( " " );
           }
           */
    }
    printf( "\n" );
    free( data );

    return( EXIT_SUCCESS );
    return( EXIT_SUCCESS );
}

char *intToBinaryString( int num ){
    char *string;

    string = (char *)malloc( sizeof( char ) * 33 );

    for( int i = 0; i < 32; ++i ){
        string[ 31 - i ] = num % 2 + '0';
        num >>= 1;
    }
    string[ 32 ] = '\0';
    return( string );
}
