#include "main.h"

/**
 * puts_half - Prints the second half of a string
 * @str: Pointer to the string
 *
 * Return: void
 */
void puts_half(char *str)
{
	int length = 0;
	int i, start;

	/* Calculate the length of the string */
	while (str[length] != '\0')
	{
		length++;
	}

	/* Determine the starting point */
	if (length % 2 == 0)
	{
		/* Even length: start from the middle */
		start = length / 2;
	}
	else
	{
		/* Odd length: start from (length + 1) / 2 */
		start = (length + 1) / 2;
	}

	/* Print from the starting point to the end */
	for (i = start; i < length; i++)
	{
		_putchar(str[i]);
	}
	_putchar('\n');
}
