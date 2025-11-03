#include "main.h"
#include <stdlib.h>

/**
 * word_count - counts the number of words in a string
 * @str: string to check
 *
 * Return: number of words
 */
int word_count(char *str)
{
	int i = 0, count = 0;

	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0')
		{
			count++;
			while (str[i] != ' ' && str[i] != '\0')
				i++;
		}
	}
	return (count);
}

/**
 * strtow - splits a string into words
 * @str: the string to split
 *
 * Return: pointer to an array of strings (words), or NULL on failure
 */
char **strtow(char *str)
{
	char **words;
	int i = 0, j, k, len, wc, start;

	if (str == NULL || *str == '\0')
		return (NULL);

	wc = word_count(str);
	if (wc == 0)
		return (NULL);

	words = malloc(sizeof(char *) * (wc + 1));
	if (words == NULL)
		return (NULL);

	for (k = 0; k < wc; k++)
	{
		while (str[i] == ' ')
			i++;
		start = i;
		while (str[i] != ' ' && str[i] != '\0')
			i++;
		len = i - start;

		words[k] = malloc(sizeof(char) * (len + 1));
		if (words[k] == NULL)
		{
			while (k--)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (j = 0; j < len; j++)
			words[k][j] = str[start + j];
		words[k][j] = '\0';
	}
	words[k] = NULL;

	return (words);
}
