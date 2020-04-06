/*
 * Name: xThreadToN.c
 * Auth: Blake Wingard
 * Desc: Uses x number of threads to add all the numbers from 1 to N.
 * Vers: 1.0.0 04/06/2020 CBW - Original code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

typedef struct {
	long long int startNum;
	long long int endNum;
	long long int *answer;
} inputArgsType;

void *addToN( void *args );

pthread_mutex_t mutex;

int main( int argc, char **argv ){
	long long int number;
	long long int answer;
	int updateFlag;
	int threadNum;

	if( argc < 3 ){
		fprintf( stderr, "ERROR: Not enough arguments.\n" );
	} else {
		threadNum = atoi( argv[ 1 ] );
		number = atoll( argv[ 2 ] );

		if( threadNum <= 0 ){
			fprintf( stderr, "ERROR: Must have at least one thread.\n" );
		} else if( number <= 0 ){
			fprintf( stderr, "ERROR: Number must be at least one.\n" );
		} else {
			updateFlag = 0;
			answer = 0;
			while( number / threadNum <= 0 ){
				threadNum /= 2;
				updateFlag = 1;
			}
			if( updateFlag ){
				printf( "To many threads for %lld, updating to %d threads.\n", number, threadNum );
			}
			if( pthread_mutex_init( &mutex, NULL ) != 0 ){
				perror( "ERROR" );
				return( EXIT_FAILURE );
			}
			pthread_t threads[ threadNum ];
			inputArgsType inputs[ threadNum ];
			for( int i = 0; i < threadNum; ++i ){
				inputs[ i ].startNum = i * number / threadNum + 1;
				inputs[ i ].endNum = ( i + 1 ) * number / threadNum;
				inputs[ i ].answer = &answer;
				if( pthread_create( &(threads[ i ]), NULL, addToN, &(inputs[ i ] )) != 0 ){
					perror( "ERROR" );
					return( EXIT_FAILURE );
				}
			}
			for( int i = 0; i < threadNum; ++i ){
				pthread_join( threads[ i ], NULL );
			}
			pthread_mutex_destroy( &mutex );
			printf( "The sum of all values from 1 to %lld = %lld\n", number, answer );
		}
	}

	return( EXIT_SUCCESS );
}

void *addToN( void *args ){
	inputArgsType input;
	long long int startNum;
	long long int endNum;
	long long int answer;

	input = *(inputArgsType *)args;
	startNum = input.startNum;
	endNum = input.endNum;

	answer = 0;
	for( long long int i = startNum; i <= endNum; ++i ){
		answer += i;
	}

	// mutex
	pthread_mutex_lock( &mutex );
	*(input.answer) += answer;
	pthread_mutex_unlock( &mutex );
}
