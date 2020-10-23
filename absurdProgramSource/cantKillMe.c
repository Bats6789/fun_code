/*
 * Name: cantKillMe.c
 * Auth: Blake Wingard, bats23456789@gmail.com
 * Desc: A program that can't be killed using Ctrl-C. 
 * Vers: 1.0.0 09/03/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

void ABRT( int a );
void FPE( int a );
void ILL( int a );
void INT( int a );
void SEGV( int a );
void TERM( int a );

static jmp_buf buf;

int main ( int argc, char **argv ){
    int numerator;
    int denominator;
    int quotient;

    signal( SIGABRT, ABRT );
    signal( SIGFPE, FPE );
    signal( SIGILL, ILL );
    signal( SIGINT, INT );
    signal( SIGSEGV, SEGV );
    signal( SIGTERM, TERM );
    
    while( 1 ){
        setjmp( buf );
        printf( "Enter a numerator\n" );
        scanf( "%d", &numerator );
        printf( "Enter a denominator (Don't enter zero :P)\n" );
        scanf( "%d", &denominator );
        quotient = numerator / denominator;
        printf( "Your answer is\n" );
        printf( "This %d / %d is this %d\n", numerator, denominator, quotient );
        printf( "I'm not leaving your console though :P\n" );
    }
    return( EXIT_SUCCESS );
}

void ABRT( int a ){
    printf( "You can't abort me mortal!!!\n" );
    signal( SIGABRT, ABRT );
}

void FPE( int a ){
    printf( "You shouldn't devide by 0 :P\n" );
    signal( SIGFPE, FPE );
    longjmp( buf, 1 );
}

void ILL( int a ){
    printf( "This is illegal\n" );
    signal( SIGILL, ILL );
}

void INT( int a ){
    printf( "Stop interupting me!!!\n" );
    signal( SIGINT, INT );
    while( getchar() == 35);
}

void SEGV( int a ){
    printf( "I'm not allowed to go there\n" );
    signal( SIGSEGV, SEGV );
}

void TERM( int a ){
    printf( "I'm not gonna stop!!!\n" );
    signal( SIGTERM, TERM );
}
