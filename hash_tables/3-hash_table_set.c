#include "hash_tables.h"
#include <string.h>
/**
* hash_table_set - Adds an element to the hash table
* @ht: The hash table to add or update the key/value to
* @key: The key (cannot be an empty string)
* @value: The value associated with the key (must be duplicated)
*
* Return: 1 if succeeded, 0 otherwise
*/
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
hash_node_t *new_node, *temp;
unsigned long int index;
char *value_copy;

/* Check if hash table, key, or value are NULL */
if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
return (0);

/* Create a copy of the value */
value_copy = strdup(value);
if (value_copy == NULL)
return (0);

/* Get the index for the key */
index = key_index((const unsigned char *)key, ht->size);

/* Check if key already exists in the chain */
temp = ht->array[index];
while (temp != NULL)
{
if (strcmp(temp->key, key) == 0)
{
/* Key found, update the value */
free(temp->value);
temp->value = value_copy;
return (1);
}
temp = temp->next;
}

/* Key doesn't exist, create a new node */
new_node = malloc(sizeof(hash_node_t));
if (new_node == NULL)
{
free(value_copy);
return (0);
}

/* Duplicate the key */
new_node->key = strdup(key);
if (new_node->key == NULL)
{
free(value_copy);
free(new_node);
return (0);
}

/* Set the node values */
new_node->value = value_copy;

/* Add the new node at the beginning of the list */
new_node->next = ht->array[index];
ht->array[index] = new_node;

return (1);
}
/* Set the node values */
new_node->value = value_copy;

/* Add the new node at the beginning of the list */
new_node->next = ht->array[index];
ht->array[index] = new_node;

return (1);
}
