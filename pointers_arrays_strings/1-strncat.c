#include "main.h"

/**
 * _strncat - Concatenates two strings using at most n bytes from src
 * @dest: The destination string
 * @src: The source string to append
 * @n: Maximum number of bytes to use from src
 *
 * Return: Pointer to the resulting string dest
 */
char *_strncat(char *dest, char *src, int n)
{
	char *ptr = dest;
	int i = 0;

	/* Find the end of dest */
	while (*ptr != '\0')
	{
		ptr++;
	}

	/* Copy at most n bytes from src to the end of dest */
	while (i < n && src[i] != '\0')
	{
		*ptr = src[i];
		ptr++;
		i++;
	}

	/* Add the terminating null byte */
	*ptr = '\0';

	return (dest);
}
