/*
 * Name: ticTacToe.c
 * Auth: Blake Wingard
 * Desc: Tic tac toe recreated in c
 * Vers: 1.0.0 07/31/2019 CBW - Original code
 */

#include <stdio.h>
#include <stdlib.h>

void printBoard( char boxContents[ 3 ][ 3 ] );
void initializeBoard( char boxContents[ 3 ][ 3 ], int spaceUsed[ 3 ][ 3 ] );

int main( int argc, char **argv ){
	char key;
	char botLetter;
	char playerLetter;
	char boxContents[ 3 ][ 3 ];
	int spaceUsed[ 3 ][ 3 ];
	int first;
	int spot;
	printf( "Want to play Tic Tac Toe?\ny/n - " );
	scanf( "%c%c", &key, NULL );
	switch( key ){
		case 'y':
		case 'Y':
			printf( "Let's begin\n" );
		break;
		case 'n':
		case 'N':
			printf( "Okay :(\n" );
			return( 1 );
		break;
		default:
			printf( "Wrong key >:(\n" );
			return( 1 );
		break;
	}
	initializeBoard( boxContents, spaceUsed );
	printBoard( boxContents );
	printf( "First or second?\n(1/2) - " );
	scanf( "%c%c", &key, NULL );
	switch( key ){
		case '1':
			first = 1;
		break;
		case '2':
			first = 0;
		break;
		default:
			printf( "Wrong key\n You're going second\n" );
			first = 0;
		break;
	}
	printf( "X or O?\n" );
	scanf( "%c%c", &key, NULL );
	switch( key ){
		case 'X':
		case 'x':
			botLetter = 'O';
			playerLetter = 'X';
		break;
		case 'O':
		case 'o':
			botLetter = 'X';
			playerLetter = 'O';
		break;
		default:
			printf( "Wrong letter\nYou're O's\n" );
			botLetter = 'X';
			playerLetter = 'O';
		break;
	}
	if( !first ){
		spaceUsed[ 0 ][ 0 ] = 1;
		boxContents[ 0 ][ 0 ] = botLetter;
		spot = playersMove( boxContents, spaceUsed );
		if( spot == 2 || spot == 6 ){
	
	} else {
	
	}
	
	return( 0 );
}

void printBoard( char boxContents[ 3 ][ 3 ] ){
	for( int colIndex = 0; colIndex < 3; ++colIndex ){
		for( int rowIndex = 0; rowIndex < 3; ++rowIndex ){
			printf( "%c", boxContents[ colIndex ][ rowIndex ] );
			if( rowIndex < 2 ){
				printf( "|" );
			}
		}
		printf( "\n" );
		if( colIndex < 2 ){
			printf( "-----\n");
		}
	}
}

void initializeBoard( char boxContents[ 3 ][ 3 ], int spaceUsed[ 3 ][ 3 ] ){
	for( int colIndex = 0; colIndex < 3; ++colIndex ){
		for( int rowIndex = 0; rowIndex < 3; ++rowIndex ){
			boxContents[ colIndex ][ rowIndex ] = ' ';
			spaceUsed[ colIndex ][ rowIndex ] = 0;
		}
	}
}
