#include "main.h"
#include <stdio.h>
#include <ctype.h>

/**
 * print_buffer - Prints a buffer in a specific format
 * @b: The buffer to print
 * @size: The size of the buffer
 *
 * Return: void
 */
void print_buffer(char *b, int size)
{
	int i, j;

	if (size <= 0)
	{
		printf("\n");
		return;
	}

	for (i = 0; i < size; i += 10)
	{
		/* Print the position in hexadecimal */
		printf("%08x: ", i);

		/* Print the hexadecimal content */
		for (j = 0; j < 10; j++)
		{
			if (i + j < size)
				printf("%02x", (unsigned char)b[i + j]);
			else
				printf("  ");

			if (j % 2 == 1 && j < 9)
				printf(" ");
		}

		printf(" ");

		/* Print the ASCII content */
		for (j = 0; j < 10; j++)
		{
			if (i + j >= size)
				break;

			if (isprint((unsigned char)b[i + j]))
				printf("%c", b[i + j]);
			else
				printf(".");
		}
		printf("\n");
	}
}
