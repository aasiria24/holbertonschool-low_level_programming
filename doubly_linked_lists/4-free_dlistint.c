#include "lists.h"

/**
* free_dlistint - frees a dlistint_t list
* @head: pointer to the head of the list
*
* Description: Frees all nodes of a doubly linked list
*/
void free_dlistint(dlistint_t *head)
{
dlistint_t *current;
dlistint_t *next_node;

current = head;

while (current != NULL)
{
next_node = current->next;

/* Free the current node */
free(current);

current = next_node;
}
}
