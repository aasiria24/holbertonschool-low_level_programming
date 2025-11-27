#include "lists.h"

/**
* insert_dnodeint_at_index - inserts a new node at a given position
* @h: double pointer to the head of the list
* @idx: index where the new node should be added
* @n: integer to be added to the new node
*
* Return: address of the new node, or NULL if it failed
*/
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
dlistint_t *new, *temp;
unsigned int i = 0;

if (!h)
return (NULL);

if (idx == 0)
return (add_dnodeint(h, n));

temp = *h;
while (temp && i < idx - 1)
{
temp = temp->next;
i++;
}

if (!temp)
return (NULL);

if (!temp->next)
return (add_dnodeint_end(h, n));

new = malloc(sizeof(dlistint_t));
if (!new)
return (NULL);

new->n = n;
new->prev = temp;
new->next = temp->next;
temp->next->prev = new;
temp->next = new;

return (new);
}
