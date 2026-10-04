#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - generates a random valid password for 101-crackme
 *
 * Return: Always 0
 */
int main(void)
{
	int sum = 2772;
	char c;

	srand(time(NULL));

	while (sum > 126)
	{
		c = rand() % 94 + 33;
		if (sum - c < 33)
			continue;
		printf("%c", c);
		sum -= c;
	}
	printf("%c", sum);
	return (0);
}
