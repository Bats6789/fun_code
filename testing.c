#include <stdio.h>

int main ( void ){

	int i = 4;
	int j = i++;
	int k = ++j;
	printf("i = %d, j = %d, k = %d\n",i,j,k);
	return(0);
}
