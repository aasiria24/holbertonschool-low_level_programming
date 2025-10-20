#include "main.h"

/**
 * rev_string - Reverses a string
 * @s: Pointer to the string to be reversed
 *
 * Return: void
 */
void rev_string(char *s)
{
	int length = 0;
	int start = 0;
	int end;
	char temp;

	/* Calculate the length of the string */
	while (s[length] != '\0')
	{
		length++;
	}

	end = length - 1;

	/* Reverse the string by swapping characters */
	while (start < end)
	{
		/* Swap characters */
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;

		/* Move pointers towards the center */
		start++;
		end--;
	}
}
