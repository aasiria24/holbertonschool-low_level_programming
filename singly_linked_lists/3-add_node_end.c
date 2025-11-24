#include "lists.h"

/**
* add_node_end - adds a new node at the end of a list_t list
* @head: double pointer to the head of the list
* @str: string to be duplicated and added to the new node
*
* Return: address of the new element, or NULL if it failed
*/
list_t *add_node_end(list_t **head, const char *str)
{
list_t *new_node;
list_t *last;
char *str_dup;
unsigned int len = 0;

/* Allocate memory for new node */
new_node = malloc(sizeof(list_t));
if (new_node == NULL)
return (NULL);

/* Duplicate the string */
if (str == NULL)
{
str_dup = NULL;
len = 0;
}
else
{
str_dup = strdup(str);
if (str_dup == NULL)
{
free(new_node);
return (NULL);
}

/* Calculate string length */
while (str[len])
len++;
}

/* Initialize the new node */
new_node->str = str_dup;
new_node->len = len;
new_node->next = NULL;

/* If the list is empty, make new node the head */
if (*head == NULL)
{
*head = new_node;
return (new_node);
}

/* Otherwise, traverse to the last node */
last = *head;
while (last->next != NULL)
last = last->next;

/* Change the next of the last node */
last->next = new_node;

return (new_node);
}
