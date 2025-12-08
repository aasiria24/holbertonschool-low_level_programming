#include "hash_tables.h"

/**
* hash_table_print - Prints a hash table
* @ht: The hash table to print
*
* Description: Prints the key/value pairs in the order they appear
*              in the array of the hash table
*/
void hash_table_print(const hash_table_t *ht)
{
unsigned long int i;
hash_node_t *node;
int first = 1;

/* Check if hash table is NULL */
if (ht == NULL)
return;

/* Start printing */
printf("{");

/* Traverse through the entire array */
for (i = 0; i < ht->size; i++)
{
/* Traverse each linked list in the array */
node = ht->array[i];
while (node != NULL)
{
/* Print comma and space if not the first element */
if (!first)
printf(", ");

/* Print key/value pair */
printf("'%s': '%s'", node->key, node->value);
first = 0;

/* Move to next node in the linked list */
node = node->next;
}
}

/* End printing */
printf("}\n");
}
