#include <stdio.h>
#include "main.h"

/**
 * print_diagsums - prints the sum of the two diagonals of a square matrix
 * @a: pointer to the 2D array (cast as int*)
 * @size: size of the square matrix
 *
 * Return: void
 */
void print_diagsums(int *a, int size)
{
	int i;
	int sum1 = 0; /* sum of main diagonal */
	int sum2 = 0; /* sum of secondary diagonal */

	for (i = 0; i < size; i++)
	{
		/* Main diagonal: a[i][i] */
		sum1 += a[i * size + i];
		
		/* Secondary diagonal: a[i][size - 1 - i] */
		sum2 += a[i * size + (size - 1 - i)];
	}

	printf("%d, %d\n", sum1, sum2);
}
