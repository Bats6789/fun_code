/*
 * Name: tictactoe.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A game of tictactoe with minimax algorithm. 
 * Vers: 1.0.0 04/13/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int nextMove( int board[ 9 ], int level, int piece, int isAITurn, difficultyType difficulty );
int setBoard( int board[ 9 ] );
int printBoard( int board[ 9 ] );
int getFreeSpaces( int board[ 9 ] );
int boardResults( int board[ 9 ], int piece );
int singlePlayerGame( int board[ 9 ], int playerOnePiece, int playerTwoPiece, int playerTurn, difficultyType difficulty );
int multiPlayerGame( int board[ 9 ] );

int main ( int argc, char **argv ) { 
        int board[ 9 ];
        int quit;
        int gameMode;
        int playerTurn;
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
        if( setBoard( board ) != EXIT_SUCCESS ){
                fprintf( stderr, "ERROR: Something went wrong on initial setup\n" );
                return( EXIT_FAILURE );
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
                        printf( "How many players? (1 or 2)\n" );
                        numOfPlayers = getchar();
                        while( getchar() != '\n' ); // buffer clearing
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
                        if( singlePlayerGame( board, playerOnePiece, playerTwoPiece, playerTurn, hard ) == -1 ){
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
                        if( multiPlayerGame( board ) == -1 ){
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
 *      int board[ 9 ] - the tic tac toe board
 *      int level - how deep has the algorithm searched.
 *      int place - where should it place a piece.
 *      int piece - the piece the AI is using.
 *      int isAITurn - is it the AI's turn.
 *      difficultyType difficulty - the difficulty.
 */
int nextMove( int board[ 9 ], int level, int piece, int isAITurn, difficultyType difficulty ) {
        int move;
        int currentOutcome;
        int outcome;
        int opponentPeice;

        move = 0;
        opponentPeice = ( piece == X ) ? O : X;
        if(  level == 0 ){
                currentOutcome = -2;
                for( int i = 0; i < 9; ++i ){
                        if( board[ i ] == EMPTY ){
                                board[ i ] = piece;
                                outcome = nextMove( board, 1, piece, 0, difficulty );
                                board[ i ] = EMPTY;
                                if( outcome > currentOutcome ){
                                        move = i;
                                        currentOutcome = outcome;
                                }
                        }
                }
        } else {
                outcome = boardResults( board, piece );
                if( outcome != -2 ){
                        return( outcome );
                }
                if( isAITurn == 1 ){
                        currentOutcome = -2;
                        for( int i = 0; i < 9; ++i ){
                                if( board[ i ] == EMPTY ){
                                        board[ i ] = piece;
                                        outcome = nextMove( board, level + 1, piece, 0, difficulty );
                                        board[ i ] = EMPTY;
                                        if( outcome > currentOutcome ){
                                                move = i;
                                                currentOutcome = outcome;
                                        }
                                }
                        }
                        return( currentOutcome );
                } else if( isAITurn == 0 ){
                        currentOutcome = 2;
                        for( int i = 0; i < 9; ++i ){
                                if( board[ i ] == EMPTY ){
                                        board[ i ] = opponentPeice;
                                        outcome = nextMove( board, level + 1, piece, 1, difficulty );
                                        board[ i ] = EMPTY;
                                        if( outcome < currentOutcome ){
                                                move = i;
                                                currentOutcome = outcome;
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
 *      int board[ 9 ] - the tic tac toe board
 */
int setBoard( int board[ 9 ] ) {
        int results;
        int i;

        for( i = 0; i < 9; ++i ){
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
 *      int board[ 9 ] - the tic tac toe board
 */
int printBoard( int board[ 9 ] ) {
        int results;
        int i;
        char piece;

        printf( "\n\n" );
        for( i = 0; i < 9; ++i ){
                if( i % 3 == 0 ){
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
                if( i == 2 || i == 5 ){
                        printf( "     " );
                        for( int j = 0; j < 3; ++j ){
                                putchar( '1' + ( i - 2 + j ) );
                                if( j != 2 ){
                                        putchar( '|' );
                                }
                        }
                        printf( "\n   -----     -----\n" );
                } else if( i != 8 ){
                        putchar( '|' );
                }
        }
        printf( "     " );
        for( int j = 0; j < 3; ++j ){
                putchar( '1' + ( i - 3 + j ) );
                if( j != 2 ){
                        putchar( '|' );
                }
        }
        printf( "\n\n" );
        if( i == 9 ){
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
 *      int board[ 9 ] - the board.
 *      int piece - the piece the AI is using.
 */
int boardResults( int board[ 9 ], int piece ) {

        for( int i = 0; i < 3; ++i ){
                if( board[ 3 * i + 0 ] == board[ 3 * i + 1 ] && 
                                board[ 3 * i + 1 ] == board[ 3 * i + 2 ] &&
                                board[ 3 * i + 0 ] != EMPTY ){
                        return(( board[ 3 * i + 0 ] == piece ) ? 1 : -1 );
                } else if( board[ 0 + i ] == board[ 3 + i ] &&
                                board[ 3 + i ] == board[ 6 + i ] &&
                                board[ 0 + i ] != EMPTY ){
                        return(( board[ 0 + i] == piece ) ? 1 : -1 );
                }
        }

        if( board[ 0 ] == board[ 4 ] && board[ 4 ] == board[ 8 ] && board[ 4 ] != EMPTY ){
                return(( board[ 4 ] == piece ) ? 1 : -1 );
        } else if( board[ 2 ] == board[ 4 ] && board[ 4 ] == board[ 6 ] && board[ 4 ] != EMPTY ){
                return(( board[ 4 ] == piece ) ? 1 : -1 );
        }

        for( int i = 0; i < 9; ++i ){
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
 *      int board[ 9 ] - the board.
 *      int playerOnePiece - the AI's piece.
 *      int playerTwoPiece - the player's piece.
 *      int playerTurn - Who goes first.
 *      difficultyType difficulty - the difficulty.
 */
int singlePlayerGame( int board[ 9 ], int playerOnePiece, int playerTwoPiece, int playerTurn, difficultyType difficulty ) {
        int move;
        int results;
        char key;

        results = -2;
        setBoard( board ); 
        printBoard( board );
        while( results == -2 ){
                if( playerTurn == 1 ){
                        move = nextMove( board, 0, playerOnePiece, 1, difficulty );
                        printf( "The AI is making its move.\n" );
                        board[ move ] = playerOnePiece;
                        printBoard( board );
                        playerTurn = 2;
                } else if( playerTurn == 2 ){
                        printf( "Your turn.\n" );
                        key = getchar();
                        while( getchar() != '\n' );
                        if( key >= '1' && key <= '9' && board[ key - '1' ] == EMPTY ){
                                board[ key - '1' ] = playerTwoPiece;
                                printBoard( board );
                                playerTurn = 1;
                        } else if(( key & '_') == 'Q'  ){
                                printf( "Quitting game.\n" );
                                return( -1 );
                        } else {
                                printf( "Invalid move.\n" );
                                printBoard( board );
                        }
                }
                results = boardResults( board, playerOnePiece );
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
 *      int board[ 9 ] - the board.
 */
int multiPlayerGame( int board[ 9 ] ) {
        int results;
        int playerTurn;
        char key;

        results = -2;
        playerTurn = 1;
        setBoard( board );
        printBoard( board );
        while( results == -2 ){
                if( playerTurn == 1 ){
                        printf( "Player 1's turn.\n" );
                        key = getchar();
                        while( getchar() != '\n' );
                        if( key >= '1' && key <= '9' && board[ key - '1' ] == EMPTY ){
                                board[ key - '1' ] = X;
                                printBoard( board );
                                playerTurn = 2;
                        } else if(( key & '_') == 'Q'  ){
                                printf( "Quitting game.\n" );
                                return( -1 );
                        } else {
                                printf( "Invalid move.\n" );
                                printBoard( board );
                        }
                } else if( playerTurn == 2 ){
                        printf( "Player 2's turn.\n" );
                        key = getchar();
                        while( getchar() != '\n' );
                        if( key >= '1' && key <= '9' && board[ key - '1' ] == EMPTY ){
                                board[ key - '1' ] = O;
                                printBoard( board );
                                playerTurn = 1;
                        } else if(( key & '_') == 'Q'  ){
                                printf( "Quitting game.\n" );
                                return( -1 );
                        } else {
                                printf( "Invalid move.\n" );
                                printBoard( board );
                        }
                }
                results = boardResults( board, X );
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
