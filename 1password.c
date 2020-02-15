#include <stdio.h>
#include <string.h>

int main()
{
	char userpas[50];
	printf("Enter your password: ");
	scanf("%s", userpas);

	if(strlen(userpas)>49)
	{
		printf("Password is too long\n");
		return 1;
	}

	if(strcmp(userpas, "12345") == 0)
		printf("Password accepted.\n");
	else
		printf("Password denied.");
	return 0;
}
