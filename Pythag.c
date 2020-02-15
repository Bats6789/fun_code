#include <stdio.h>
#include <math.h>
#include <string.h>

float solve(float * x, float * y, char * prop)
{
	float a = *x;
	float b = *y;
	if(strcmp(prop,"+")==0)
	{
		float c = sqrt(a*a+b*b);
		return c;
	}
	else if(strcmp(prop,"-")==0)
	{
		float c = sqrt(b*b-a*a);
		return c;
	}
	else
	{
		return 0;
	}
}


int main()
{
	float a, b, c;		// The length of the sides.
	char side[2];		// The side selected

	// User determines side selected
	printf("Please enter the side you're trying to solve for using the relation a^2 + b^2 = c^2 : ");
	scanf("%s",&side);

	// User gives side information
	printf("Please enter the length of the shorter side: ");
	scanf("%f",&a);
	printf("Please enter the length of the longer side: ");
	scanf("%f",&b);

	// Determine the length of the remaining side
	if(strcmp(side,"c")==0)
	{
		c = solve(&a,&b,"+");
	}
	else
	{
		c = solve(&a,&b,"-");
	}

	// return the value to the user
	printf("Side %s = %g\n",side,c);
	return 0;

}
