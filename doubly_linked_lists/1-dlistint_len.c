#include "lists.h"
/**
* dlistint_len - returns the number of elements in a linked dlistint_t list
* @h: pointer to the head of the list
*
* Return: number of elements in the list
*/
size_t dlistint_len(const dlistint_t *h)
{
size_t count = 0;
const dlistint_t *current = h;

while (current != NULL)
{
count++;
current = current->next;
}

return (count);
}
