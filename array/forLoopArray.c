#include <stdio.h>
#include <windows.h>
#include <time.h>

#define DOUBLE_VECTOR_SIZE 200000

int main( int argc, char **argv ){
	FILETIME beforetv;
	FILETIME aftertv;
	double doubleVector[ DOUBLE_VECTOR_SIZE ];
	GetSystemTimeAsFileTime( &beforetv );

	for( int index = 0; index < DOUBLE_VECTOR_SIZE; ++index ){
		doubleVector[ index ] = 0;
	}
	GetSystemTimeAsFileTime( &aftertv );
	for( int index = 0; index < DOUBLE_VECTOR_SIZE; ++index ){
		printf( "%lf\n", doubleVector[ index ] );
	}
	printf( "Took %ul microseconds\n", aftertv.dwLowDateTime - beforetv.dwLowDateTime );
	printf( "done\n" );
	return( 0 );
}
