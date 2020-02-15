#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *cnvt = argv[1];					// Assigns the conversion specified by the user

	float a = atoi(argv[2]), b = atoi(argv[3]);		// Assigns the two values entered by the user

	if(strcmp(cnvt,"r2p")==0)				// Runs if the user is converting rectangular cord to polar cord
	{
		float x = a, y = b;				// "a" becomes "x" and "b" becomes "y"

		float ans1 = sqrtf(powf(x, 2) + powf(y, 2));	// The radius "r" is determined

		float ans2 = atanf(y / x) * (180 / 3.141592);	// The angle "theta" is determined in degrees
		
		// used to include the entire graph
		if(x < 0) // used if the cordinates are in quad II or III 
		{
			ans2 += 180;
		}
		else if(y < 0) // used if cordinates are in quad IV
		{
			ans2 += 360;
		}

		printf("r = %g\ntheta = %g\n",ans1,ans2);

	}

	else if(strcmp(cnvt,"p2r")==0)				// Runs if the user is converting polar cord to rectangular cord
	{
		float r = a, theta = b;				// "a" becomes the radius "r" and "b" becomes the angle "theta" in 
		theta *= (3.141592/180);			//  degrees

		float ans1 = r*cos(theta);			// "x" is determined

		float ans2 = r*sin(theta);			// "y" is determined

		printf("x = %0.5g\ny = %0.5g\n",ans1,ans2);

	}
	else
	{
		printf("failed\n");				// used if the user selected in invalid conversion
	}

	return 0;
}
