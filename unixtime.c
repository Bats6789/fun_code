#include <stdio.h>
#include <time.h>

int main()
{
	time_t now = time(NULL);

	if(now == -1)
	{
		puts("The time() function failed");
	}

	printf("%ld\n",now);

	return 0;
}
