#include <stdio.h>

/**
 * main - prints the number of arguments passed into it
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	(void)argv; /* Unused parameter */

	printf("%d\n", argc - 1);

	return (0);
}
