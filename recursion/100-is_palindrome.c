#include "main.h"

/**
 * _strlen_pal - returns the length of a string recursively
 * @s: string to evaluate
 *
 * Return: length of string
 */
int _strlen_pal(char *s)
{
	if (*s == '\0')
		return (0);
	return (1 + _strlen_pal(s + 1));
}

/**
 * check_pal - checks the characters recursively for palindrome
 * @s: string to check
 * @start: starting index
 * @end: ending index
 *
 * Return: 1 if palindrome, 0 if not
 */
int check_pal(char *s, int start, int end)
{
	if (start >= end)
		return (1);
	if (s[start] != s[end])
		return (0);
	return (check_pal(s, start + 1, end - 1));
}

/**
 * is_palindrome - checks if a string is a palindrome
 * @s: string to evaluate
 *
 * Return: 1 if palindrome, 0 if not
 */
int is_palindrome(char *s)
{
	int len;

	if (*s == '\0')
		return (1);
	len = _strlen_pal(s);
	return (check_pal(s, 0, len - 1));
}
