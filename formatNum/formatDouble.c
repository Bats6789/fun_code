/*
 * Name: formatDouble.c
 * Auth: Blake Wingard
 * Desc: Formats an integer to contain commas every three digits.
 * Vers: 1.0.0 02/21/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_CHUNK 50

char *formatDouble( double num, char *dilem );
char *formatInt( int num, char *dilem );
char *reverseString( char *str, int size );

int main( int argc, char **argv ){
	double num;

	if( argc < 3 ){
		fprintf( stderr, "ERROR: Please enter a number and the dilemeter\n" );
	} else {
		num = atof( argv[ 1 ] );
		printf( "Original = %70.50lf\n", num );
		printf( "Formatted = %s\n", formatDouble( num, argv[ 2 ] ));
	}
	return( EXIT_SUCCESS );
}

char *formatInt( int num, char *dilem ){
	char *str;
	char *tmpStr;
	int numChunk;
	int scale;
	int isNegative;
	int count;
	int strIndex;
	int dilemSize;

	scale = 1;
	numChunk = 0;
	str = malloc( sizeof( char ) * STR_CHUNK * scale );
	str[ 0 ] = '\0';
	count = 0;
	strIndex = 0;
	dilemSize = strlen( dilem );

	/*
	   if( dilemSize >= STR_CHUNK ){
	   free( str );
	   return( NULL );
	   }
	   */

	if( num < 0 ){
		isNegative = 1;
		num = -num;
	} else {
		isNegative = 0;
	}


	while( num != 0 ){
		if( count == 3 ){
			while( strIndex + dilemSize + 1 >= STR_CHUNK * scale ){
				++scale;
				str = realloc( str, sizeof( char ) * STR_CHUNK * scale );
			}
			strcat( str, dilem );
			strIndex += dilemSize;
			count = 0;
		}
		numChunk = num % 10;
		num /= 10;
		str[ strIndex ] = '0' + numChunk;
		++strIndex;
		if( strIndex == STR_CHUNK * scale ){
			++scale;
			str = realloc( str, sizeof( char ) * STR_CHUNK * scale );
		}
		str[ strIndex ] = '\0';
		++count;

	}
	if( str[ 0 ] == '\0' ){
		str[ 0 ] = '0';
		str[ 1 ] = '\0';
	} else {
		str = reverseString( str, strIndex - 1 );
	}
	if( isNegative ){
		tmpStr = malloc( sizeof( char ) * strlen( str ) + 2 );
		sprintf( tmpStr, "-%s", str );
		free( str );
		return( tmpStr );
	}
	return( str );
}

char *reverseString( char *str, int size ){
	char tmpChar;

	for( int index = 0; index < size / 2; ++index ){
		tmpChar = str[ index ];
		str[ index ] = str[ size - index ];
		str[ size - index ] = tmpChar;
	}

	return( str );
}

char *formatDouble( double num, char *dilem ){
	int tmpNum;
	int strSize;
	int index;
	char *str;

	tmpNum = num;
	num = num - (double)tmpNum;
	str = formatInt( tmpNum, dilem );
	strSize = strlen( str );
	index = strSize;
	str = realloc( str, sizeof( char ) * strSize * 2 + 1 );
	strSize = strSize * 2 + 1;
	if( num != 0.0 ){
		str[ index ] = '.';
		++index;
		str[ index ] = '\0';
	}
	while( num != 0.0 ){
		tmpNum = num * 10;
		num = num * 10 - (double)tmpNum;
		printf("%lf\n", num );
		str[ index ] = '0' + tmpNum;
		++index;
		if( index == strSize ){
			strSize = 2 * strSize;
			str = realloc( str, sizeof( char ) * strSize );
		}
		str[ index ] = '\0';
	}
	return( str );
}


