#include "main.h"
#include <stdlib.h>

/**
 * _calloc - allocates memory for an array and sets it to zero
 * @nmemb: number of elements in the array
 * @size: size of each element in bytes
 *
 * Return: pointer to the allocated memory
 *         NULL if nmemb or size is 0, or if allocation fails
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *ptr;
	unsigned int total_size;
	unsigned int i;
	char *char_ptr;

	/* Check for zero parameters */
	if (nmemb == 0 || size == 0)
		return (NULL);

	/* Calculate total memory needed */
	total_size = nmemb * size;

	/* Allocate memory */
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);

	/* Set memory to zero */
	char_ptr = (char *)ptr;
	for (i = 0; i < total_size; i++)
		char_ptr[i] = 0;

	return (ptr);
}
