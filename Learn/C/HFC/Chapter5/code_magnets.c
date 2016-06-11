#include <stdio.h>

int count = 0;

typedef enum unit_of_measure 
{
	COUNT, PINTS, POUNDS
} unit_of_measure;

typedef union
{
	int count;
	float volume;
	float weight;
} quantity;

typedef struct
{
	const char* name;
	const char* country;
	quantity amount;
	unit_of_measure units;
} fruit_order;

void display (fruit_order order)
{
	if (count == 0)
		printf("This order contains: \n");
		
	printf ("%i.	", count+1); 
	
	if (order.units == PINTS)
	{
		printf("%2.3f pints of %s from %s\n", order.amount.volume, order.name, order.country);
	}
	
	else if (order.units == POUNDS)
	{
		printf("%2.2f pounds of %s from %s\n", order.amount.weight, order.name, order.country);
	}
	
	else
	{
		printf("%i %s from %s\n", order.amount.count, order.name, order.country);
	}
	
	count++;
}

int main()
{
	fruit_order apples = {"Apples", "Greece", .amount.count=144, COUNT};
	
	fruit_order strawberries = {"Strawberries", "Spain", .amount.weight=5.5, POUNDS};
	
	fruit_order beer = {"Beer", "Germany", .amount.volume=25, PINTS};
	
	display(apples);
	display(strawberries);
	display(beer);
	
	return 0;
}