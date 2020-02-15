#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char word[50];
	printf("Please enter a word to be sorted: ");
	scanf("%s",&word);

	for(int run = 0; run < strlen(word)-1; run++)
	{
		for(int size = run+1; size < strlen(word); size++)
		{
			if(word[run] > word[size])
			{
				char dummy[2];
				dummy[1] = word[run];
				word[run] = word[size];
				word[size] = dummy[1];
			}
		}
	}
	printf("%s\n",word);
}
