#include <stdio.h>
#include <windows.h>
#include <string.h>

#define DOUBLE_VECTOR_SIZE 200000

int main( int argc, char **argv ){
	FILETIME beforetv;
	FILETIME aftertv;
	double doubleVector[ DOUBLE_VECTOR_SIZE ];
	GetSystemTimeAsFileTime( &beforetv );

	memset( doubleVector, 0.0, sizeof( double ) * DOUBLE_VECTOR_SIZE );

	GetSystemTimeAsFileTime( &aftertv );
	for( int index = 0; index < DOUBLE_VECTOR_SIZE; ++index ){
		printf( "%lf\n", doubleVector[ index ] );
	}
	printf( "Took %ul microseconds\n", aftertv.dwLowDateTime - beforetv.dwLowDateTime );
	printf( "done\n" );
	return( 0 );
}

