/*
 * Name: FILEStructDemo.c
 * Auth: Blake Wingard
 * Desc: Demonstrates the elements of a FILE structure.
 * Vers: 1.0.0 03/27/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main( int argc, char **argv ){
	FILE *file;
	char chunk;

	chunk = '\0';

	if( argc == 1 ){
		fprintf( stderr, "ERROR: Not enough arguments.\n" );
	} else {
		file = fopen( argv[ 1 ], "r" );
		if( file == NULL ){
			perror( "ERROR" );
		} else {
			do{
				printf( "file->_ptr %p\n", file->_ptr );
				printf( "file->_cnt %d\n", file->_cnt );
				printf( "file->_base %p\n", file->_base );
				printf( "file->_flag %d\n", file->_flag );
				printf( "file->_file %d\n", file->_file );
				printf( "file->_charbuf %d\n", file->_charbuf );
				printf( "file->_bufsiz %d\n", file->_bufsiz );
				printf( "file->_tmpfname %p\n", file->_tmpfname );
				printf( "%c\n", chunk );

			} while( fscanf( file, "%c", &chunk ) != EOF );
		}
	}

	return( EXIT_SUCCESS );
}
