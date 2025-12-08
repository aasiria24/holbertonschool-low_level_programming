#include "hash_tables.h"

/**
* hash_table_get - Retrieves a value associated with a key
* @ht: The hash table to look into
* @key: The key you are looking for
*
* Return: The value associated with the element, or NULL if key not found
*/
char *hash_table_get(const hash_table_t *ht, const char *key)
{
hash_node_t *node;
unsigned long int index;

/* Check if hash table or key are NULL */
if (ht == NULL || key == NULL || *key == '\0')
return (NULL);

/* Get the index for the key */
index = key_index((const unsigned char *)key, ht->size);

/* Traverse the linked list at the index */
node = ht->array[index];
while (node != NULL)
{
/* Check if the current node's key matches */
if (strcmp(node->key, key) == 0)
return (node->value);
node = node->next;
}

/* Key not found */
return (NULL);
}
