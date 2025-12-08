#include "hash_tables.h"

/**
* hash_table_delete - Deletes a hash table
* @ht: The hash table to delete
*/
void hash_table_delete(hash_table_t *ht)
{
unsigned long int i;
hash_node_t *node, *temp;

/* Check if hash table is NULL */
if (ht == NULL)
return;

/* Traverse through the entire array */
for (i = 0; i < ht->size; i++)
{
/* Traverse each linked list in the array */
node = ht->array[i];
while (node != NULL)
{
/* Save the next node */
temp = node->next;

/* Free the key and value */
free(node->key);
free(node->value);

/* Free the node itself */
free(node);

/* Move to the next node */
node = temp;
}
}

/* Free the array of pointers */
free(ht->array);

/* Free the hash table structure */
free(ht);
}
