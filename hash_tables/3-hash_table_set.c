#include "hash_tables.h"
#include <string.h>

/**
* hash_table_set - Adds an element to the hash table
* @ht: The hash table
* @key: The key
* @value: The value
* Return: 1 if succeeded, 0 otherwise
*/
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
hash_node_t *new_node, *temp;
unsigned long int index;
char *value_copy;

if (!ht || !key || !*key || !value)
return (0);
value_copy = strdup(value);
if (!value_copy)
return (0);
index = key_index((const unsigned char *)key, ht->size);
temp = ht->array[index];
while (temp)
{
if (strcmp(temp->key, key) == 0)
{
free(temp->value);
temp->value = value_copy;
return (1);
}
temp = temp->next;
}
new_node = malloc(sizeof(hash_node_t));
if (!new_node)
{
free(value_copy);
return (0);
}
new_node->key = strdup(key);
if (!new_node->key)
{
free(value_copy);
free(new_node);
return (0);
}
new_node->value = value_copy;
new_node->next = ht->array[index];
ht->array[index] = new_node;
return (1);
}
