#include "main.h"

/**
 * _strcat - Concatenates two strings
 * @dest: The destination string
 * @src: The source string to append
 *
 * Return: Pointer to the resulting string dest
 */
char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	/* Find the end of dest */
	while (*ptr != '\0')
	{
		ptr++;
	}

	/* Copy src to the end of dest */
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	/* Add the terminating null byte */
	*ptr = '\0';

	return (dest);
}
