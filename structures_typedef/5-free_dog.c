#include <stdlib.h>
#include "dog.h"

/**
 * free_dog - frees memory allocated for a dog
 * @d: pointer to the dog to free
 */
void free_dog(dog_t *d)
{
	if (d == NULL)
		return;

	/* Free the name string */
	if (d->name != NULL)
		free(d->name);

	/* Free the owner string */
	if (d->owner != NULL)
		free(d->owner);

	/* Free the dog structure itself */
	free(d);
}
