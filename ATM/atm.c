#include <stdio.h>
#include <stdlib.h>

int authenticate() ;
int menu();
int getBalance();
int setBalance();
int withdraw();
int deposit();
void atmQuit();

unsigned int balance = 5000;

int main ()
{
	int choice;
	int login = authenticate();
	if (login)
	{
		do
		{
			int choice = menu();
			switch (choice)
			{
				case 1:
					printf("Your account balance is currently: $%d", getBalance());
					break;
				case 2:	
					withdraw();
					break;
				case 3:
					deposit();
					break;
				case 4:
					printf("%d", choice);
					break;
			}
			printf("choice is right now %d", choice);
		} while (choice != 4);
	}
	atmQuit();
}

int authenticate()
{
	int pin;
	int tries = 0;
	int login = 1;
	puts("\n\nWelcome, please enter your PIN to continue\n");
	printf("%s", "\tPIN:  ");
	scanf("%d", &pin);
	while (tries < 2 && pin != 3014)
	{
		puts("\nSorry, the PIN you entered is incorrect.  Please try again.\n");
		printf("%s", "\tPIN:  ");
		scanf("%d", &pin);
		++tries;
	}
	if (tries == 2 && pin != 3014)
	{
		puts("\nYou have exceeded the number of PIN attempts on this ATM.");
		login = 0;
	}
	return login;		
}

int menu ()
{	
	int choice;
	do
	{
		puts("Available menu actions:\n");
		puts("\t1: Account Balance");
		puts("\t2: Account Withdrawal");
		puts("\t3: Account Deposition");
		puts("\t4: Quit");
		puts("\nPlease enter the number of your selection: ");
		scanf("%d", &choice);
		if ((choice > 4) || (choice < 1))
		{
			puts("\n\nThat is not a valid menu selection.  Please try again.\n\n");
		}
	} while ((choice > 4) || (choice < 1));
	return choice;
}

int getBalance ()
{
	return balance;
}

int setBalance (int amount)
{
	balance += amount;
}

int withdraw ()
{
	int takeOut = 0;
	static unsigned int takenToday = 0;
	int tries = 0;
	if (takenToday >= 981)
		puts("You have already withdrawn your maximum for today");
	else
	{
		while((tries < 3) && ((takeOut < 1) || ((takeOut + takenToday) > 1000) || ((takeOut % 20) != 0)))
		{
		puts("Please enter the amount you wish to withdraw in $20 increments (maximum $1000 daily)\n");
		printf("\tRemaining withdrawable today : $%d\n", 1000 - takenToday);  
		printf("%s", "\t$");
		scanf("%d", &takeOut);
			if (takeOut < 1)
				puts("This is an invalid amount");
			else if ((takeOut + takenToday) > 1000)
				puts("This will exceed your maximum daily withdrawal of $1000");
			else if ((takeOut % 20) != 0)
				puts("This machine only serves withdrawals in increments of $20");		
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

int deposit ()
{
	int putIn = 0;
	static unsigned int inToday = 0;
	int tries = 0;
	if (inToday >= 10000)
		puts("You have already deposited your maximum for today");
	else
	{
		while((tries < 3) && ((putIn < 1) || ((putIn + inToday) > 10000)))
		{
		puts("Please enter the amount you wish to deposit in (maximum $10090 daily)\n");
		printf("\tRemaining depositable today : $%d\n", 10000 - inToday);  
		printf("%s", "\t$");
		scanf("%d", &putIn);
			if (putIn < 1)
				puts("This is an invalid amount");
			else if ((putIn + inToday) > 10000)
				puts("This will exceed your maximum daily deposits of $10000");		
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

void atmQuit()
{
	puts("Thank you for banking with us today.");
	exit(0);
}
