#include <stdio.h>
#include <time.h>

int main()
{
	struct tm xmas = { 0, 0, 0, 24, 11, 119};

	time_t rawtime = mktime(&xmas);

	if(rawtime == -1)
	{
		puts("The mktime() function failed");
		return 1;
	}

	printf("The Unix time for Xmas is: %ld\n", rawtime);
	printf("The date of Xmas is: %02d/%02d/%04d\n",
			xmas.tm_mon+1, xmas.tm_mday, xmas.tm_year+1900);
	return 0;

}
