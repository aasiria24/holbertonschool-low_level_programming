#include "main.h"

/**
 * _strcpy - Copies a string from src to dest
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	/* Copy each character until we reach the null terminator */
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	/* Copy the null terminator */
	dest[i] = '\0';

	return (dest);
}
