#include <stdio.h>

/**
 * main - finds and prints the first 98 Fibonacci numbers,
 * starting with 1 and 2
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	unsigned long int fib1 = 1, fib2 = 2, sum;
	unsigned long int fib1_half1, fib1_half2, fib2_half1, fib2_half2;
	unsigned long int sum_half1, sum_half2;
	int count;

	printf("%lu, %lu", fib1, fib2);
	for (count = 2; count < 92; count++)
	{
		sum = fib1 + fib2;
		printf(", %lu", sum);
		fib1 = fib2;
		fib2 = sum;
	}

	fib1_half1 = fib1 / 1000000000;
	fib1_half2 = fib1 % 1000000000;
	fib2_half1 = fib2 / 1000000000;
	fib2_half2 = fib2 % 1000000000;

	for (; count < 98; count++)
	{
		sum_half1 = fib1_half1 + fib2_half1;
		sum_half2 = fib1_half2 + fib2_half2;

		if (sum_half2 >= 1000000000)
		{
			sum_half1 += 1;
			sum_half2 %= 1000000000;
		}
		
		printf(", %lu%09lu", sum_half1, sum_half2);

		fib1_half1 = fib2_half1;
		fib1_half2 = fib2_half2;
		fib2_half1 = sum_half1;
		fib2_half2 = sum_half2;
	}
	printf("\n");
	return (0);
}
