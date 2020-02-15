#include <stdio.h>

int main( void ){
	int integer;
	int *pInteger;
	int **ppInteger;
	char character;
	char *pCharacter;
	char **ppCharacter;
	float Float;
	float *pFloat;
	float **ppFloat;
	double Double;
	double *pDouble;
	double **ppDouble;

	integer = 1;
	character = 'a';
	Float = 1;
	Double = 1;
	
	pInteger = &integer;
	pCharacter = &character;
	pFloat = &Float;
	pDouble = &Double;

	ppInteger = &pInteger;
	ppCharacter = &pCharacter;
	ppFloat = &pFloat;
	ppDouble = &pDouble;

	printf("The size of an integer is %d\n", sizeof( integer ));
	printf("The size of a character is %d\n", sizeof( character ));
	printf("The size of a float is %d\n", sizeof( Float ));
	printf("The size of a double is %d\n", sizeof( Double ));

	printf("The size of a pointer to an integer is %d\n", sizeof( pInteger ));
	printf("The size of a pointer to a character is %d\n", sizeof( pCharacter ));
	printf("The size of a pointer to a float is %d\n", sizeof( pFloat ));
	printf("The size of a pointer to a double is %d\n", sizeof( pDouble ));

	printf("The size of a pointer to an pointer to a integer is %d\n", sizeof( ppInteger ));
	printf("The size of a pointer to a pointer to a character is %d\n", sizeof( ppCharacter ));
	printf("The size of a pointer to a pointer to a float is %d\n", sizeof( ppFloat ));
	printf("The size of a pointer to a pointer to a double is %d\n", sizeof( ppDouble ));

	printf("The value of a variable with type int is %d\n", integer );
	printf("The address of said variable is %p\n", &integer );
	printf("The value of a variable with type *int is %p\n", pInteger );
	printf("The address of said variable is %p\n", &pInteger );
	printf("When the said variable is dereferenced %d\n", *pInteger );
	printf("The value of a variable with type **int is %p\n", ppInteger );
	printf("The address of said variable is %p\n", &ppInteger );
	printf("When the said variable is dereferenced %p\n", *ppInteger );
	printf("When dereferenced a second time %d\n", **ppInteger );

	printf("The value of a variable with type char is %c\n", character );
	printf("The address of said variable is %p\n", &character );
	printf("The value of a variable with type *char is %p\n", pCharacter );
	printf("The address of said variable is %p\n", &pCharacter );
	printf("When the said variable is dereferenced %c\n", *pCharacter );
	printf("The value of a variable with type **char is %p\n", ppCharacter );
	printf("The address of said variable is %p\n", &ppCharacter );
	printf("When the said variable is dereferenced %p\n", *ppCharacter );
	printf("When dereferenced a second time %c\n", **ppCharacter );

	printf("The value of a variable with type float is %f\n", Float );
	printf("The address of said variable is %p\n", &Float );
	printf("The value of a variable with type *float is %p\n", pFloat );
	printf("The address of said variable is %p\n", &pFloat );
	printf("When the said variable is dereferenced %f\n", *pFloat );
	printf("The value of a variable with type **float is %p\n", ppFloat );
	printf("The address of said variable is %p\n", &ppFloat );
	printf("When the said variable is dereferenced %p\n", *ppFloat );
	printf("When dereferenced a second time %f\n", **ppFloat );

	printf("The value of a variable with type double is %f\n", Double );
	printf("The address of said variable is %p\n", &Double );
	printf("The value of a variable with type *double is %p\n", pDouble );
	printf("The address of said variable is %p\n", &pDouble );
	printf("When the said variable is dereferenced %f\n", *pDouble );
	printf("The value of a variable with type **double is %p\n", ppDouble );
	printf("The address of said variable is %p\n", &ppDouble );
	printf("When the said variable is dereferenced %p\n", *ppDouble );
	printf("When dereferenced a second time %f\n", **ppDouble );

	return( 0 );
}
