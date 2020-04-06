#include <stdio.h>

/*
 * While it converts all lowercase to uppercase.
 * Other characters can be influenced in a negative way.
 * For example, using this eleminates all numbers (0 - 9).
 */

int main( int argc, char **argv ){

	for( char i = 0; i < 128 && i >= 0; ++i ){
		printf( "%d = %c    ", (int)i, i & '_' );
		if( i % 3 == 2 ){
			printf( "\n" );
		}

	}
	return( 0 );
}
