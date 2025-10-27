#include "main.h"

/**
 * _strchr - locates a character in a string
 * @s: string to search
 * @c: character to locate
 *
 * Return: pointer to first occurrence of c, or NULL if not found
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}

	/* Check for the null terminator if c is '\0' */
	if (c == '\0')
	{
		return (s);
	}

	return (NULL);
}
