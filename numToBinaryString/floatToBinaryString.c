/*
 * Name: floatToBinaryString.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Converts a floating point number to a binary string. 
 * Vers: 1.0.0 08/13/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>

#define NUM_DATA_SIZE 32

char *floatToBinaryString( float num );

typedef union {
    float num;
    unsigned numData;
} numToData;

int main ( int argc, char **argv ){
    float num;
    char *data;

    if( argc < 2 ){
        printf( "Please enter a float:\n" );
        scanf( "%f", &num );
    } else {
        num = atof( argv[ 1 ] );
    }

    data = floatToBinaryString( num );
    printf( "%f = ", num );
    for( int i = 0; i < 33; ++i ){
        if( i == 1 || i == 9 ){
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
}

/* 
 * Name: floatToBinaryString
 * Desc: Converts a float to a binary string representation. 
 * Args:
 *      float num - the number being converted.
 */
char *floatToBinaryString( float num ) {
    char *string;
    numToData floatData;

    string = (char *)malloc( sizeof( char ) * 33 );
    floatData.num = num;

    for( int i = 0; i < 32; ++i ){
        string[ 31 - i ] = (( floatData.numData & 1 ) == 1 ) ? '1' : '0';
        floatData.numData = floatData.numData >> 1;
    }
    string[ 32 ] = '\0';
    return( string );
}
