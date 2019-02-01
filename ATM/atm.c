/*
Zach Essel
01/29/2019
CIS 2107 002
Lab 3: ATM

This program simulates an ATM once a specific user beings to authenticate.
It has 3 basic functions: Balance, Withdraw, Deposit; and those functions
have various restrictions.  It maintains a balance, a number of transactions, and
amounts deposited and withdrawn for each instance of the program. 
*/
#include <stdio.h>
#include <stdlib.h>

#define PIN 3014
#define BALANCE 5000

void inputBars();
void printReceipt();
int authenticate();
int menu();
int getTransactions();
void setTransactions();
int getBalance();
void setBalance();
void withdraw();
void deposit();
void atmQuit();

unsigned int balance = BALANCE;    // balance is only accessible within atm.c but to all functions
unsigned int transactions = 0;     // transactions counts the transactions made in this program instance

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
					printReceipt();
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
	printReceipt is just a simple loop to check for valid input and then an if 
	statement that prints a line of tect and nothign else
*/

void printReceipt()
{
	int receipt;
	do
	{
		printf("%s", "\nWould you like a receipt?\n\n\t1. Yes\n\t2. No\n\nSelection: ");
		scanf("%d", &receipt);
		puts("");
	} while ((receipt > 2) || (receipt < 1));
	if (receipt == 1)
		puts("Receipt printing...\n");
}


/*
	authenticate gives the user 3 chances to enter their PIN number.  If the user fails
	the bulk of the programs functions will never be called and the program will terminate.
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
	while (tries < 2 && pin != PIN)
	{
		puts("Sorry, the PIN you entered is incorrect.  Please try again.\n");
		printf("%s", "\tPIN:  ");
		scanf("%d", &pin);
		inputBars();
		++tries;
	}
	if (tries == 2 && pin != PIN)
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
	getTransactions just gives you the current value of transactions
*/

int getTransactions ()
{
	return transactions;
}

/*
	incrementTransations gets called after a transaction and increases it's count
*/

void incrementTransations ()
{
	transactions += 1;
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
		puts("\nYou have already withdrawn your maximum for today\n");
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
		
		// tries increments to 3 even if third attempt is valid, requires full check
		
		if ((tries == 3) && ((takeOut < 1) || ((takeOut + takenToday) > 1000) || ((takeOut % 20) != 0)))
		{
			puts("You have exceeded the number of withdraw attempts.  The ATM will now exit.");
			atmQuit();
		}
		takenToday += takeOut;
		setBalance(0-takeOut);
		incrementTransations();
		printReceipt();
	}
}

/*
	deposit handles the logic for a user adding to the account balance and also the logic for invalid
	input related to those requests.
	Restrictions are that deposits may be a maximum of $10000 cumulative, must be positive.
	Checks if any further deposits are possible before jumping into the meat of the function.
	Takes input as a float and casts it as a int to prevent input errors from coinage.
*/
void deposit ()
{
	float userInput;					// 
	int putIn = 0;						// user input initialized
	static unsigned int inToday = 0;	// tracker for the total deposits in this instance eof the program
	int tries = 0;						// counter
	
	if (inToday >= 10000)
		puts("You have already deposited your maximum for today\n");
	else
	{
		while((tries < 3) && ((putIn < 1) || ((putIn + inToday) > 10000)))
		{
		puts("Please enter the amount you wish to deposit in whole bills (maximum $10000 daily)");
		puts("WARNING: Any coinage  will be ignored.\n");
		printf("\tRemaining depositable today : $%d\n", 10000 - inToday);  
		printf("%s", "\t$");
		scanf("%f", &userInput);
		putIn = (int)userInput;
		inputBars();
			if (putIn < 1)
				puts("This is an invalid amount\n");
			else if ((putIn + inToday) > 10000)
				puts("This will exceed your maximum daily deposits of $10000\n");		
		++tries;
		}
		
		// tries increments to 3 even if the third attempt at deposit is valid
		
		if ((tries == 3) && ((putIn < 1) || ((putIn + inToday) > 10000)))
		{
			puts("You have exceeded the number of deposit attempts.  The ATM will now exit.");
			atmQuit();
		}
		inToday += putIn;
		setBalance(putIn);
		incrementTransations();
		printReceipt();
	}
}

/*
	atmQuit simply gives a goodbye message and exits the program
*/

void atmQuit()
{
	printf("\nYou have made %d transactions today\n", getTransactions());
	puts("\nThank you for banking with us\n");
	exit(0);
}
