#include "lists.h"

/**
* delete_dnodeint_at_index - deletes the node at index of a dlistint_t list
* @head: double pointer to the head of the list
* @index: index of the node that should be deleted (starts at 0)
*
* Return: 1 if it succeeded, -1 if it failed
*/
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
dlistint_t *current;
unsigned int i = 0;

if (head == NULL || *head == NULL)
return (-1);

current = *head;

/* Case 1: Delete the first node */
if (index == 0)
{
*head = current->next;
if (*head != NULL)
(*head)->prev = NULL;
free(current);
return (1);
}

/* Traverse to the node at the given index */
while (current != NULL && i < index)
{
current = current->next;
i++;
}

/* If index is out of bounds */
if (current == NULL)
return (-1);

/* Case 2: Delete a middle or last node */
if (current->prev != NULL)
current->prev->next = current->next;

if (current->next != NULL)
current->next->prev = current->prev;

free(current);
return (1);
}
