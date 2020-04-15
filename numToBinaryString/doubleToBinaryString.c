/*
 * Name: doubleToBinaryString.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Converts a double to a binary string. 
 * Vers: 1.0.0 04/11/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>

#define NUM_DATA_SIZE 32

char *doubleToBinaryString( double num );

typedef union {
        double num;
        unsigned numData[ 2 ];
} numToData;

int main ( int argc, char **argv ){
        double num;
        char *data;

        if( argc < 2 ){
                printf( "Please enter a double:\n" );
                scanf( "%lf", &num );
        } else {
                num = atof( argv[ 1 ] );
        }

        data = doubleToBinaryString( num );
        printf( "%lf = ", num );
        for( int i = 0; i < 65; ++i ){
                if( i == 1 || i == 12 ){
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
 * Name: doubleToBinaryString
 * Desc: Converts a double to a binary string representation. 
 * Args:
 *      double num - the number being converted.
 */
char *doubleToBinaryString( double num ) {
        char *string;
        numToData doubleData;

        string = (char *)malloc( sizeof( char ) * 65 );
        doubleData.num = num;

        for( int i = 0; i < 64; ++i ){
                string[ 63 - i ] = (( doubleData.numData[ i / NUM_DATA_SIZE ] & 1 ) == 1 ) ? '1' : '0';
                doubleData.numData[ i / NUM_DATA_SIZE ] = doubleData.numData[ i / NUM_DATA_SIZE ] >> 1;
        }
        string[ 64 ] = '\0';
        return( string );
}
