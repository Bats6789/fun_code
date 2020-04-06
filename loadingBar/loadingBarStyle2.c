/*
 * Name: loadingBar.c
 * Auth: Blake Wingard
 * Desc: Demonstrates a loading screen using printf's
 * Vers: 1.0.0 04/06/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *loadingBar( void *args );

typedef struct {
	int *run;
	int dots;
} threadInputsType;

int main( int argc, char **argv ){
	int wait;
	int run;
	pthread_t thread;
	threadInputsType threadInput;

	if( argc < 2 ){
		wait = 3;
		threadInput.dots = 20;
	} else if( argc < 3 ){
		wait = atoi( argv[ 1 ] );
		threadInput.dots = 20;
	} else {
		wait = atoi( argv[ 1 ] );
		threadInput.dots = atoi( argv[ 2 ] );
	}


	if( wait <= 0 ){
		wait = 1;
	}
	if( threadInput.dots < 5 ){
		threadInput.dots = 5;
	}

	run = 1;
	threadInput.run = &run;
	pthread_create( &thread, NULL, loadingBar, &threadInput );

	sleep( wait );
	run = 0;
	pthread_join( thread, NULL );

	return( EXIT_SUCCESS );
}

void *loadingBar( void *args ){
	int count;
	struct timespec time;
	threadInputsType threadInput;
	
	count = 0;
	time.tv_sec = 0;
	time.tv_nsec = 300000000L; // 300 million or 0.3 seconds
	threadInput = *(threadInputsType *)args;
	printf( "Loading:[" );
	for( int i = 0; i < threadInput.dots; ++i ){
		printf( "_" );
	}
	printf( "]" );
	for( int i = 0; i < threadInput.dots + 1; ++i ){
		printf( "\b" );
	}
	while( *threadInput.run ){
		if( count >= threadInput.dots ){
			count -= 5;
			for( int i = 0; i < 5; ++i ){
				printf( "\b" );
			}
			for( int i = 0; i < 5; ++i ){
				printf( "_" );
			}
			for( int i = 0; i < 5; ++i ){
				printf( "\b" );
			}
		}
		printf( "*" );
		++count;
		nanosleep( &time, NULL );
	}
	for( ; count < threadInput.dots; ++count ){
		printf( "*" );
	}
	printf( "\n" );
}
