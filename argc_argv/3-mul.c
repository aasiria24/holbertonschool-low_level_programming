#include <stdio.h>
#include <stdlib.h>

/**
 * main - multiplies two numbers
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char *argv[])
{
	int num1, num2, result;

	/* Check if exactly two arguments are provided */
	if (argc != 3)
	{
		printf("Error\n");
		return (1);
	}

	/* Convert arguments to integers */
	num1 = atoi(argv[1]);
	num2 = atoi(argv[2]);

	/* Multiply the numbers */
	result = num1 * num2;

	/* Print the result */
	printf("%d\n", result);

	return (0);
}
