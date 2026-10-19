#include "main.h"
#include <stdlib.h>

/**
 * count_words - counts the number of words in a string
 * @str: string to evaluate
 *
 * Return: number of words
 */
int count_words(char *str)
{
	int i, count = 0, in_word = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ')
		{
			if (!in_word)
			{
				in_word = 1;
				count++;
			}
		}
		else
		{
			in_word = 0;
		}
	}
	return (count);
}

/**
 * free_tab - frees a 2D array of characters
 * @tab: array of strings
 * @i: number of elements to free
 */
void free_tab(char **tab, int i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
}

/**
 * word_len - returns the length of a word starting at str
 * @str: string pointing to start of word
 *
 * Return: length of the word
 */
int word_len(char *str)
{
	int len = 0;

	while (str[len] != '\0' && str[len] != ' ')
		len++;
	return (len);
}

/**
 * strtow - splits a string into words
 * @str: string to split
 *
 * Return: pointer to array of strings (words), or NULL on failure
 */
char **strtow(char *str)
{
	char **words;
	int i = 0, k, len, num_words, w = 0;

	if (str == NULL || *str == '\0')
		return (NULL);
	num_words = count_words(str);
	if (num_words == 0)
		return (NULL);
	words = malloc(sizeof(char *) * (num_words + 1));
	if (words == NULL)
		return (NULL);
	while (str[i] != '\0' && w < num_words)
	{
		if (str[i] != ' ')
		{
			len = word_len(str + i);
			words[w] = malloc(sizeof(char) * (len + 1));
			if (words[w] == NULL)
			{
				free_tab(words, w);
				return (NULL);
			}
			for (k = 0; k < len; k++, i++)
				words[w][k] = str[i];
			words[w][k] = '\0';
			w++;
		}
		else
		{
			i++;
		}
	}
	words[w] = NULL;
	return (words);
}
