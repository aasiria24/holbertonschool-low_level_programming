#include "lists.h"

/**
* free_list - frees a list_t list
* @head: pointer to the head of the list
*
* Description: Frees all nodes of a linked list, including the strings
*/
void free_list(list_t *head)
{
list_t *current;
list_t *next_node;

current = head;

while (current != NULL)
{
next_node = current->next;

/* Free the string if it exists */
if (current->str != NULL)
free(current->str);

/* Free the node itself */
free(current);

current = next_node;
}
}
