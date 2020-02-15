#include <stdio.h>
#include <time.h>

void main()
{
	
	int month, day, year;		// variables for users birthday
	struct time {			// Structure for storing user's age values
		float sec;	// seconds
		float min;	// minutes
		float hour;	// hours
		float year;	// years
	};

	// Obtain users birthday
	printf("Please enter your birthday in the format (mm/dd/yyyy): ");
	scanf("%d/%d/%d", &month, &day, &year);

	// Determine current date
	time_t crttime = time(NULL);
	struct tm *crtdate = localtime(&crttime);

	// Determine user's age value
	struct tm birthday = {0, 0, 0, day, month-1, year-1900};
	time_t usertime = mktime(&birthday);

	// Calulate user's age in different units
	struct time age;
	age.sec = crttime - usertime;
	age.min = age.sec/60;
	age.hour = age.min / 60;
	age.year = age.hour / (365.25 * 24);

	// Return information to the user
	printf("On %02d/%02d/%02d, anyone born during %02d/%02d/%02d, is\n%0.3g seconds old\n%0.3g minutes old\n%0.3g hours old\n%0.3g years old\n",
		crtdate->tm_mon+1, crtdate->tm_mday, crtdate->tm_year+1900, // current date
		month, day, year, // user's birthday
		age.sec, age.min, age.hour, age.year /* user's age */ );
}
	
