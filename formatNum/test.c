#include <malloc.h>
#include <string.h>
#include <stdio.h>

char *reverseString( char *str, int size ){
	char tmpChar;

	for( int index = 0; index < size / 2 + 1; ++index ){
		tmpChar = str[ index ];
		str[ index ] = str[ size - index ];
		str[ size - index ] = tmpChar;
	}

	return( str );
}

char *strsum(const char *a, const char *b){
  int sizeA;
  int sizeB;
  int sizeAnswer;
  int aIndex;
  int bIndex;
  int answerIndex;
  int tmpNum;
  int carry;
  char *answer;
  char *newA;
  char *newB;
  
  aIndex = 0;
  bIndex = 0;
  answerIndex = 0;
  sizeA = strlen( a );
  sizeB = strlen( b );
  newA = malloc( sizeof( char ) * sizeA + 1 );
  newB = malloc( sizeof( char ) * sizeB + 1 );
  sizeAnswer = (sizeA > sizeB) ? sizeA : sizeB;
  answer = malloc( sizeof( char ) * sizeAnswer + 2 );
  strcpy( newA, a );
  strcpy( newB, b );
  newA = reverseString( newA, sizeA  - 1 );
  newB = reverseString( newB, sizeB  - 1 );
  printf( "%s\n", newB );
  
  carry = 0;
  while( newA[ aIndex ] != '\0' && newB[ bIndex ] != '\0' ){
    tmpNum = newA[ aIndex ] + newB[ bIndex ] - 2 * '0' + carry;
    printf("%d = %d + %d - 2 * %d + %d\n", tmpNum, newA[ aIndex ], newB[ bIndex ], '0', carry );
    if( tmpNum >= 10 ){
      carry = 1;
      tmpNum -= 10;
    } else {
      carry = 0;
    }
    answer[ answerIndex ] = '0' + tmpNum;
    ++aIndex;
    ++bIndex;
    ++answerIndex;
  }
  
  if( newA[ aIndex ] != '\0' ){
    while( newA[ aIndex ] != '\0' ){
      tmpNum = newA[ aIndex ] + carry - '0';
      if( tmpNum >= 10 ){
        tmpNum -= 10;
        carry = 1;
      } else {
        carry = 0;
      }
      answer[ answerIndex ] = tmpNum + '0';
      ++aIndex;
      ++answerIndex;
    }
    answer[ answerIndex ] = '\0';
  } else if( newB[ bIndex ] != '\0' ){
    while( newB[ aIndex ] != '\0' ){
      tmpNum = newB[ bIndex ] + carry - '0';
      if( tmpNum >= 10 ){
        tmpNum -= 10;
        carry = 1;
      } else {
        carry = 0;
      }
      answer[ answerIndex ] = tmpNum + '0';
      ++bIndex;
      ++answerIndex;
    }
    answer[ answerIndex ] = '\0';
  } else {
    answer[ answerIndex ] = '\0';
  }
  
  answer = reverseString( answer, answerIndex - 1 );
  return( answer );
}

int main( int argc, char **argv ){
	printf( "%s\n", strsum( argv[ 1 ], argv[ 2 ] ));
	return( 0 );
}
