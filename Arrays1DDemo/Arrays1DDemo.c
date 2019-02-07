/*
Zach Essel
02/04/2019
CIS 2107 002
Lab 4: Processing 1D Arrays

The purpose of this program is to familiarize myself with 1d arrays by
manipulating them with different specific functions.  The required functions are:
Array generation,
Maximum value searching,
Array reversal,
Designated range reversal, and 
Sequence searching.

I also added a simple print function available from the main menu, and another ranged print function that is 
not accessable from the program menu.  Ranged print was designed to help with readability when performing functions
on smaller segments of the overall array 
*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 64	// The size of the array
#define ARRAY_MIN 0	// Used to calculate the minimum a random number can be for the array
#define ARRAY_MAX 100	// Used to calculate the maximum a random number can be for the array

unsigned int globalArray[ARRAY_SIZE]; 

int menu();
int indexCheck(); 
void printArrayDefault(); 
void printArrayRange(); 
void fillArray();
unsigned findWithRange();
void reverseArray();
void reverseInRange();
unsigned findSequence();

/*
	main has a very basic main menu loop and runs through the first array generation automatically.
	Some of the index input could be moved to a new function to make main look cleaner but I thought it
	was okay for the scope of this program to have it a bit messy.  Couldn't find a clear answer on
	whether leaving the break out of the first case to intentionally run the second is an acceoptable practice
	but I like it here.
*/
void main()
{
	int choice = 1;
	int start, end;
	
	while (choice > 0 && choice < 7)
	{ 
		switch (choice)
		{
			case 1:
				fillArray();
				printf("\nThis array was generated with a size of %d and random values between %d-%d\n", ARRAY_SIZE, ARRAY_MIN, ARRAY_MAX);
			case 2:
				printArrayDefault();
				break;
			case 3:
				printf("%s", "Enter a starting index: ");
				scanf("%d", &start);
				printf("%s", "Enter an ending index: ");
				scanf("%d", &end);
				if (indexCheck(start, end) != -1)
					printf("\nMax = %d\n", findWithRange(start, end));
				break;
			case 4:
				reverseArray();
				break;
			case 5: 
				printf("%s", "Enter a starting index: ");
				scanf("%d", &start);
				printf("%s", "Enter an ending index: ");
				scanf("%d", &end);
				if (indexCheck(start, end) != -1)
					reverseInRange(start, end);
				break;
			case 6:
				printf("%s", "Enter the first term: ");
				scanf("%d", &start);
				printf("%s", "Enter the second term: ");
				scanf("%d", &end);
				int found = findSequence(start, end);
				if (found >= 0)
					printf("\nThe sequence can be found at index %d\n", found);
				else
					puts("Sequence not found");
				break;
		}
		
		choice = menu();
	}
}

/*
	menu displays the main options of the program and handles the input for that choice
*/
int menu ()
{
	int option;
	puts("\n============================================================\n");
	puts("\n\t1: Generate a new array");
	puts("\t2: Print the current array");
	puts("\t3: Find the maximum value in the array between two indexes");
	puts("\t4: Reverse the entire current array");
	puts("\t5: Reverses a portion of the array between two indexes");
	puts("\t6: Searches the array for two sequential values\n");
	printf("%s", "Select an option 1-6, other numbers exit the program:  ");
	scanf("%d", &option);
	return option;
}

/*
	indexCheck moves the messy index validation out of main
*/
int indexCheck (int start, int end)
{
	int check = 0;
	if (start < 0)
	{
		puts("Starting index is out of bounds");
		check = -1;
	}
	else if (end >= ARRAY_SIZE)
	{
		puts("Ending index is out of bounds");
		check = -1;
	}
	else if (start > end)
	{
		puts("Starting index must be less than ending index");
		check = -1;
	}
	return check;				
}

/*
	printArrayDefault prints out an the entire array based on ARRAY_SIZE 
*/
void printArrayDefault ()
{
	puts("");
	for (size_t i = 0; i < ARRAY_SIZE; ++i)
	{
		printf("%3d ", globalArray[i]);
		if (((i + 1) % 8) == 0)
			puts("");		
	}
	puts("");
}

/*
	printArrayRange prints out the portion of the array from a given start and end index.
	Prints 8 values to a row.  For testing.
*/
void printArrayRange (unsigned int start, unsigned int end)
{
	puts("");
	for (size_t i = start; i <= end; ++i)
	{
		printf("%3d ", globalArray[i]);		
		if (((i - start + 1) % 8) == 0)
			puts("");
	}
	puts("");
}

/*
	fillArray uses a global array because we aren't allowed to use pointers and if it returned
	integers to main fillArray would just be a random number call
*/
void fillArray ()
{
	srand((unsigned int)time(NULL));
	for (size_t i = 0; i < ARRAY_SIZE; ++i)
	{
		globalArray[i] = rand() % (ARRAY_MAX - ARRAY_MIN + 1) + ARRAY_MIN;
	}
}

/*
	findWithRange returns the maximum value in the array between 2 given indexes.  Assumes inputs are valid
	and does no checking
*/
unsigned findWithRange (unsigned int start, unsigned int end)
{
	unsigned int max = globalArray[start];
	for (size_t i = start + 1; i <= end; ++i)
	{	
		if (max < globalArray[i])
			max = globalArray[i];
	}
	return max;
}

/*
	reverseArray reverses globalArray by copying it into a locally scoped array,
	then iterating backwards through globalArray while iterating forward through the copy. 
*/
void reverseArray ()
{
	unsigned int tempArray[ARRAY_SIZE];
	
	for (size_t i = 0; i < ARRAY_SIZE; ++i)
	{
		tempArray[i] = globalArray[i];
	}
	
	for (size_t i = 0; i < ARRAY_SIZE; ++i)
	{
		globalArray[ARRAY_SIZE - i - 1] = tempArray[i];
	}
}

/*
	reverseArray reverses a portion of globalArray by copying it into a locally scoped array,
	then iterating backwards through globalArray while iterating forward through the copied portion. 
	The start and end values are not checked and assumed valid
*/
void reverseInRange (unsigned int start, unsigned int end)
{
	unsigned int tempArray[end - start + 1];
	
	for (size_t i = 0; i < (end - start + 1); ++i)
	{
		tempArray[i] = globalArray[i + start];
	}
	
	for (size_t i = 0; i < (end - start + 1); ++i)
	{
		globalArray[end - i] = tempArray[i];
	}
}

/*
	findSequence looks for two consecutive values in the array,
	if found it returns the index of the first value.  Does not bother to check 
	the final value of the array when looking for "tom."  If no sequence is found
	it returns -1
*/
unsigned findSequence (unsigned int tom, unsigned int jerry)
{
	int tomsIndex = -1;
	
	for (size_t i = 0; i < ARRAY_SIZE - 1; ++i)
	{
		if (globalArray[i] == tom && globalArray[i + 1] == jerry)
			tomsIndex = i;
	}
	return tomsIndex;
}
