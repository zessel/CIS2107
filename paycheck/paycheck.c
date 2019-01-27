#include <stdio.h>
#include <stdlib.h>

int main()
{
	int error = 0;
	int employeeNumber;
	double hours, wage, regPay, netPay;
	double overPay = 0;
	
	printf("%s", "\n\nWelcome to \"TEMPLE HUMAN RESOURCES\"\n\n\tEnter Employee Number: ");
	scanf("%d", &employeeNumber);
	
	// Small if else tree to check for 0 or negatives in the user input
	
	if (employeeNumber < 1)
	{
		puts("\n\tThis is not a valid Employee Number.\n\tPlease run the program again\n");
		error = 1;
	}
	else
	{
		printf("%s", "\tEnter Hourly Salary: ");
		scanf("%lf", &wage);
		if (wage <= 0)
		{
			puts("\n\tThis is not a valid hourly salary amount.\n\tPlease run the program again\n");
			error = 1;
		}
		else
		{
			printf("%s", "\tEnter Weekly Time: "); 
			scanf("%lf", &hours);
			if (hours <= 0)
			{
				puts("\n\tThis is not a weekly time.\n\tPlease run the program again\n\n");
				error = 1;
			}
		}
	}
	
	// the bulk of the program hides behind a boolean that checks if the user input was good
	
	if(error == 0)
	{
		printf("\t==============================\n\tEmployee #: %d\n", employeeNumber);
		printf("\tHourly Salary: $%.1lf\n", wage);
		printf("\tWeekly Time: %.1lf\n", hours);
		
		if(hours > 40)
		{
			regPay = wage * 40;
			overPay = (hours - 40) * wage * 1.5;
		}
		else
			regPay = wage * hours;
		
		netPay = regPay + overPay; 

		printf("\tRegular Pay: $%.1lf\n", regPay); 
		printf("\tOvertime Pay: $%.1lf\n", overPay); 
		printf("\tNet Pay: $%.1lf\n", netPay); 
		puts("\t==============================\n");
	}

	puts("Thank you for using \"TEMPLE HUMAN RESOURCES\"\n");
	exit(0);
}
