/*
Zach Essel
01/29/2019
CIS 2107 002
Lab 3: ATM

This program simulates an ATM once a specific user beings to authenticate.  
*/
#include <stdio.h>
#include <stdlib.h>

void inputBars();
int authenticate();
int menu();
int getBalance();
void setBalance();
void withdraw();
void deposit();
void atmQuit();

unsigned int balance = 5000;    // balance is only accessible within atm.c but to all functions

int main ()
{
	int choice; 				// Used to hold the return value from the menu function
	int login = authenticate(); // a quick check if the PIN check succeeds
	
	if (login)					
	{
		do
		{
			choice = menu();
			switch (choice)
			{
				case 1:
					printf("Your account balance is currently: $%d\n\n", getBalance());
					break;
				case 2:	
					withdraw();
					break;
				case 3:
					deposit();
					break;
			}
		} while (choice != 4);
	}
	atmQuit();
}

/*
	inputBars runs after every scanf in an attempt to make console output more readable
*/

void inputBars()
{
	puts("\n==============================================================\n");
}

/*
	authenticate gives the user 3 chances to enter their PIN number.  If the user fails
	the bulk of the programs functions will never be called and the program will terminate.
	For simplicity the users PIN is hardcoded into the function.
*/	

int authenticate()
{
	int pin;		// user input variable
	int tries = 0;  // attempt counter
	int login = 1;  // boolean
	
	puts("\n\nWelcome, please enter your PIN to continue\n");
	printf("%s", "\tPIN:  ");
	scanf("%d", &pin);
	inputBars();
	while (tries < 2 && pin != 3014)
	{
		puts("Sorry, the PIN you entered is incorrect.  Please try again.\n");
		printf("%s", "\tPIN:  ");
		scanf("%d", &pin);
		inputBars();
		++tries;
	}
	if (tries == 2 && pin != 3014)
	{
		puts("You have exceeded the number of PIN attempts on this ATM.");
		login = 0;
	}
	return login;		
}

/*
	menu is the root interactable function in this program.  It self contains the logic
	for handling incorrect user input.
*/

int menu ()
{	
	int choice;	// user input
	do
	{
		puts("Available menu actions:\n");
		puts("\t1: Account Balance");
		puts("\t2: Account Withdrawal");
		puts("\t3: Account Deposition");
		puts("\t4: Quit");
		printf("%s", "\nPlease enter the number of your selection: ");
		scanf("%d", &choice);
		inputBars();
		if ((choice > 4) || (choice < 1))
		{
			puts("That is not a valid menu selection.  Please try again.");
		}
	} while ((choice > 4) || (choice < 1));
	return choice;
}

/*
	getBalance just sends the global balance variable to whatever calls it.
*/

int getBalance ()
{
	return balance;
}

/*
	setBalance is the only way to directly manipulate the global balance variable.  It adds the amount
	sent by argument.
*/

void setBalance (int amount)
{
	balance += amount;
}

/*
	withdraw handles the logic for a user deducting from the account balance and also the logic for invalid
	input related to those requests.
	Restrictions are that withdraws may be a maximum of $1000 cumulative, must be positive, and must be in $20s
	Checks if any further withdrawals are possible before jumping into the meat of the function.
*/
void withdraw ()
{
	int takeOut = 0;						// user input initialized
	static unsigned int takenToday = 0;		// tracker for the total withdrawn in this instance of the program
	int tries = 0;							// counter
	
	if (takenToday >= 981)
		puts("\nYou have already withdrawn your maximum for today");
	else
	{
		while((tries < 3) && ((takeOut < 1) || ((takeOut + takenToday) > 1000) || ((takeOut % 20) != 0)))
		{
		puts("Please enter the amount you wish to withdraw in $20 increments (maximum $1000 daily)\n");
		printf("\tRemaining withdrawable today : $%d\n", 1000 - takenToday);  
		printf("%s", "\t$");
		scanf("%d", &takeOut);
		inputBars();
			if (takeOut < 1)
				puts("This is an invalid amount\n");
			else if ((takeOut + takenToday) > 1000)
				puts("This will exceed your maximum daily withdrawal of $1000\n");
			else if ((takeOut % 20) != 0)
				puts("This machine only serves withdrawals in increments of $20\n");		
		++tries;
		}
		if (tries == 3)
		{
			puts("You have exceeded the number of withdraw attempts.  The ATM will now exit.");
			atmQuit();
		}
		takenToday += takeOut;
		setBalance(0-takeOut);
	}
}

/*
	deposit handles the logic for a user adding to the account balance and also the logic for invalid
	input related to those requests.
	Restrictions are that deposits may be a maximum of $10000 cumulative, must be positive.
	Checks if any further deposits are possible before jumping into the meat of the function.
*/
void deposit ()
{
	int putIn = 0;						// user input initialized
	static unsigned int inToday = 0;	// tracker for the total deposits in this instance eof the program
	int tries = 0;						// counter
	
	if (inToday >= 10000)
		puts("You have already deposited your maximum for today\n");
	else
	{
		while((tries < 3) && ((putIn < 1) || ((putIn + inToday) > 10000)))
		{
		puts("Please enter the amount you wish to deposit in (maximum $10090 daily)\n");
		printf("\tRemaining depositable today : $%d\n", 10000 - inToday);  
		printf("%s", "\t$");
		scanf("%d", &putIn);
		inputBars();
			if (putIn < 1)
				puts("This is an invalid amount\n");
			else if ((putIn + inToday) > 10000)
				puts("This will exceed your maximum daily deposits of $10000\n");		
		++tries;
		}
		if (tries == 3)
		{
			puts("You have exceeded the number of deposit attempts.  The ATM will now exit.");
			atmQuit();
		}
		inToday += putIn;
		setBalance(putIn);
	}
}

/*
	atmQuit simply gives a goodbye message and exits the program
*/

void atmQuit()
{
	puts("\nThank you for banking with us today\n");
	exit(0);
}
