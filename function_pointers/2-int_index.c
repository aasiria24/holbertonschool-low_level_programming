#include "function_pointers.h"

/**
 * int_index - searches for an integer in an array
 * @array: array to search in
 * @size: number of elements in the array
 * @cmp: pointer to the function used to compare values
 *
 * Return: index of first element where cmp doesn't return 0,
 *         -1 if no element matches or size <= 0
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	if (array == NULL || cmp == NULL || size <= 0)
		return (-1);

	for (i = 0; i < size; i++)
	{
		if (cmp(array[i]) != 0)
			return (i);
	}

	return (-1);
}
