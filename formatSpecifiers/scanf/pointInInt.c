/*
 * Name: pointInDouble.c
 * Auth: Blake Wingard
 * Desc: Test a decimal point in a double.
 * Vers: 1.0.0 04/05/2020 CBW - Original code.
 */

#include <stdio.h>

int main( int argc, char **argv ){
	int num;

	printf( "Please enter a decimal:\n" );
	/* Doesn't work
	scanf( "%0.2lf", &num );
	*/
	scanf( "%d", &num );

	printf( "%0.2d\n", num );
	return( 0 );
}

