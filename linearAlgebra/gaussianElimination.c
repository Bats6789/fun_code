/*
 * Name: gaussianElimination.c
 * Auth: Blake Wingard
 * Desc: Performs gaussian elimination on a file.
 * Vers: 1.0.0 04/02/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main( int argc, char **argv ){
	char *inputFilename;
	char *outputFilename;
	int size;
	int count;
	int nonZeroFlag;
	int zeroRowCount;
	double scale;
	FILE *inputFile;
	FILE *outputFile;

	zeroRowCount = 0;

	if( argc < 2 ){
		// help
	} else if( argc == 2 ){
		outputFilename = malloc( sizeof( char ) * 11 );
		if( outputFilename == NULL || strcmp( argv[ 1 ], "/d" ) == 0 ){
			perror( "ERROR" );
			return( EXIT_FAILURE );
		}
		strcpy( outputFilename, "output.txt" );
	} else {
		outputFilename = argv[ 4 ];
	}
	inputFilename = argv[ 1 ];

	inputFile = fopen( inputFilename, "r" );
	if( inputFile == NULL ){
		perror( "ERROR" );
		return( EXIT_FAILURE );
	}

	outputFile = fopen( outputFilename, "w" );
	if( outputFile == NULL ){
		perror( "ERROR" );
		return( EXIT_FAILURE );
	}
	if( argc == 3 ){
		free( outputFilename );
	}

	if( fscanf( inputFile, "%d", &size ) == EOF ){
		perror( "ERROR" );
		fclose( inputFile );
		fclose( outputFile );
		return( EXIT_FAILURE );
	}

	if( size <= 0 ){
		fprintf( stderr, "ERROR: %d is an invalid size for square matrix\n", size );
		fclose( inputFile );
		fclose( outputFile );
		return( EXIT_FAILURE );
	}

	double matrix[ size * size ];
	int zeroRow[ size ];
	for( int i = 0; i < size; ++i ){
		zeroRow[ i ] = 0;
	}

	for( count = 0; count < size * size; ++count ){
		if( fscanf( "%lf%*c", &( matrix[ count ] )) == EOF ){
			perror( "ERROR" );
			fprintf( stderr, "Possible format issue.\n" );
			fclose( inputFile );
			fclose( outputFile );
			return( EXIT_FAILURE );
		}
	}
	fclose( inputFile );

	if( count != size * size ){
		fprintf( stderr, "ERROR: Not enough elements for the matrix.\n" );
		fprintf( stderr, "Needed: %d\n", size * size );
		fprintf( stderr, "Recieved: %d\n", count );
		fclose( outputFile );
		return( EXIT_FAILURE );
	}

	for( int row = 0; row < size - 1; ++row ){
		nonZeroFlag = 0;
		for( int currentRow = row; currentRow < size - 1; ++currentRow ){
			if( matrix[ row * size + row ] != 0 ){
				nonZeroFlag = 1;
				scale = -matrix[ ( currentRow + 1 ) * size + row ] 
					/ matrix[ row * size + row ];
				for( int col = row; col < size; ++col ){
					matrix[ ( currentRow + 1 ) * size + col ] += 
						scale * matrix[ row * size + col ];
				}
			}
		}
	}

	return( EXIT_SUCCESS );
}
