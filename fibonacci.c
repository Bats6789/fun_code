// ===========================================================
// file name: fibonacci.c
// desc: determines the number in the term the user selects of the fibonacci sequance
// Vers: 1.0.0 03/28/2019 CBW - Original code
// ===========================================================

#include <stdio.h>
#include <stdlib.h>

// function prototypes
long unsigned int fibonacci(int term);

// start of code

// name: int main(int argc, char **argv)
// desc: the function the executes when the program starts
// arguments:
// 	argc - number of arguments passed to the executable
// 	argv - the arguments passed to the executable
int main(int argc, char **argv)
{
	// declare variables
	int term;	// user's input
	unsigned long int value;	// value of the term the user selected

	// check for no input from command window.
	if( argc == 1)
	{
	// 	if no input (argc == 1) is detected, prompt the user for a value.

		printf("Please enter the term you would like: ");
		scanf("%d", &term);
	} // else
	else
	{
	//	collect input from the command window
		term = atoi(argv[1]);
	//	printf("term = %d\n", term);
	}

	// check if input is negative or zero
	if(term <= 0)
	{
	// 	if true, output an error message
		printf("Error: Value must be a positive integer.\n");
	//	return failure
		return(EXIT_FAILURE);
	}

	// pass input to function
	value = fibonacci( term );

	// print the value to the user
	printf("The fibonacci number at term %d = %lu.\n", term, value);

	// return success
	return(EXIT_SUCCESS);
}

// name: fibonacci
// desc: determines the number in the term the user selects of the fibonacci sequance 
unsigned long int fibonacci(int term)
{
	// declare varaibles
	int current_term;

	// error checking
	//	 check if term is negative or zero
	if( term <= 0 )
	{
	// 	if true, print error message (value must be positive integer)
		printf("ERROR: value must be a positive integer.\n");

	// 	return -1 for failure
		return(-1);
	}

	// end of error checking

	// start of function's code
	//	 check if term is 1
	if( term == 1)
	{
	// 	if true, return 0
		return(0);
	} // else check if term 2
	else if( term == 2)
	{
	// 	if true, return 1
		return(1);
	} // else
	else
	{
	// 	evaluate sequance
	//	create a vector of "values" with size term
		unsigned long int values[term];

	//	initialize first two terms as 0 and 1
		values[0] = 0;
		values[1] = 1;

	//	to evaluate sequance, loop from 2 to "term"
		for( current_term = 2; current_term < term; current_term++)
		{
	//		while evaluating term["current"] = term["previous" (current - 1)] + term["before previous" (current - 2)];
			values[current_term] = values[current_term - 1] + values[current_term - 2];
		}
	//	once loop ends, return term["current"]
	//	printf("values[%d] = %d.\n", current_term, values[current_term - 1]);
		return(values[current_term - 1]);
	}

	// end of function's code

}
