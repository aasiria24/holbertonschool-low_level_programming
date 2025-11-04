#include "main.h"
#include <stdlib.h>

/**
 * array_range - creates an array of integers from min to max
 * @min: starting value (inclusive)
 * @max: ending value (inclusive)
 *
 * Return: pointer to the newly created array
 *         NULL if min > max or if malloc fails
 */
int *array_range(int min, int max)
{
	int *arr;
	int size, i;

	/* Check if min > max */
	if (min > max)
		return (NULL);

	/* Calculate size of array */
	size = max - min + 1;

	/* Allocate memory for the array */
	arr = malloc(sizeof(int) * size);
	if (arr == NULL)
		return (NULL);

	/* Fill array with values from min to max */
	for (i = 0; i < size; i++)
		arr[i] = min + i;

	return (arr);
}
