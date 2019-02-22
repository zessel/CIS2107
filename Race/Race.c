/*
Zach Essel
02/21/2019
CIS 2107 002
Lab 6: Race

This program simulates the turtle and the hare race.  I do this using 5 functions outside of main
random value generator
movement for the hare
movement for the turtle
a formatter for the "race track" string
a winner output check

I have the length of the race as a defined constant so you can change it from the painfully slow default of 70.

The main contains the initializations and the loop of the functions

I decided to update a single string repeatedly for the main output.  I think creating and concatting multiple strings would be a bigger
hit on memory then rewriting the one string.  For the "erasing" I could have written a loop similar to the initialization of the string, 
but my assumption is memset does exactly that and it looks cleaner.  

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define RACE_LENGTH 70

int getRandom ();
int moveHare (int harePos);
int moveTurtle (int turtPos);
void updateRaceString (char *track_ptr, int harePos, int turtPos);
void winCheck (int harePos, int turtPos);

void main ()
{
	int turtPos = 1;
	int harePos = 1;
	
	// Space to display 70 Race characters, a finish line "OUCH!!!", and a null terminator

	char track[RACE_LENGTH + 7 + 1] = "";

	// fills string with spaces and sets final index to null.  Needed for strlen to call correctly in updateRaceString
	
	for (size_t i = 0; i < sizeof(track); ++i)
		track[i] = ' ';
	track[RACE_LENGTH + 7 + 1] = '\0';

	// seeds random with time
	
	srand((unsigned int)time(NULL));
	
	puts("\n\nON YOUR MARK, GET SET");
	puts("BANG               !!!!");
	puts("AND THEY'RE OFF    !!!!");
	
	while (harePos != RACE_LENGTH && turtPos != RACE_LENGTH)
	{
		harePos = moveHare(harePos);
		turtPos = moveTurtle(turtPos);
		updateRaceString(track, harePos, turtPos);
		printf("%s\n", track); 
		sleep(1);
	}
	
	winCheck(harePos, turtPos);
	exit(0);
}

/*
	getRandom returns a int between 1 and 10. Full formula is  % (MAX - MIN + 1) + MIN
*/

int getRandom()
{
	return rand() % 10 + 1;
}


/*
	moveHare gets a random value and puts it through the switch case for hare movement.  Then checks for bounds because
	it's later used as an array index.  Chose to leave a large switch case with 10 options so it can be more
	easily modified.
*/

int moveHare (int harePos)
{
	int roll = getRandom();
	
	switch (roll)
	{
		case 1:
		case 2:
			break;
		case 3:
		case 4:
			harePos += 9;
			break;
		case 5:
			harePos -= 12;
			break;
		case 6:
		case 7:
		case 8:
			harePos += 1;
			break;
		case 9:
		case 10:
			harePos -= 2;
	}
	
	if (harePos > RACE_LENGTH)
		harePos = RACE_LENGTH;
	else if (harePos < 1)
		harePos = 1;
	return harePos;
}

/*
	moveTurtle functions the same as moveHare, but for the turtle variable.
*/

int moveTurtle (int turtPos)
{
	int roll = getRandom();
	
	switch (roll)
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			turtPos += 3;
			break;
		case 6:
		case 7:
			turtPos -= 6;
			break;
		case 8:
		case 9:
		case 10:
			turtPos += 1;
	}
	
	if (turtPos > RACE_LENGTH)
		turtPos = RACE_LENGTH;
	else if (turtPos < 1)
		turtPos = 1;
	return turtPos;
}

/*
	updateRaceString rewrites the entire output string with spaces before inserting the positions or collision.
	If the race length were long enough, might be worthwhile to create an erase function that calls immediately after output
	that just resets the 2 or 7 spaces that were changed.
*/

void updateRaceString (char *track_ptr, int harePos, int turtPos)
{
	memset(track_ptr, ' ', strlen(track_ptr));

	if (harePos == turtPos)
	{
		track_ptr[harePos - 1] = 'O';
		track_ptr[harePos + 0] = 'U';
		track_ptr[harePos + 1] = 'C';
		track_ptr[harePos + 2] = 'H';
		track_ptr[harePos + 3] = '!';
		track_ptr[harePos + 4] = '!';
		track_ptr[harePos + 5] = '!';
	}
	else
	{
		track_ptr[harePos - 1] = 'H';
		track_ptr[turtPos - 1] = 'T';
	}
}

/*
	winCheck tests for which condition broke the while loop in main and defaults to a turtle victory
*/

void winCheck (int harePos, int turtPos)
{
	if (turtPos == RACE_LENGTH)
		puts("TORTOISE WINS!!! YAY!!!\n");
	else if (harePos == RACE_LENGTH)
		puts("Hare wins. Yuch.\n");
}
