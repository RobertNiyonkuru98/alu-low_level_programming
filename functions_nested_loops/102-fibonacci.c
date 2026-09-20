#include <stdio.h>

/**
 * main - prints the first 50 Fibonacci numbers, starting with 1 and 2
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int count;
	unsigned long fib1 = 1, fib2 = 2, sum;

	printf("%lu, %lu", fib1, fib2);

	for (count = 2; count < 50; count++)
	{
		sum = fib1 + fib2;
		printf(", %lu", sum);
		fib1 = fib2;
		fib2 = sum;
	}
	printf("\n");

	return (0);
}
