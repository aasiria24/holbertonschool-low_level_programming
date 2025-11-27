#include "lists.h"

/**
* insert_dnodeint_at_index - inserts a new node at a given position
* @h: double pointer to the head of the list
* @idx: index where the new node should be added (starting at 0)
* @n: integer to be added to the new node
*
* Return: address of the new node, or NULL if it failed
*/
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
dlistint_t *new_node, *current;
unsigned int i;

if (h == NULL)
return (NULL);

/* If inserting at the beginning */
if (idx == 0)
return (add_dnodeint(h, n));

current = *h;

/* Traverse to the node before the desired index */
for (i = 0; current != NULL && i < idx - 1; i++)
current = current->next;

/* If we reached the end and idx is exactly one beyond, add at end */
if (current != NULL && current->next == NULL && i == idx - 1)
return (add_dnodeint_end(h, n));

/* If current is NULL, index is out of bounds */
if (current == NULL)
return (NULL);

/* Create new node */
new_node = malloc(sizeof(dlistint_t));
if (new_node == NULL)
return (NULL);

/* Initialize new node */
new_node->n = n;
new_node->prev = current;
new_node->next = current->next;

/* Update the next node's previous pointer */
if (current->next != NULL)
current->next->prev = new_node;

/* Update current node's next pointer */
current->next = new_node;

return (new_node);
}
