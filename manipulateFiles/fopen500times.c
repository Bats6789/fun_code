#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ){
	FILE *file;

	printf("====================================================\n");
	for( int i = 0; i < 500; ++i ){
		file = fopen( "test.txt", "w" );
		printf( "%d = %p\n", i, file );
	}
	printf("====================================================\n");
	return( 0 );
}
