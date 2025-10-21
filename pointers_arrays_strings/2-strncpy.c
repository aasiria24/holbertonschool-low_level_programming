#include "main.h"

/**
 * _strncpy - Copies a string up to n bytes
 * @dest: The destination buffer
 * @src: The source string
 * @n: Maximum number of bytes to copy
 *
 * Return: Pointer to the resulting string dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	/* Copy up to n bytes from src to dest */
	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	/* If n is greater than the length of src, pad with null bytes */
	for (; i < n; i++)
	{
		dest[i] = '\0';
	}

	return (dest);
}
