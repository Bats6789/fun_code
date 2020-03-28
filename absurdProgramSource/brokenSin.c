#include <stdio.h>
#include <math.h>
#include <string.h>
#include "a34.h"

int testing( int x );
char *writeString( char *string );
void something( void );

int main( int argc, char **argv ){
	char string[ 20 ];
	strcpy( string, "testing" );

something:
	printf( "sin( 2 ) = %d\n", sin( 2 ));
	printf( "2 + 2 = %d\n", 2 + 2 );
	printf( "2 + 2 = %d\n", testing( 2 ));
	printf( "string = %s\n", writeString( string ));
	printf( "sizeof( double ) = %d\n", sizeof( double ));
	goto something;
	return( 0 );
}

int testing( int x ){
	return( x + x );
}

char *writeString( char *string ){
	return( string );
}

/*
void something( void ){
	printf("something\n" );
}
*/
