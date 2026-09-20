#include "main.h"

/**
 * print_times_table - prints the n times table, starting with 0
 * @n: number of the times table
 */
void print_times_table(int n)
{
	int i, j, mult;

	if (n >= 0 && n <= 15)
	{
		for (i = 0; i <= n; i++)
		{
			for (j = 0; j <= n; j++)
			{
				mult = i * j;
				if (j == 0)
					_putchar(mult + '0');
				else
				{
					_putchar(',');
					_putchar(' ');
					if (mult < 10)
					{
						_putchar(' ');
						_putchar(' ');
						_putchar(mult + '0');
					}
					else if (mult < 100)
					{
						_putchar(' ');
						_putchar((mult / 10) + '0');
						_putchar((mult % 10) + '0');
					}
					else
					{
						_putchar((mult / 100) + '0');
						_putchar(((mult / 10) % 10) + '0');
						_putchar((mult % 10) + '0');
					}
				}
			}
			_putchar('\n');
		}
	}
}
