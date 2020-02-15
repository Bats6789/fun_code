/*
 * Name: geometricProperties.c
 * Auth: Blake Wingard
 * Desc: Calculates the properties of geometric shapes
 * Vers: 1.0.0 02/12/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ncurses.h>

#define PI approximate_pi()
#ifdef WIN32
#define BACKSPACE 8
#else
#define BACKSPACE 127
#endif
#define ENTER 13
#define ESC 27
#define TAB 9

int circle( int maxY, int maxX );
int rectangle( int maxY, int maxX );
int triangle( int maxY, int maxX );
int ellipse( int maxY, int maxX );
int polygon( int maxY, int maxX );
int stringCompareI( const char *firstString, const char *secondString );
int printHelp( int startY, int startX );

// from p3
double approximate_pi(void); // used to approximate PI since it is not reliably 
int get_circle_properties( double radius, int maxY, int maxX, int startY, int startX );
int get_rectangle_properties( double length, double width, int maxY, int maxX, int startY, int startX);
int get_triangle_properties( double a, double b, double gamma, int maxY, int maxX, int startY, int startX );
int get_ellipse_properties( double a, double b, int maxY, int maxX, int startY, int startX );
int get_regular_polygon_properties( int n, double s, int maxY, int maxX, int startY, int startX );

int main( int argc, char **argv ){
	int quit;
	int screenMiddleX;
	int maxX;
	int maxY;
	int index;
	int chunk;
	char input[16];

	quit = 0;
	index = 0;
	input[ index ] = '\0';
	chunk = '\0';

	initscr();
	raw();
	getmaxyx( stdscr, maxY, maxX );
	screenMiddleX = maxX / 2;
	curs_set( 0 );
	noecho();

	while( quit != 1 ){
		// display basic information
		border( '|', '|', '-', '-', '+', '+', '+', '+' );
		mvprintw( 4, screenMiddleX - 22, "Please enter a shape from the following list:" );
		mvprintw( 5, screenMiddleX - 22, "Circle" );
		mvprintw( 6, screenMiddleX - 22, "Rectangle" );
		mvprintw( 7, screenMiddleX - 22, "Triangle" );
		mvprintw( 8, screenMiddleX - 22, "Ellipse" );
		mvprintw( 9, screenMiddleX - 22, "Polygon" );
		mvprintw( 10, screenMiddleX - 10, "+------------------+");
		mvprintw( 11, screenMiddleX - 10, "| %-16s |", input);
		mvprintw( 12, screenMiddleX - 10, "+------------------+");
		//mvprintw( 14, 22, "%d", chunk );

		// update and collect chunk
		refresh();
		chunk = getch();
		erase();

		// what to do with the chunk
		switch( chunk ){
			case '\0': // do nothing
				break;
			case 'q': // quit
			case 'Q':
			case ESC:
				quit = 1;
				break;
			case BACKSPACE: // delete the last character
			case KEY_BACKSPACE:
				if( index > 0 ){
					--index;
					input[ index ] = '\0';
				} else {
					// do nothing
				}
				break;
			case '\n': // check the input
			case ENTER:
				if( stringCompareI( input, "circle" ) == 0 ){
					erase();
					circle( maxY, maxX );
				} else if( stringCompareI( input, "rectangle" ) == 0 ){
					erase();
					rectangle( maxY, maxX );
				} else if( stringCompareI( input, "triangle" ) == 0 ){
					erase();
					triangle( maxY, maxX );
				} else if( stringCompareI( input, "ellipse" ) == 0 ){
					erase();
					ellipse( maxY, maxX );
				} else if( stringCompareI( input, "polygon" ) == 0 ){
					erase();
					polygon( maxY, maxX );
				} else {
					mvprintw( maxY - 3, screenMiddleX - 10, "ERROR: Invalid option" );
				}
				index = 0;
				input[ index ] = '\0';
				break;
			default: // add character
				if( index < 16 ){
					input[ index ] = chunk;
					++index;
					input[ index ] = '\0';
				} else {
					// do nothing
				}
				break;
		}
	}
	endwin();
	return( EXIT_SUCCESS );
}

/*
 * Name: circle
 * Desc: The menu for the circle properties.
 * Args:
 *      int maxY - the max value for y
 *      int maxX - the max value for x
 */
int circle( int maxY, int maxX ){
	int exitCode;
	int quit;
	int screenMiddleX;
	int index;
	int printProp;
	char chunk;
	char input[ 50 ];
	double radius;

	exitCode = EXIT_SUCCESS;
	quit = 0;
	screenMiddleX = maxX / 2;
	index = 0;
	printProp = 0;
	chunk = '\0';
	input[ index ] = '\0';
	radius = 0.0;

	while( quit != 1 ){
		// display basic information
		border( '|', '|', '-', '-', '+', '+', '+', '+' );
		mvprintw( 5, screenMiddleX - 30, "Please enter the radius in inches: %s", input );
		if( printProp == 1 ){
			get_circle_properties( radius, maxY, maxX, maxY/2 - 4, screenMiddleX - 23 );
		} else {
			printHelp( maxY/2 - 4, screenMiddleX - 25 );
		}

		// update information and collect chunk
		refresh();
		chunk = getch();
		erase();

		// what to do with the chunk
		if(( chunk == '\n' || chunk == ENTER ) && index > 0 ){ // update the properties
			radius = atof( input );
			printProp = 1;
			index = 0;
			input[ index ] = '\0';
		} else if( chunk == BACKSPACE ){ // delete the last character
			if( index > 0 ){
				--index;
				input[ index ] = '\0';
			}
		} else if(( chunk >= '0' && chunk <= '9' ) || chunk == '.' ){ // add on a character
			if( index < 49 ){
				input[ index ] = chunk;
				++index;
				input[ index ] = '\0';
			} else {
				mvprintw( maxY - 3, maxX / 2 - 15, "ERROR: To many input characters" );
			}
		} else if( chunk == ESC || chunk == 'q' || chunk == 'Q' ){
			quit = 1;
		} else {
			// do nothing
		}
	}

	return( exitCode );
}

/*
 * Name: rectangle
 * Desc: The menu for the rectangle properties.
 * Args:
 *      int maxY - the max value for y
 *      int maxX - the max value for x
 */
int rectangle( int maxY, int maxX ){
	int exitCode;
	int quit;
	int screenMiddleX;
	int lengthIndex;
	int widthIndex;
	int printProp;
	int entering; // what the user is currently entering ( 0 is the first argument, 1 is the second, and so on )
	char chunk;
	char lengthInput[ 50 ];
	char widthInput[ 50 ];
	double length;
	double width;

	exitCode = EXIT_SUCCESS;
	quit = 0;
	screenMiddleX = maxX / 2;
	lengthIndex = 0;
	widthIndex = 0;
	printProp = 0;
	entering = 0;
	chunk = '\0';
	lengthInput[ lengthIndex ] = '\0';
	widthInput[ widthIndex ] = '\0';
	length = 0.0;
	width = 0.0;

	while( quit != 1 ){
		// display basic information
		border( '|', '|', '-', '-', '+', '+', '+', '+' );
		mvprintw( 5, screenMiddleX - 30, "Please enter the length in inches: %s", lengthInput );
		mvprintw( 6, screenMiddleX - 30, "Please enter the width in inches: %s", widthInput );
		if( printProp == 1 ){
			get_rectangle_properties( length, width, maxY, maxX, maxY/2 - 4, screenMiddleX - 23 );
		} else {
			printHelp( maxY/2 - 4, screenMiddleX - 25 );
		}

		// update information and collect chunk
		refresh();
		chunk = getch();
		erase();

		// what to do with the chunk
		if(( chunk == '\n' || chunk == ENTER ) && ( lengthIndex > 0 || widthIndex > 0 )){ // update the properties
			if( printProp == 0 && entering == 0 ){
				length = atof( lengthInput );
				lengthIndex = 0;
				lengthInput[ lengthIndex ] = '\0';
				entering = 1;
			} else {
				if( entering == 0 ){
					length = atof( lengthInput );
					lengthIndex = 0;
					lengthInput[ lengthIndex ] = '\0';
					entering = 1;
				} else {
					width = atof( widthInput );
					widthIndex = 0;
					widthInput[ widthIndex ] = '\0';
					entering = 0;
				}
				printProp = 1;
			}
		} else if( chunk == BACKSPACE ){ // delete the last character
			if( entering == 0 ){
				if( lengthIndex > 0 ){
					--lengthIndex;
					lengthInput[ lengthIndex ] = '\0';
				} else {
					// do nothing
				}
			} else {
				if( widthIndex > 0 ){
					--widthIndex;
					widthInput[ widthIndex ] = '\0';
				} else {
					// do nothing
				}
			}
		} else if(( chunk >= '0' && chunk <= '9' ) || chunk == '.' ){ // add on a character
			if( entering == 0 ){
				if( lengthIndex < 49 ){
					lengthInput[ lengthIndex ] = chunk;
					++lengthIndex;
					lengthInput[ lengthIndex ] = '\0';
				} else {
					mvprintw( maxY - 3, maxX / 2 - 15, "ERROR: To many input characters" );
				}
			} else {
				if( widthIndex < 49 ){
					widthInput[ widthIndex ] = chunk;
					++widthIndex;
					widthInput[ widthIndex ] = '\0';
				} else {
					mvprintw( maxY - 3, maxX / 2 - 15, "ERROR: To many input characters" );
				}
			}
		} else if( chunk == ESC || chunk == 'q' || chunk == 'Q' ){
			quit = 1;
		} else {
			// do nothing
		}
	}

	return( exitCode );
}

/*
 * Name: triangle
 * Desc: The menu for the triangle properties.
 * Args:
 *      int maxY - the max value for y
 *      int maxX - the max value for x
 */
int triangle( int maxY, int maxX ){
	int exitCode;
	int quit;
	int screenMiddleX;
	int aIndex;
	int bIndex;
	int gammaIndex;
	int printProp;
	int entering; // what the user is currently entering ( 0 is the first argument, 1 is the second, and so on )
	char chunk;
	char aInput[ 50 ];
	char bInput[ 50 ];
	char gammaInput[ 50 ];
	double a;
	double b;
	double gamma;

	exitCode = EXIT_SUCCESS;
	quit = 0;
	screenMiddleX = maxX / 2;
	aIndex = 0;
	bIndex = 0;
	gammaIndex = 0;
	printProp = 0;
	entering = 0;
	chunk = '\0';
	aInput[ aIndex ] = '\0';
	bInput[ bIndex ] = '\0';
	gammaInput[ gammaIndex ] = '\0';
	a = 0.0;
	b = 0.0;
	gamma = 0.0;

	while( quit != 1 ){
		// display basic information
		border( '|', '|', '-', '-', '+', '+', '+', '+' );
		mvprintw( 5, screenMiddleX - 35, "Please enter the length for side a in inches: %s", aInput );
		mvprintw( 6, screenMiddleX - 35, "Please enter the length for side b in inches: %s", bInput );
		mvprintw( 7, screenMiddleX - 35, "Please enter the angle for gamma in radians: %s", gammaInput );
		if( printProp == 1 ){
			get_triangle_properties( a, b, gamma, maxY, maxX, maxY/2 - 4, screenMiddleX - 23 );
		} else {
			printHelp( maxY/2 - 4, screenMiddleX - 25 );
		}

		// update information and collect chunk
		refresh();
		chunk = getch();
		erase();

		// what to do with the chunk
		if(( chunk == '\n' || chunk == ENTER ) && ( aIndex > 0 || bIndex > 0 || gammaIndex > 0 )){ // update the properties
			if( printProp == 0 && entering == 0 ){
				a = atof( aInput );
				aIndex = 0;
				aInput[ aIndex ] = '\0';
				entering = 1;
			} else if( printProp == 0 && entering == 1 ){
				b = atof( bInput );
				bIndex = 0;
				bInput[ bIndex ] = '\0';
				entering = 2;
			} else {
				if( entering == 0 ){
					a = atof( aInput );
					aIndex = 0;
					aInput[ aIndex ] = '\0';
					entering = 1;
				} else if( entering == 1 ){
					b = atof( bInput );
					bIndex = 0;
					bInput[ bIndex ] = '\0';
					entering = 2;
				} else {
					gamma = atof( gammaInput );
					gammaIndex = 0;
					gammaInput[ gammaIndex ] = '\0';
					entering = 0;
				}
				printProp = 1;
			}
		} else if( chunk == BACKSPACE ){ // delete the last character
			if( entering == 0 ){
				if( aIndex > 0 ){
					--aIndex;
					aInput[ aIndex ] = '\0';
				} else {
					// do nothing
				}
			} else if( entering == 1 ){
				if( bIndex > 0 ){
					--bIndex;
					bInput[ bIndex ] = '\0';
				} else {
					// do nothing
				}
			} else {
				if( gammaIndex > 0 ){
					--gammaIndex;
					gammaInput[ gammaIndex ] = '\0';
				} else {
					// do nothing
				}
			}
		} else if(( chunk >= '0' && chunk <= '9' ) || chunk == '.' ){ // add on a character
			if( entering == 0 ){
				if( aIndex < 49 ){
					aInput[ aIndex ] = chunk;
					++aIndex;
					aInput[ aIndex ] = '\0';
				} else {
					mvprintw( maxY - 3, maxX / 2 - 15, "ERROR: To many input characters" );
				}
			} else if( entering == 1 ){
				if( bIndex < 49 ){
					bInput[ bIndex ] = chunk;
					++bIndex;
					bInput[ bIndex ] = '\0';
				} else {
					mvprintw( maxY - 3, maxX / 2 - 15, "ERROR: To many input characters" );
				}
			} else {
				if( gammaIndex < 49 ){
					gammaInput[ gammaIndex ] = chunk;
					++gammaIndex;
					gammaInput[ gammaIndex ] = '\0';
				} else {
					mvprintw( maxY - 3, maxX / 2 - 15, "ERROR: To many input characters" );
				}
			}
		} else if( chunk == ESC || chunk == 'q' || chunk == 'Q' ){
			quit = 1;
		} else {
			// do nothing
		}
	}

	return( exitCode );
}

/*
 * Name: ellipse
 * Desc: The menu for the ellipse properties.
 * Args:
 *      int maxY - the max value for y
 *      int maxX - the max value for x
 */
int ellipse( int maxY, int maxX ){
	int exitCode;
	int quit;
	int screenMiddleX;
	int aIndex;
	int bIndex;
	int printProp;
	int entering; // what the user is currently entering ( 0 is the first argument, 1 is the second, and so on )
	char chunk;
	char aInput[ 50 ];
	char bInput[ 50 ];
	double a;
	double b;

	exitCode = EXIT_SUCCESS;
	quit = 0;
	screenMiddleX = maxX / 2;
	aIndex = 0;
	bIndex = 0;
	printProp = 0;
	entering = 0;
	chunk = '\0';
	aInput[ aIndex ] = '\0';
	bInput[ bIndex ] = '\0';
	a = 0.0;
	b = 0.0;

	while( quit != 1 ){
		// display basic information
		border( '|', '|', '-', '-', '+', '+', '+', '+' );
		mvprintw( 5, screenMiddleX - 30, "Please enter the minor axis (a) in inches: %s", aInput );
		mvprintw( 6, screenMiddleX - 30, "Please enter the major axis (b) in inches: %s", bInput );
		if( printProp == 1 ){
			get_ellipse_properties( a, b, maxY, maxX, maxY/2 - 4, screenMiddleX - 23 );
		} else {
			printHelp( maxY/2 - 4, screenMiddleX - 25 );
		}

		// update information and collect chunk
		refresh();
		chunk = getch();
		erase();

		// what to do with the chunk
		if(( chunk == '\n' || chunk == ENTER ) && ( aIndex > 0 || bIndex > 0 )){ // update the properties
			if( printProp == 0 && entering == 0 ){
				a = atof( aInput );
				aIndex = 0;
				aInput[ aIndex ] = '\0';
				entering = 1;
			} else {
				if( entering == 0 ){
					a = atof( aInput );
					aIndex = 0;
					aInput[ aIndex ] = '\0';
					entering = 1;
				} else {
					b = atof( bInput );
					bIndex = 0;
					bInput[ bIndex ] = '\0';
					entering = 0;
				}
				printProp = 1;
			}
		} else if( chunk == BACKSPACE ){ // delete the last character
			if( entering == 0 ){
				if( aIndex > 0 ){
					--aIndex;
					aInput[ aIndex ] = '\0';
				} else {
					// do nothing
				}
			} else {
				if( bIndex > 0 ){
					--bIndex;
					bInput[ bIndex ] = '\0';
				} else {
					// do nothing
				}
			}
		} else if(( chunk >= '0' && chunk <= '9' ) || chunk == '.' ){ // add on a character
			if( entering == 0 ){
				if( aIndex < 49 ){
					aInput[ aIndex ] = chunk;
					++aIndex;
					aInput[ aIndex ] = '\0';
				} else {
					mvprintw( maxY - 3, maxX / 2 - 15, "ERROR: To many input characters" );
				}
			} else {
				if( bIndex < 49 ){
					bInput[ bIndex ] = chunk;
					++bIndex;
					bInput[ bIndex ] = '\0';
				} else {
					mvprintw( maxY - 3, maxX / 2 - 15, "ERROR: To many input characters" );
				}
			}
		} else if( chunk == ESC || chunk == 'q' || chunk == 'Q' ){
			quit = 1;
		} else {
			// do nothing
		}
	}

	return( exitCode );
}

/*
 * Name: polygon
 * Desc: The menu for the polygon properties.
 * Args:
 *      int maxY - the max value for y
 *      int maxX - the max value for x
 */
int polygon( int maxY, int maxX ){
	int exitCode;
	int quit;
	int screenMiddleX;
	int nIndex;
	int sIndex;
	int printProp;
	int entering; // what the user is currently entering ( 0 is the first argument, 1 is the second, and so on )
	char chunk;
	char nInput[ 50 ];
	char sInput[ 50 ];
	double n;
	double s;

	exitCode = EXIT_SUCCESS;
	quit = 0;
	screenMiddleX = maxX / 2;
	nIndex = 0;
	sIndex = 0;
	printProp = 0;
	entering = 0;
	chunk = '\0';
	nInput[ nIndex ] = '\0';
	sInput[ sIndex ] = '\0';
	n = 0.0;
	s = 0.0;

	while( quit != 1 ){
		// display basic information
		border( '|', '|', '-', '-', '+', '+', '+', '+' );
		mvprintw( 5, screenMiddleX - 30, "Please enter the number of sides (n): %s", nInput );
		mvprintw( 6, screenMiddleX - 30, "Please enter the side length (s) in inches: %s", sInput );
		if( printProp == 1 ){
			get_regular_polygon_properties( n, s, maxY, maxX, maxY/2 - 4, screenMiddleX - 23 );
		} else {
			printHelp( maxY/2 - 4, screenMiddleX - 25 );
		}

		// update information and collect chunk
		refresh();
		chunk = getch();
		erase();

		// what to do with the chunk
		if(( chunk == '\n' || chunk == ENTER ) && ( nIndex > 0 || sIndex > 0 )){ // update the properties
			if( printProp == 0 && entering == 0 ){
				n = atof( nInput );
				nIndex = 0;
				nInput[ nIndex ] = '\0';
				entering = 1;
			} else {
				if( entering == 0 ){
					n = atof( nInput );
					nIndex = 0;
					nInput[ nIndex ] = '\0';
					entering = 1;
				} else {
					s = atof( sInput );
					sIndex = 0;
					sInput[ sIndex ] = '\0';
					entering = 0;
				}
				printProp = 1;
			}
		} else if( chunk == BACKSPACE ){ // delete the last character
			if( entering == 0 ){
				if( nIndex > 0 ){
					--nIndex;
					nInput[ nIndex ] = '\0';
				} else {
					// do nothing
				}
			} else {
				if( sIndex > 0 ){
					--sIndex;
					sInput[ sIndex ] = '\0';
				} else {
					// do nothing
				}
			}
		} else if(( chunk >= '0' && chunk <= '9' ) || chunk == '.' ){ // add on a character
			if( entering == 0 ){
				if( nIndex < 49 ){
					nInput[ nIndex ] = chunk;
					++nIndex;
					nInput[ nIndex ] = '\0';
				} else {
					mvprintw( maxY - 3, maxX / 2 - 15, "ERROR: To many input characters" );
				}
			} else {
				if( sIndex < 49 ){
					sInput[ sIndex ] = chunk;
					++sIndex;
					sInput[ sIndex ] = '\0';
				} else {
					mvprintw( maxY - 3, maxX / 2 - 15, "ERROR: To many input characters" );
				}
			}
		} else if( chunk == ESC || chunk == 'q' || chunk == 'Q' ){
			quit = 1;
		} else {
			// do nothing
		}
	}

	return( exitCode );
}

/*
 * Name: stringCompareI
 * Desc: strcmp while ignoring case.
 * Args:
 *      const char *firstString - the first string
 *      const char *secondString - the second string
 */
int stringCompareI( const char *firstString, const char *secondString ){
	int returnValue;
	int index;
	char firstChunk;
	char secondChunk;

	returnValue = 0;
	for( index = 0; ( returnValue == 0 ) && ( firstString[ index ] != '\0' ) && ( secondString[ index ] != '\0' ); ++index ){
		firstChunk = firstString[ index ];
		secondChunk = secondString[ index ];

		if( firstChunk >= 'A' && firstChunk <= 'Z' ){
			firstChunk += 32;
		}
		if( secondChunk >= 'A' && secondChunk <= 'Z' ){
			secondChunk += 32;
		}
		if( firstChunk > secondChunk ){
			returnValue = 1;
		} else if( firstChunk < secondChunk ){
			returnValue = -1;
		} else {
			returnValue = 0;
		}
	}
	if( returnValue == 0 ){
		if( firstString[ index ] == '\0' && secondString[ index ] == '\0' ){
			returnValue = 0;
		} else if( firstString[ index ] == '\0' ){
			returnValue = -1;
		} else {
			returnValue = 1;
		}
	}
	return( returnValue );
}

// from p3
/*
 * Name: double approximate_PI(void)
 * Desc: Calculate PI using the Gregory–Leibniz series
 */
double approximate_pi(void)
{
	int count;
	int sign;
	double sum;

	sign = 1;
	sum = 0.0;

	for (count = 1; count <= 19999; count += 2)
	{
		sum = sum +  sign * (1 / ((double) count)); 
		/* Display the iteration number, the addendum and the running total.
		 * printf("%d %f %f\n", count, (sign * (1 / ((double) count))), (4*sum) );
		 */
		// 
		sign = -sign;        
	}
	sum = 4 * sum;
	return( sum );
}

/*
 * Name: int get_circle_properties( double radius )
 * Desc: Calculates the circle properties with a given radius
 * Args: 
 *      double radius - the circles radius
 */
int get_circle_properties( double radius, int maxY, int maxX, int startY, int startX ){
	double perimeter;
	double area;
	int returnValue;

	if( radius < 0 ){
		mvprintw( maxY - 3, maxX / 2 - 12, "ERROR: radius is negative\n" );
		returnValue = -1;
	} else {
		perimeter = 2 * radius * PI;
		area = radius * radius * PI;

		mvprintw( startY + 0, startX, "==============================================" );
		mvprintw( startY + 1, startX, "radius: %33.2f   in", radius );
		mvprintw( startY + 2, startX, "perimeter: %30.2f   in", perimeter );
		mvprintw( startY + 3, startX, "area: %35.2f in^2", area );
		mvprintw( startY + 4, startX, "==============================================" );
		returnValue = 0;
	}
	return( returnValue );
}

/*
 * Name: int get_rectangle_properties( double length, double width )
 * Desc: Calculates the rectangle properties with a given length and width
 * Args:
 *      double length - the length of the rectangle
 *      double width  - the width of the rectangle
 */
int get_rectangle_properties( double length, double width, int maxY, int maxX, int startY, int startX ){
	double perimeter;
	double area;
	double diagonal;
	double aspect_ratio;
	double inscribed_circle_area;
	double circumscribed_circle_area;
	int returnValue;

	if( length <= 0 || width <= 0 ){
		mvprintw( maxY - 3, maxX/2 - 15, "ERROR: sides must be positive.\n" );
		returnValue = -1;
	} else {
		perimeter = 2 * length + 2 * width;
		area = length * width;
		diagonal = sqrt( length * length + width * width );
		aspect_ratio = length / width;
		inscribed_circle_area = ( length < width ) ? ( length * PI ) : ( width * PI );
		circumscribed_circle_area = diagonal * PI;

		mvprintw( startY + 0, startX, "==============================================" );
		mvprintw( startY + 1, startX, "length: %33.2f   in", length );
		mvprintw( startY + 2, startX, "width: %34.2f   in", width );
		mvprintw( startY + 3, startX, "perimeter: %30.2f   in", perimeter );
		mvprintw( startY + 4, startX, "area: %35.2f in^2", area );
		mvprintw( startY + 5, startX, "diagonal: %31.2f   in", diagonal );
		mvprintw( startY + 6, startX, "aspect_ratio: %27.2f     ", aspect_ratio );
		mvprintw( startY + 7, startX, "inscribed_circle_area: %18.2f in^2", inscribed_circle_area );
		mvprintw( startY + 8, startX, "circumscribed_circle_area: %14.2f in^2", circumscribed_circle_area );
		mvprintw( startY + 9, startX, "==============================================\n" );
		returnValue = 0;
	}
	return( returnValue );
}

/*
 * Name: int get_triangle_properties( double a, double b, double gamma )
 * Desc: Calculates the triangle properties with a given a, b, and gamma
 * Args:
 *      double a     - side a of the triangle
 *      double b     - side b of the triangle
 *      double gamma - the angle between side a and b
 */
int get_triangle_properties( double a, double b, double gamma, int maxY, int maxX, int startY, int startX ){
	double c;
	double alpha;
	double beta;
	double base;
	double height;
	double area;
	double perimeter;
	double inscirbed_circle_radius;
	double inscribed_circle_area;
	double circumscribed_circle_radius;
	double circumscribed_circle_area;
	int returnValue;
	char msg[ 12 ];

	if( a <= 0 || b <= 0 ){
		if( a <= 0 && b <= 0 ){
			strcpy( msg, "a and b are" );
		} else if( a <= 0 ){
			strcpy( msg, "a is" );
		} else {
			strcpy( msg, "b is" );
		}
		mvprintw( maxY - 3, maxX / 2 - ( strlen( msg ) / 2 ) - 17, "ERROR: %s less than or equal to zero", msg );
		returnValue = -1;
	} else if( gamma == 0 ){
		mvprintw( maxY - 3, maxX / 2 - 10, "ERROR: gamma is zero" );
		returnValue = -1;
	} else {
		c = sqrt( a * a + b * b + 2 * a * b * cos( gamma ));
		alpha = asin(( sin( gamma ) * a ) / c );
		beta = asin(( sin( gamma ) * b ) / c );
		base = b;
		height =  a * sin( gamma );
		area = 0.5 * base * height;
		perimeter = a + b + c;
		inscirbed_circle_radius = ( 2 * area )/ perimeter;
		inscribed_circle_area = inscirbed_circle_radius * inscirbed_circle_radius * PI;
		circumscribed_circle_radius = ( a * b * c ) / ( sqrt( ( a + b + c ) * ( b + c - a ) * ( c + a - b ) * ( a + b - c )));
		circumscribed_circle_area = circumscribed_circle_radius * circumscribed_circle_radius * PI;

		mvprintw( startY + 0 , startX, "==============================================" );
		mvprintw( startY + 1 , startX, "a: %35.2f      in", a );
		mvprintw( startY + 2 , startX, "b: %35.2f      in", b );
		mvprintw( startY + 3 , startX, "gamma: %31.2f radians", gamma );
		mvprintw( startY + 4 , startX, "c: %35.2f      in", c );
		mvprintw( startY + 5 , startX, "alpha: %31.2f radians", alpha );
		mvprintw( startY + 6 , startX, "beta: %32.2f radians", beta );
		mvprintw( startY + 7 , startX, "perimeter: %27.2f      in", perimeter );
		mvprintw( startY + 8 , startX, "area: %32.2f    in^2", area );
		mvprintw( startY + 9 , startX, "inscribed_circle_area: %15.2f    in^2", inscribed_circle_area );
		mvprintw( startY + 10, startX, "circumscribed_circle_area: %11.2f    in^2", circumscribed_circle_area );
		mvprintw( startY + 11, startX, "==============================================" );
		returnValue = 0;
	}
	return( returnValue );
}

/*
 * Name: int get_ellipse_properties( double a, double b )
 * Desc: Calculates the oval properties with a given a (minor axis) and b (major axis)
 * Args:
 *      double a - the minor axis
 *      double b - the major axis
 */
int get_ellipse_properties( double a, double b, int maxY, int maxX, int startY, int startX ){
	double c;
	double e;
	double h;
	double area;
	double perimeter;
	int returnValue;

	if( a < b ){
		mvprintw( maxY - 3, maxX / 2 - 28, "ERROR: minor axis a should be larger than or equal to b." );
		returnValue = -1;
	} else {
		c = sqrt( a * a - b * b );
		e = c / a;
		area = a * b * PI;
		h = (( a - b ) * ( a - b )) / (( a + b ) * ( a + b ));
		perimeter = ( a + b ) * ( 1 + ( 3 * h ) / ( 10 + sqrt( 4 - 3 * h ))) * PI;
		mvprintw( startY + 0, startX, "==============================================" );
		mvprintw( startY + 1, startX, "a: %38.2f   in", a );
		mvprintw( startY + 2, startX, "b: %38.2f   in", b );
		mvprintw( startY + 3, startX, "c: %38.2f   in", c );
		mvprintw( startY + 4, startX, "e: %38.2f   in", e );
		mvprintw( startY + 5, startX, "area: %35.2f in^2", area );
		mvprintw( startY + 6, startX, "perimeter: %30.2f   in", perimeter );
		mvprintw( startY + 7, startX, "==============================================" );
		returnValue = 0;
	}
	return( returnValue );
}

/*
 * Name: int get_regular_polygon_properties( int n, double s )
 * Desc: Calculates the regular polygon properties with a given n (number of sides) and s (side length)
 * Args:
 *      int n    - the number of sides
 *      double s - the length of a side
 */
int get_regular_polygon_properties( int n, double s, int maxY, int maxX, int startY, int startX ){
	double a;
	double R;
	double theta;
	double perimeter;
	double area;
	int returnValue;

	if( n < 3 ){
		mvprintw( maxY - 3, maxX / 2 - 21, "ERROR: number of sides must be at least 3." );
		returnValue = -1;
	} else if( s <= 0 ){
		mvprintw( maxY - 3, maxX / 2 - 19, "ERROR: side length should be positive." );
		returnValue = -1;
	} else {
		a = s / ( 2 * tan( PI / n ));
		R = s / ( 2 * sin( PI / n ));
		theta = ( ( n - 2 ) * PI ) / n;
		perimeter = n * s;
		area = 0.5 * n * s * a;

		mvprintw( startY + 0, startX, "==============================================" );
		mvprintw( startY + 1, startX, "n: %35d       ", n );
		mvprintw( startY + 2, startX, "s: %35.2f      in", s );
		mvprintw( startY + 3, startX, "a: %35.2f      in", a );
		mvprintw( startY + 4, startX, "R: %35.2f      in", R );
		mvprintw( startY + 5, startX, "theta: %31.2f radians", theta );
		mvprintw( startY + 6, startX, "perimeter: %27.2f      in", perimeter );
		mvprintw( startY + 7, startX, "area: %32.2f    in^2", area );
		mvprintw( startY + 8, startX, "==============================================" );
		returnValue = 0;
	}
	return( returnValue );
}

/*
 * Name: printHelp
 * Desc: Prints the instructions.
 * Args:
 *      int startY - the starting y value
 *      int startX - the starting x value
 */
int printHelp( int startY, int startX ){
	mvprintw( startY + 0, startX, "+--------------------------------------------+" );
	mvprintw( startY + 1, startX, "|                   help                     |" );
	mvprintw( startY + 2, startX, "+--------------------------------------------+" );
	mvprintw( startY + 3, startX, "| Press 'Q' to quit.                         |" );
	mvprintw( startY + 4, startX, "| Press enter to calculate properties.       |" );
	mvprintw( startY + 5, startX, "+--------------------------------------------+" );
	return( EXIT_SUCCESS );
}
