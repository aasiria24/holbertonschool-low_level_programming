#include "main.h"
#include <stdlib.h>

/**
 * _strlen - calculates the length of a string
 * @s: the string to measure
 *
 * Return: length of the string
 */
unsigned int _strlen(char *s)
{
	unsigned int len = 0;

	if (s == NULL)
		return (0);

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * string_nconcat - concatenates two strings
 * @s1: first string
 * @s2: second string
 * @n: number of bytes from s2 to concatenate
 *
 * Return: pointer to newly allocated concatenated string
 *         NULL if allocation fails
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	unsigned int len1, len2, total_len, i, j;
	char *result;

	/* Handle NULL strings by treating them as empty strings */
	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";

	/* Get lengths of strings */
	len1 = _strlen(s1);
	len2 = _strlen(s2);

	/* If n >= length of s2, use entire s2 */
	if (n >= len2)
		n = len2;

	/* Calculate total length needed (s1 + n bytes of s2 + null terminator) */
	total_len = len1 + n + 1;

	/* Allocate memory */
	result = malloc(total_len);
	if (result == NULL)
		return (NULL);

	/* Copy s1 to result */
	for (i = 0; i < len1; i++)
		result[i] = s1[i];

	/* Copy first n bytes of s2 */
	for (j = 0; j < n; j++)
		result[i + j] = s2[j];

	/* Add null terminator */
	result[i + j] = '\0';

	return (result);
}
