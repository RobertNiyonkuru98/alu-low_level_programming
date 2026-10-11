#include "main.h"

/**
 * find_sqrt - finds the natural square root of a number recursively
 * @n: number to find square root of
 * @i: iterator/candidate root
 *
 * Return: square root of n, or -1 if not found
 */
int find_sqrt(int n, int i)
{
	if (i * i == n)
		return (i);
	if (i * i > n)
		return (-1);
	return (find_sqrt(n, i + 1));
}

/**
 * _sqrt_recursion - returns the natural square root of a number
 * @n: number to calculate square root of
 *
 * Return: natural square root, or -1 if n does not have one
 */
int _sqrt_recursion(int n)
{
	if (n < 0)
		return (-1);
	return (find_sqrt(n, 0));
}
