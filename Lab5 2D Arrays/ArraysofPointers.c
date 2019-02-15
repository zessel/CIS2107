/*
Zach Essel
02/13/2019
CIS 2107 002
Lab 5: Project 02: Arrays of Pointers to Functions

The purpose of this program is to use a 2d arrays with pointers.
Required functions are
a max value search
a min value search
a summation of each row
an array print

All functions outside of the menu must have the same return (void) and the same arguments.

The program is also modified from a sample program we are given where all the arrays are passed by value.
The program is a simple grade book for students which stores exam scores.  

We have to allow for a flexible array size and the potential for grades to be entered manually
but I left in the option for random assignment for testing and ease of use.  The program also must use an array of funtions
as the backbone of the menu system.

*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define GRADE_MAX 100
#define GRADE_MIN 0

int students, exams;

void minimum(int (*grades_ptr)[exams]);
void maximum(int (*grades_ptr)[exams]);
void average(int (*grades_ptr)[exams]);
void printArray(int (*grades_ptr)[exams]);

/*
	main initializes the array, fills the array, handles the menu calls
*/

int main (void)
{
	
	// initialize the array
	
	puts("\n\nLet's create a gradebook!\n");
	printf("%s", "\tHow many students? ");
	scanf("%d", &students);
	printf("%s", "\tHow many exams? ");
	scanf("%d", &exams);
	int studentGrades[students][exams];
	
	void (*processGrades[4])(int (*grades_ptr)[exams]) = {printArray, minimum, maximum, average};
	
	int checkIfRandom;
	printf("%s", "\nWould you like to randomly generate grades?\n\t1 Yes\n\t2 No\n?");
	scanf("%d", &checkIfRandom);
	
	// fill the arrays with random numbers
	
	if (checkIfRandom == 1)
	{
		srand((unsigned int)time(NULL));
		for (size_t i = 0; i < students; ++i)
		{
			for (size_t j = 0; j < exams; ++j)
			{
			studentGrades[i][j] = rand() % (GRADE_MAX - GRADE_MIN + 1) + GRADE_MIN;
			}
		}
	}		
	
	// manually fill array
	
	else
	{			
		puts("");	
		for (size_t i = 0; i < students; ++i)
		{
			for (size_t j = 0; j < exams; ++j)
			{
				printf("\tenter [%zd][%zd]: ", i, j);
				scanf("%d", &studentGrades[i][j]);
			}
		}
	}
	
	// menu section
	
	int choice;

	puts("\n==============================\nEnter a choice:");
	puts("\t0  Print the array of grad");
	puts("\t1  Find the minimum grade");
	puts("\t2  Find the maximum grade");
	puts("\t3  Print the average on all tests for each student");
	puts("\t4  End Program\n");
	printf("%s", "Option: ");
	scanf("%d", &choice);
	while (choice != 4)
	{
		(*processGrades[choice])(studentGrades);
		
		puts("\n==============================\nEnter a choice:");
		puts("\t0  Print the array of grad");
		puts("\t1  Find the minimum grade");
		puts("\t2  Find the maximum grade");
		puts("\t3  Print the average on all tests for each student");
		puts("\t4  End Program\n");
		printf("%s", "Option: ");
		scanf("%d", &choice);		
	}
}

/*
	minimum is a basic minimum value search
*/

void minimum(int (*grades_ptr)[exams])
{
	int lowGrade = 100;
	
	for (size_t i = 0; i < students; ++i)
	{
		for (size_t j = 0; j < exams; ++j)
		{
			if (grades_ptr[i][j] < lowGrade)
				lowGrade = grades_ptr[i][j];
		}
	}
	
	printf("\n\nLowest grade: %d\n", lowGrade);
}

/*
	maximum is a basic maximum value search
*/

void maximum(int (*grades_ptr)[exams])
{
	int highGrade = 0;
	
	for (size_t i = 0; i < students; ++i)
	{
		for (size_t j = 0; j < exams; ++j)
		{
			if (grades_ptr[i][j] > highGrade)
				highGrade = grades_ptr[i][j];
		}
	}
	
	printf("\n\nHighest grade: %d\n", highGrade);
}


/*
	average averages a single row at a time and prints out the results for the entire array
*/

void average(int (*grades_ptr)[exams])
{
	puts("\n");
	for (size_t i = 0; i < students; ++i)
	{
		int total = 0;

		for (size_t j = 0; j < exams; ++j)
		{
				total += grades_ptr[i][j];
		}
		printf("The average grade for student %lu is %.2f\n", i, (double)total / exams);
	}
	
}


/*
	printArray increments through the array and prints out the values with slight formatting
*/

void printArray(int (*grades_ptr)[exams])
{
	puts("\n\nThe array is:");
	printf("%s", "		");
	
	for (size_t i = 0; i < exams; ++i)
	{
		printf("[%lu]  ", i);
	}
	for (size_t i = 0; i < students; ++i)
	{
		printf("\nstudentGrades[%lu] ", i);
		
		for (size_t j = 0; j < exams; ++j)
		{
			printf("%-5d", grades_ptr[i][j]);
		}
	}
	puts("");
}
