#include <stdio.h>
#include <stdlib.h>

void main ()
{
	int error = 0;
	int quant;
	double price, discount, cost;
	
	printf("%s","\n\nWelcome to \"Temple\" store\n\n\tEnter item price: ");
	scanf("%lf", &price);
	
	// Checks user input for 0 or negative numbers with an if else
		
	if (price <= 0)
	{
		puts("\n\tThis is not a valid item price.\n\tPlease run the program again\n");
		error = 1;
	}
	else
	{
		printf("\tEnter quantity: ");
		scanf("%d", &quant);
		if (quant < 1)
		{
			puts("\n\tThis is not a valid quantity order.\n\tPlease run the program again\n");
			error = 1;
		}
	}
	
	// Hides program execution behind an error detecting boolean
	
	if(error == 0)
	{
		cost = quant*price;
		printf("\n\tThe item price is: $%.1lf\n", price);
		printf("\tThe order is: %d item(s)\n", quant);
		printf("\tThe cost is: $%.1lf\n", cost);
		
		/* Can get away with another if else tree here for the discount amount
		   figured just typing out the discount was slightly faster than assigning
		   it to a variable and immediately calling it.                            */
		   
		printf("%s", "\tThe discount is: ");
			if (quant < 50)
			{
				puts("0%");
				discount = 0;
			}
			else if (quant < 100)
			{
				puts("10.0%");
				discount = .1 * cost;
			}
			else if (quant < 150)
			{
				puts("15.0%");
				discount = .15 * cost;
			}
			else
			{
				puts("25.0%");
				discount = .25 * cost;
			}
			
		printf("\tThe discount amount is: $%.1lf\n", discount);
		printf("\tThe total is: $%.1lf\n\n", cost - discount);
	}
	
	printf("Thank You for using \"Temple\" store\n\n");
	exit(0);
}
