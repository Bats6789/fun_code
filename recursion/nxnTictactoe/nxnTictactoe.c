/*
 * Name: nxnTictactoe.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A game of tictactoe with minimax algorithm. 
 * Vers: 2.0.0 04/16/2020 CBW - Changed to support a nxn board.
 * Vers: 1.0.0 04/13/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EMPTY 0
#define X 1
#define O -1
#define DEBUG -1
#define SINGLE_PLAYER 1
#define MULTI_PLAYER 2
#define NO_MODE_SELCTED 0

typedef enum{
        easy = 3,
        medium = 6,
        hard = 9
} difficultyType;

int nextMove( int *board, int size, int alpha, int beta, int level, int piece, int isAITurn, difficultyType difficulty );
int setBoard( int *board, int size );
int printBoard( int *board, int size );
int getFreeSpaces( int *board, int size );
int boardResults( int *board, int size, int piece );
int singlePlayerGame( int *board, int size, int playerOnePiece, int playerTwoPiece, int playerTurn, difficultyType difficulty );
int multiPlayerGame( int *board, int size );

int main ( int argc, char **argv ) { 
        int *board;
        int quit;
        int gameMode;
        int playerTurn;
        int size;
        char firstPlayer;
        char numOfPlayers;
        char playerOnePiece;
        char playerTwoPiece;
        char key;

        if( argc > 1 ){
                if( strcmp( argv[ 1 ], "/d" ) == 0 ){
                        gameMode = DEBUG;
                } else if( strcmp( argv[ 1 ], "/m" ) == 0 ){
                        gameMode = MULTI_PLAYER;
                } else if( strcmp( argv[ 1 ], "/s" ) == 0 ){
                        gameMode = SINGLE_PLAYER;
                } else {
                                gameMode = NO_MODE_SELCTED;
                }
        } else {
                gameMode = NO_MODE_SELCTED;
        }

        quit = 0;
        playerTurn = 0;
        if( gameMode != DEBUG && gameMode != SINGLE_PLAYER &&
                        gameMode != MULTI_PLAYER && gameMode != NO_MODE_SELCTED ){
                fprintf( stderr, "ERROR: Something went wrong in gameMode selection\n" );
                return( EXIT_FAILURE );
        }

        while( !quit ){
                if( gameMode == NO_MODE_SELCTED ){
                        printf( "How big do you want the board? (At least 3)\n" );
                        scanf( "%d", &size );
                        while( getchar() != '\n' );
                        board = (int *)malloc( sizeof( int ) * size * size );
                        printf( "How many players? (1 or 2)\n" );
                        numOfPlayers = getchar();
                        while( getchar() != '\n' );
                        switch( numOfPlayers ){
                                case '1':
                                        gameMode = SINGLE_PLAYER;
                                        break;
                                case '2':
                                        gameMode = MULTI_PLAYER;
                                        break;
                                case 'd':
                                case 'D':
                                        gameMode = DEBUG;
                                        break;
                                case 'q':
                                case 'Q':
                                        quit = 1;
                                        break;
                                default:
                                        printf("error: invalid option selected\n");
                                        printf( "press enter to continue..." );
                                        while( getchar() != '\n' ); // waits for enter and keeps the buffer clear
                                        break;

                        }
                        continue;
                } else {
                        if( gameMode == SINGLE_PLAYER ){
                                printf( "would you like to go first or second? (enter 1 or 2)\n" );
                                firstPlayer = getchar();
                                while( getchar() != '\n' );
                                switch( firstPlayer ){
                                        case '1':
                                                printf( "Single player selected.\n" );
                                                printf( "instruction:\n" );
                                                printf( "To quit at any time press Q.\n" );
                                                printf( "On your turn press 1-9 to place your piece in the corresponding square.\n" );
                                                playerTurn = 2;
                                                playerOnePiece = O;
                                                playerTwoPiece = X;
                                                break;
                                        case '2':
                                                printf( "Single player selected.\n" );
                                                printf( "instructions:\n" );
                                                printf( "To quit at any time press Q.\n" );
                                                printf( "On your turn press 1-9 to place your piece in the corresponding square.\n" );
                                                playerTurn = 1;
                                                playerOnePiece = X;
                                                playerTwoPiece = O;
                                                break;
                                        case 'q':
                                        case 'Q':
                                                quit = 1;
                                                break;
                                        default:
                                                printf("error: invalid option selected\n");
                                                printf( "press enter to continue..." );
                                                while( getchar() != '\n' ); // clear buffer and wait for enter
                                                continue;
                                                break;
                                }
                        } else if( gameMode == MULTI_PLAYER ){
                                printf( "Multi player selected.\n" );
                                printf( "instruction:\n" );
                                printf( "To quit at any time press Q.\n" );
                                printf( "On your turn press 1-9 to place your piece in the corresponding square.\n" );
                        } else if( gameMode == DEBUG ){
                                printf( "Debug mode selected.\n" );
                        }
                }
                if( gameMode == SINGLE_PLAYER ){
                        if( singlePlayerGame( board, size, playerOnePiece, playerTwoPiece, playerTurn, hard ) == -1 ){
                                quit = 1;
                        } else {
                                key = '\0';
                                while( key == '\0' ){
                                        printf( "Play again? (Y/N).\n" );
                                        key = getchar();
                                        while( getchar() != '\n' );
                                        if(( key & '_' ) == 'Y' ){
                                                quit = 0;
                                                gameMode = NO_MODE_SELCTED;
                                        }else if(( key & '_' ) == 'N' ){
                                                quit = 1;
                                        } else if(( key & '_' ) == 'Q' ){
                                                quit = 1;
                                        } else {
                                                printf( "Invalid option.\n" );
                                                key = '\0';
                                        }
                                }
                        }
                } else if( gameMode == MULTI_PLAYER ){
                        if( multiPlayerGame( board, size ) == -1 ){
                                quit = 1;
                        } else {
                                key = '\0';
                                while( key == '\0' ){
                                        printf( "Play again? (Y/N).\n" );
                                        key = getchar();
                                        while( getchar() != '\n' );
                                        if(( key & '_' ) == 'Y' ){
                                                quit = 0;
                                                gameMode = NO_MODE_SELCTED;
                                        }else if(( key & '_' ) == 'N' ){
                                                quit = 1;
                                        } else if(( key & '_' ) == 'Q' ){
                                                quit = 1;
                                        } else {
                                                printf( "Invalid option.\n" );
                                                key = '\0';
                                        }
                                }
                        }
                } else if( gameMode == DEBUG ){
                        printf( "DEBUG mode hasn't been implemented yet.\n" );
                        gameMode = NO_MODE_SELCTED;
                }
        }

        return( EXIT_SUCCESS );
}

/* 
 * Name: nextMove
 * Desc: Determines the next move for the AI 
 * Args:
 *      int *board - the tic tac toe board
 *      int size - the size of the board.
 *      int level - how deep has the algorithm searched.
 *      int place - where should it place a piece.
 *      int piece - the piece the AI is using.
 *      int isAITurn - is it the AI's turn.
 *      difficultyType difficulty - the difficulty.
 */
int nextMove( int *board, int size, int alpha, int beta, int level, int piece, int isAITurn, difficultyType difficulty ) {
        int move;
        int currentOutcome;
        int outcome;
        int opponentPeice;

        move = 0;
        opponentPeice = ( piece == X ) ? O : X;
        if(  level == 0 ){
                currentOutcome = -2;
                for( int i = 0; i < size * size; ++i ){
                        if( board[ i ] == EMPTY ){
                                board[ i ] = piece;
                                outcome = nextMove( board, size, alpha, beta, 1, piece, 0, difficulty );
                                board[ i ] = EMPTY;
                                if( outcome > currentOutcome ){
                                        move = i;
                                        currentOutcome = outcome;
                                }
                                if( currentOutcome == 1 ){
                                        return( move );
                                }
                        }
                }
        } else {
                outcome = boardResults( board, size, piece );
                if( outcome != -2 ){
                        return( outcome );
                }
                if( isAITurn == 1 ){
                        currentOutcome = -2;
                        for( int i = 0; i < size * size; ++i ){
                                if( board[ i ] == EMPTY ){
                                        board[ i ] = piece;
                                        outcome = nextMove( board, size, alpha, beta, level + 1, piece, 0, difficulty );
                                        board[ i ] = EMPTY;
                                        if( outcome > currentOutcome ){
                                                move = i;
                                                currentOutcome = outcome;
                                                alpha = currentOutcome;
                                        }
                                        if( beta <= currentOutcome ){
                                                return( currentOutcome );
                                        }
                                        if( currentOutcome == 1 ){
                                                return( currentOutcome );
                                        }
                                }
                        }
                        return( currentOutcome );
                } else if( isAITurn == 0 ){
                        currentOutcome = 2;
                        for( int i = 0; i < size * size; ++i ){
                                if( board[ i ] == EMPTY ){
                                        board[ i ] = opponentPeice;
                                        outcome = nextMove( board, size, alpha, beta, level + 1, piece, 1, difficulty );
                                        board[ i ] = EMPTY;
                                        if( outcome < currentOutcome ){
                                                move = i;
                                                currentOutcome = outcome;
                                                beta = currentOutcome;
                                        }
                                        if( alpha >= currentOutcome ){
                                                return( currentOutcome );
                                        }
                                        if( currentOutcome == -1 ){
                                                return( currentOutcome );
                                        }
                                }
                        }
                        return( currentOutcome );
                } else {
                        printf( "ERROR: Invalid option selected for isAITurn.\n" );
                        return( -99 );
                }
        }
        return( move );
}

/* 
 * Name: setBoard
 * Desc: Sets the board to all 0's (empty) 
 * Args:
 *      int *board - the tic tac toe board
 *      int size - the size of the board.
 */
int setBoard( int *board, int size ) {
        int results;
        int i;

        for( i = 0; i < size * size; ++i ){
                board[ i ] = EMPTY;
        }
        if( i == 9 ){
                results = EXIT_SUCCESS;
        } else {
                results = EXIT_FAILURE;
        }

        return( results );
}

/* 
 * Name: printBoard
 * Desc: Prints the board. 
 * Args:
 *      int *board - the tic tac toe board
 *      int size - the size of the board.
 */
int printBoard( int *board, int size ) {
        int results;
        int i;
        int numOfDigits;
        int currentNumOfDigits;
        char msg[20];

        numOfDigits = 0;
        currentNumOfDigits = 0;
        for( int digitNum = 0; ( size * size ) / (int)pow( 10.0, digitNum ) > 0; ++digitNum ){
                ++numOfDigits;
        }
        printf( "\n\n" );
        for( i = 0; i < size * size; ++i ){
                if( i % size == 0 ){
                        printf( "   " );
                }
                switch( board[ i ] ){
                        case O:
                                putchar( 'O' );
                                break;
                        case X:
                                putchar( 'X' );
                                break;
                        case EMPTY:
                                putchar( ' ' );
                                break;
                }
                if( i  % size == size - 1 && i != size * size - 1 ){ // do this for each row except the last
                        for( int j = 0; j < size; ++j ){
                                currentNumOfDigits = 0;
                                for( int digitNum = 0; ( i - size + 2 + j ) / (int)pow( 10.0, digitNum ) > 0; ++digitNum ){
                                        ++currentNumOfDigits;
                                }
                                fprintf( stderr, "Number = %d, currentNumOfDigits = %d,  ", i - size + 2 + j, currentNumOfDigits );
                                if( j == 0 ){
                                        sprintf( msg, "%%%dd", 6 );
                                        fprintf( stderr, "%s\n", msg );
                                        printf( msg, i - size + 2 + j );
                                } else {
                                        sprintf( msg, "%%%dd", numOfDigits );
                                        fprintf( stderr, "%s\n", msg );
                                        printf( msg, i - size + 2 + j );
                                }
                                if( j != size - 1 ){
                                        putchar( '|' );
                                }
                        }
                        printf( "\n   " );
                        for( int j = 0; j < size; ++j ){
                                // this next loop will run for each digit
                                putchar( '-' );
                                if( j != size - 1 ){
                                        putchar( '-' );
                                }
                        }
                        printf( "     " );
                        for( int j = 0; j < size; ++j ){
                                // this next loop will run for each digit
                                for( int k = 0; k < numOfDigits; ++k ){
                                        putchar( '-' );
                                }
                                if( j != size - 1 ){
                                        putchar( '-' );
                                }
                        }
                        printf( "\n" );
                } else if( i != size * size - 1 ){
                        putchar( '|' );
                }
        }
        for( int j = 0; j < size; ++j ){
                currentNumOfDigits = 0;
                for( int digitNum = 0; ( i - size + 1 + j ) / (int)pow( 10.0, digitNum ) > 0; ++digitNum ){
                        ++currentNumOfDigits;
                }
                fprintf( stderr, "Number = %d, currentNumOfDigits = %d,  ", i - size + 1 + j, currentNumOfDigits );
                if( j == 0 ){
                        sprintf( msg, "%%%dd", 6 );
                        fprintf( stderr, "%s\n", msg );
                        printf( msg, i - size + 1 + j );
                } else {
                        sprintf( msg, "%%%dd", numOfDigits );
                        fprintf( stderr, "%s\n", msg );
                        printf( msg, i - size + 1 + j );
                }
                if( j != size - 1 ){
                        putchar( '|' );
                }
        }
        printf( "\n\n" );
        if( i == size * size ){
                results = EXIT_SUCCESS;
        } else {
                results = EXIT_FAILURE;
        }

        return( results );
}
/* 
 * Name: boardResults
 * Desc: Obtains the win results. 
 * Args:
 *      int *board - the board.
 *      int size - the size of the board.
 *      int piece - the piece the AI is using.
 */
int boardResults( int *board, int size, int piece ) {
        int i;
        int j;

        for( i = 0; i < size; ++i ){
                // check if row is all the same and not empty
                for( j = 1; j < size && board[ i * size + 0 ] != EMPTY; ++j ){
                        if( board[ i * size + 0 ] != board[ i * size + j ] ){
                                j = size + 1;
                        } else {
                                // keep checking
                        }
                }
                if( j == size ){
                        return(( board[ i * size + 0 ] == piece ) ? 1 : -1 );
                }
                for( j = 1; j < size && board[ 0 * size + i ] != EMPTY; ++j ){
                        if( board[ 0 * size + i ] != board[ j * size + i ] ){
                                j = size + 1;
                        } else {
                                // keep checking
                        }
                }
                if( j == size ){
                        return(( board[ 0 * size + i ] == piece ) ? 1 : -1 );
                }
                // check if column is all the same and not empty
        }

        // check 0,0 to size,size diagonal
        for( j = 1; j < size && board[ 0 * size + 0 ] != EMPTY; ++j ){
                if( board[ 0 * size + 0 ] != board[ j * size + j ] ){
                        j = size + 1;
                }
        }
        if( j == size ){
                return(( board[ 0 * size + 0 ] == piece ) ? 1 : -1 );
        }
        // check 0,size to size,0 diagonal
        for( j = 1; j < size && board[ 0 * size + size - 1 ] != EMPTY; ++j ){
                if( board[ 0 * size + size - 1 ] != board[ j * size + size - j - 1 ] ){
                        j = size + 1;
                }
        }
        if( j == size ){
                return(( board[ 0 * size + size - 1 ] == piece ) ? 1 : -1 );
        }

        for( i = 0; i < size * size; ++i ){
                if( board[ i ] == EMPTY ){
                        return( -2 );
                }
        }

        return( 0 );
}

/* 
 * Name: singlePlayerGame
 * Desc: The game logic for a single player game. 
 * Args:
 *      int *board - the board.
 *      int size - the size of the board.
 *      int playerOnePiece - the AI's piece.
 *      int playerTwoPiece - the player's piece.
 *      int playerTurn - Who goes first.
 *      difficultyType difficulty - the difficulty.
 */
int singlePlayerGame( int *board, int size, int playerOnePiece, int playerTwoPiece, 
                int playerTurn, difficultyType difficulty ) { 
        int move;
        int results;
        int key;

        results = -2;
        setBoard( board, size ); 
        printBoard( board, size );
        while( results == -2 ){
                if( playerTurn == 1 ){
                        move = nextMove( board, size, -2, 2, 0, playerOnePiece, 1, difficulty );
                        printf( "The AI is making its move.\n" );
                        board[ move ] = playerOnePiece;
                        printBoard( board, size );
                        playerTurn = 2;
                } else if( playerTurn == 2 ){
                        printf( "Your turn.\n" );
                        key = getchar();
                        if(( key & '_' ) == 'Q' ){
                                printf( "Quitting game.\n" );
                                return( -1 );
                        } else if( key < '1' || key > '9' ){
                                printf( "Invalid move.\n" );
                                printBoard( board, size );
                        } else {
                                ungetc( key, stdin );
                                scanf( "%d", &key );
                        }
                        while( getchar() != '\n' );
                        if( board[ key - 1 ] == EMPTY ){
                                board[ key - 1 ] = playerTwoPiece;
                                printBoard( board, size );
                                playerTurn = 1;
                        } else {
                                printf( "Invalid move.\n" );
                        }
                }
                results = boardResults( board, size, playerOnePiece );
                if( results == 1 ){
                        printf( "Game over.\n" );
                        printf( "AI wins.\n" );
                        results = 1;
                        return( 0 );
                } else if( results == -1 ){
                        printf( "Game over.\n" );
                        printf( "Player wins.\n" );
                        results = 2;
                        return( 0 );
                } else if( results == 0 ){
                        printf( "Game over.\n" );
                        printf( "It's a tie.\n" );
                        results = 0;
                }
        }
        return( results );
}
/* 
 * Name: multiPlayerGame
 * Desc: The game logic for a multiplayer game. 
 * Args:
 *      int *board - the board.
 *      int size - the size of the board.
 */
int multiPlayerGame( int *board, int size ) {
        int results;
        int playerTurn;
        int key;

        results = -2;
        playerTurn = 1;
        setBoard( board, size );
        printBoard( board, size );
        while( results == -2 ){
                if( playerTurn == 1 ){
                        printf( "Player 1's turn.\n" );
                        key = getchar();
                        if(( key & '_' ) == 'Q' ){
                                printf( "Quitting game.\n" );
                                return( -1 );
                        } else if( key < '1' || key > '9' ){
                                printf( "Invalid move.\n" );
                                printBoard( board, size );
                        } else {
                                ungetc( key, stdin );
                                scanf( "%d", &key );
                        }
                        while( getchar() != '\n' );
                        if( board[ key - 1 ] == EMPTY ){
                                board[ key - 1 ] = X;
                                printBoard( board, size );
                                playerTurn = 2;
                        } else {
                                printf( "Invalid move.\n" );
                        }
                } else if( playerTurn == 2 ){
                        printf( "Player 2's turn.\n" );
                        key = getchar();
                        if(( key & '_' ) == 'Q' ){
                                printf( "Quitting game.\n" );
                                return( -1 );
                        } else if( key < '1' || key > '9' ){
                                printf( "Invalid move.\n" );
                                printBoard( board, size );
                        } else {
                                ungetc( key, stdin );
                                scanf( "%d", &key );
                        }
                        while( getchar() != '\n' );
                        if( board[ key - 1 ] == EMPTY ){
                                board[ key - 1 ] = O;
                                printBoard( board, size );
                                playerTurn = 1;
                        } else {
                                printf( "Invalid move.\n" );
                        }
                }
                results = boardResults( board, size, X );
                if( results == 1 ){
                        printf( "Game over.\n" );
                        printf( "Player 1 wins.\n" );
                        results = 1;
                        return( 0 );
                } else if( results == -1 ){
                        printf( "Game over.\n" );
                        printf( "Player 2 wins.\n" );
                        results = 2;
                        return( 0 );
                } else if( results == 0 ){
                        printf( "Game over.\n" );
                        printf( "It's a tie.\n" );
                        results = 0;
                }
        }
        return( results );
}
