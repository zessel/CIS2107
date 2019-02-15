/*
Zach Essel
02/12/2019
CIS 2107 002
Lab 5: Project 01: 2D Arrays Processing

The purpose of this program is to use 2d arrays but not pointers.
Required functions are
a max value search that isn't called?
a summation of each row
a summation of each column
a check if the array is square
an array console printing 

I imagine we are supposed to have the max function called but there is no output specified
for it on the model we are supposed to follow exactly.
*/

#include <stdio.h>
#include <stdlib.h>

int max (int rows, int columns, int array[rows][columns]);
int rowSum (int index, int rows, int columns, int array[rows][columns]);
int columnSum (int index, int rows, int columns,int array[rows][columns]);
void isSquare (int rows, int columns);
void displaysOutputs (int rows, int columns, int array[rows][columns]);

void main ()
{
	int rows, columns;
	puts("\n\nLet's create a 2Dim Array!\n\n");
	printf("%s", "\tHow many rows? ");
	scanf("%d", &rows);
	printf("%s", "\tHow many columns? ");
	scanf("%d", &columns);
	int array[rows][columns];
	
	puts("");	
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			printf("\tenter [%zd][%zd]: ", i, j);
			scanf("%d", &array [i][j]);
		}
	}

	puts("");	
	for (size_t i = 0; i < rows; ++i)
	{
		printf("Sum of row %zd = %d\n", i + 1, rowSum(i, rows, columns, array));
	}
	
	puts("");	
	for (size_t j = 0; j < columns; ++j)
	{
		printf("Sum of column %zd = %d\n", j + 1 , columnSum(j, rows, columns, array));
	}
	
	isSquare(rows, columns);
	
	printf("\nThe maximum value is %d\n", max(rows, columns, array));
	
	displaysOutputs(rows, columns, array);

	puts("");
}

/*
	max is your basic maximum value search algorithm
*/
int max (int rows, int columns, int array[rows][columns])
{
	int tempMax = array[0][0];
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			if (array[i][j] > tempMax)
				tempMax = array[i][j];
		}
	}
	return tempMax;
}

/*
	rowSum takes in lots of arguments because the array has to be passed by value.
	I believe it could work without the "int rows" because the compiler only requires
	the columns; however, I included both just so it and columnSum would have the same signatures.
	It only works on a single row at a time
*/
int rowSum (int index, int rows, int columns, int array[rows][columns])
{
	int sum = 0;
	for (size_t j = 0; j < columns; ++j)
	{
		sum += array[index][j];
	}
	return sum;
}

/*
	columnSum adds the values of a given column of a value passed array and
	returns the sum
*/
int columnSum (int index, int rows, int columns,int array[rows][columns])
{
	int sum = 0;
	for (size_t i = 0; i < rows; ++i)
	{
		sum += array[i][index];
	}
	return sum;
}

/*
	isSquare returns text saying if the array has the same number of rows 
	and columns.  Decided to jusst handle printing here instead of returning
	a bool and then having this mess in main.
*/
void isSquare (int rows, int columns)
{
	if (rows == columns)
		puts("\nThis is a square array.");
	else
		puts("\nThis is not a square array.");
}

/*
	displaysOutputs goes index by index printing the value stored there.
	some slight formatting to adhere to the given requirments
*/	
void displaysOutputs (int rows, int columns, int array[rows][columns])
{
	puts ("\nHere is your 2Dim array:\n");
		for (size_t i = 0; i < rows; ++i)
	{
		printf("%s", "[");
		for (size_t j = 0; j < columns; ++j)
		{
			printf("%d", array[i][j]);
			if (j != (columns - 1))
				printf("%s", ", ");
		}
		puts("]");
	}
}
