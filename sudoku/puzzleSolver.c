/*
 * Name: puzzleSolver.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: Solves a sudoku puzzle. 
 * Vers: 1.0.0 05/02/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int solver( int *board, int size );
int check( int *board, int size );
int copyBoard( int *dstBoard, int *srcBoard, int size );
int printBoard( int *board, int size );
void help( void );

int main ( int argc, char **argv ){ 
        int board[ 81 ];
        int results;
        FILE *inputFile;
        FILE *outputFile;

        if( argc < 3 ){
                help();
                return( -2 );
        }

        // open files
        inputFile = fopen( argv[ 1 ], "r" );
        if( inputFile == NULL ){
                fprintf( stderr, "ERROR with %s: %s\n", argv[ 1 ], strerror( errno ));
                return( -3 );
        }
        outputFile = fopen( argv[ 2 ], "w" );
        if( outputFile == NULL ){
                fprintf( stderr, "ERROR with %s: %s\n", argv[ 2 ], strerror( errno ));
                return( -4 );
        }

        // read in the input file
        for( int i = 0; i < 81; ++i ){
                fscanf( inputFile, "%d%*c", &board[ i ] );
        }

        fclose( inputFile );

        results = 0;
        results = solver( board, 9 );

        // write the results to the output file
        for( int i = 0; i < 81; ++i ){
                fprintf( outputFile, "%d", board[ i ] );
                if(( i + 1 ) % 9 == 0 ){
                        fprintf( outputFile, "\n" );
                } else {
                        fprintf( outputFile, "," );
                }
        }
        fclose( outputFile );

        return( results );
}

/* 
 * Name: solver
 * Desc: Solves a sudoku board of size size. 
 * Args:
 *      int *board - the board.
 *      int size - the size of one row on the board.
 */
int solver( int *board, int size ) {
        int newBoard[ size * size ];
        int results;

        copyBoard( newBoard, board, size );
        results = 0;
        for( int postition = 0; postition < 81 && results != 1; ++postition ){
                if( newBoard[ postition ] == 0 ){
                        for( int num = 1; num <= 9 && results <= 0; ++num ){
                                newBoard[ postition ] = num;
                                results = check( newBoard, size );
                                if( results == -1 ) {
                                        newBoard[ postition ] == 0;
                                } else if( results == 0 ){
                                        results = solver( newBoard, size );
                                }
                                if( results == 1 ) {
                                        copyBoard( board, newBoard, size );
                                        return( 1 );
                                }
                        }
                        return( -1 );
                }
        }
        // should never reach this point.
        return( -1 );
}

/* 
 * Name: check
 * Desc: Checks of solution is valid. 
 * Args:
 *      int *board - the board.
 *      int size - the size of one row on the board.
 */
int check( int *board, int size ) {
        int results;
        int bestResults;
        int checkVals[ size + 1 ];
        int row;
        int col;
        int box;
        int boxWidth;

        bestResults = 1;
        boxWidth = (int) sqrt( (double)size );
        // check rows
        for( row = 0; row < size; ++row ){
                for( int i = 0; i < size + 1; ++i ){
                        checkVals[ i ] = 0;
                }
                for( col = 0; col < size; ++col ){
                        checkVals[ board[ size * row + col ]]++;
                }
                if( checkVals[ 0 ] > 0 ){
                        bestResults = 0;
                }
                for(  int i = 1; i < size + 1; ++i ){
                        if( checkVals[ i ] > 1 ){
                                return( -1 );
                        }
                }
        }

        // check cols
        for( col = 0; col < size; ++col ){
                for( int i = 0; i < size + 1; ++i ){
                        checkVals[ i ] = 0;
                }
                for( row = 0; row < size; ++row ){
                        checkVals[ board[ size * row + col ]]++;
                }
                for(  int i = 1; i < size + 1; ++i ){
                        if( checkVals[ i ] > 1 ){
                                return( -1 );
                        }
                }
        }

        // check boxes
        for( box = 0; box < size; ++box ){
                for( int i = 0; i < size + 1; ++i ){
                        checkVals[ i ] = 0;
                }
                for( row = 0; row < boxWidth; ++row ){
                        for( col = 0; col < boxWidth; ++col ){
                                checkVals[ board[ ( row + ( box / boxWidth ) * boxWidth ) * size + 
                                        ( col + ( box % boxWidth ) * boxWidth )]]++;
                        } 
                }
                for(  int i = 1; i < size + 1; ++i ){
                        if( checkVals[ i ] > 1 ){
                                return( -1 );
                        }
                }
        }

        return( bestResults );
}

/* 
 * Name: copyBoard
 * Desc: Copies one board to another, 
 * Args:
 *      int *dstBoard - the board being copied to.
 *      int *srcBoard - the board making the copy.
 *      int size - the size of one row on the board.
 */
int copyBoard( int *dstBoard, int *srcBoard, int size ) {
        int count;
        for( count = 0; count < size * size; ++count ){
                dstBoard[ count ] = srcBoard[ count ];
        }
        return( count );
}

/* 
 * Name: printBoard
 * Desc: Prints the board. 
 * Args:
 *      int *board - the board.
 *      int size - the size of one row on the board.
 */
int printBoard( int *board, int size ) {
        int count;
        for( count = 0; count < size * size; ++count ){
                printf( "%d ", board[ count ] );
                if(( count + 1 ) % size == 0 ){
                        printf( "\n" );
                }
        }
        return( count );
}

/* 
 * Name: help
 * Desc: Prints help to the user. 
 */
void help( void ) {
        printf( "puzzleSolver usage:\n" );
        printf( "    puzzleSolver.exe <source board filename> <asnwer board filename>\n" );
}
