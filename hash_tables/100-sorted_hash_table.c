#include "hash_tables.h"

/**
* shash_table_create - Creates a sorted hash table
* @size: The size of the array
*
* Return: A pointer to the newly created sorted hash table, or NULL if failure
*/
shash_table_t *shash_table_create(unsigned long int size)
{
shash_table_t *new_table;
unsigned long int i;

/* Allocate memory for the hash table structure */
new_table = malloc(sizeof(shash_table_t));
if (new_table == NULL)
return (NULL);

/* Allocate memory for the array of pointers */
new_table->array = malloc(sizeof(shash_node_t *) * size);
if (new_table->array == NULL)
{
free(new_table);
return (NULL);
}

/* Initialize all array elements to NULL */
for (i = 0; i < size; i++)
new_table->array[i] = NULL;

/* Set the size of the hash table */
new_table->size = size;

/* Initialize sorted list pointers */
new_table->shead = NULL;
new_table->stail = NULL;

return (new_table);
}

/**
* sorted_list_insert - Inserts a node into the sorted linked list
* @ht: The sorted hash table
* @node: The node to insert
*/
void sorted_list_insert(shash_table_t *ht, shash_node_t *node)
{
shash_node_t *current;

/* If the sorted list is empty */
if (ht->shead == NULL)
{
ht->shead = node;
ht->stail = node;
node->sprev = NULL;
node->snext = NULL;
return;
}

/* If node should be inserted at the beginning */
if (strcmp(node->key, ht->shead->key) < 0)
{
node->sprev = NULL;
node->snext = ht->shead;
ht->shead->sprev = node;
ht->shead = node;
return;
}

/* Find the correct position in the sorted list */
current = ht->shead;
while (current->snext != NULL && strcmp(node->key, current->snext->key) > 0)
current = current->snext;

/* Insert node after current */
node->sprev = current;
node->snext = current->snext;

if (current->snext != NULL)
current->snext->sprev = node;
else
ht->stail = node; /* Inserting at the end */

current->snext = node;
}

/**
* create_new_shash_node - Creates a new sorted hash node
* @key: The key
* @value: The value
*
* Return: Pointer to new node or NULL
*/
shash_node_t *create_new_shash_node(const char *key, const char *value)
{
shash_node_t *node;
char *key_copy, *value_copy;

/* Allocate memory for the node */
node = malloc(sizeof(shash_node_t));
if (node == NULL)
return (NULL);

/* Duplicate the key */
key_copy = strdup(key);
if (key_copy == NULL)
{
free(node);
return (NULL);
}

/* Duplicate the value */
value_copy = strdup(value);
if (value_copy == NULL)
{
free(key_copy);
free(node);
return (NULL);
}

/* Initialize the node */
node->key = key_copy;
node->value = value_copy;
node->next = NULL;
node->sprev = NULL;
node->snext = NULL;

return (node);
}

/**
* update_existing_node - Updates an existing node's value
* @node: The node to update
* @value: The new value
*
* Return: 1 on success, 0 on failure
*/
int update_existing_node(shash_node_t *node, const char *value)
{
char *value_copy;

/* Create a copy of the new value */
value_copy = strdup(value);
if (value_copy == NULL)
return (0);

/* Free old value and assign new one */
free(node->value);
node->value = value_copy;
return (1);
}

/**
* shash_table_set - Adds an element to the sorted hash table
* @ht: The sorted hash table to add or update the key/value to
* @key: The key (cannot be an empty string)
* @value: The value associated with the key (must be duplicated)
*
* Return: 1 if succeeded, 0 otherwise
*/
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
shash_node_t *new_node, *temp;
unsigned long int index;

/* Check if hash table, key, or value are NULL */
if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
return (0);

/* Get the index for the key */
index = key_index((const unsigned char *)key, ht->size);

/* Check if key already exists in the chain */
temp = ht->array[index];
while (temp != NULL)
{
if (strcmp(temp->key, key) == 0)
return (update_existing_node(temp, value));
temp = temp->next;
}

/* Key doesn't exist, create a new node */
new_node = create_new_shash_node(key, value);
if (new_node == NULL)
return (0);

/* Add the new node to the collision chain (at the beginning) */
new_node->next = ht->array[index];
ht->array[index] = new_node;

/* Insert the new node into the sorted linked list */
sorted_list_insert(ht, new_node);

return (1);
}

/**
* shash_table_get - Retrieves a value associated with a key
* @ht: The sorted hash table to look into
* @key: The key you are looking for
*
* Return: The value associated with the element, or NULL if key not found
*/
char *shash_table_get(const shash_table_t *ht, const char *key)
{
shash_node_t *node;
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

/**
* shash_table_print - Prints a sorted hash table
* @ht: The sorted hash table to print
*
* Description: Prints the key/value pairs in the sorted order
*/
void shash_table_print(const shash_table_t *ht)
{
shash_node_t *node;
int first = 1;

/* Check if hash table is NULL */
if (ht == NULL)
return;

/* Start printing */
printf("{");

/* Traverse through the sorted linked list */
node = ht->shead;
while (node != NULL)
{
/* Print comma and space if not the first element */
if (!first)
printf(", ");

/* Print key/value pair */
printf("'%s': '%s'", node->key, node->value);
first = 0;

/* Move to next node in the sorted list */
node = node->snext;
}

/* End printing */
printf("}\n");
}

/**
* shash_table_print_rev - Prints a sorted hash table in reverse order
* @ht: The sorted hash table to print
*
* Description: Prints the key/value pairs in reverse sorted order
*/
void shash_table_print_rev(const shash_table_t *ht)
{
shash_node_t *node;
int first = 1;

/* Check if hash table is NULL */
if (ht == NULL)
return;

/* Start printing */
printf("{");

/* Traverse through the sorted linked list in reverse */
node = ht->stail;
while (node != NULL)
{
/* Print comma and space if not the first element */
if (!first)
printf(", ");

/* Print key/value pair */
printf("'%s': '%s'", node->key, node->value);
first = 0;

/* Move to previous node in the sorted list */
node = node->sprev;
}

/* End printing */
printf("}\n");
}

/**
* sorted_list_remove - Removes a node from the sorted linked list
* @ht: The sorted hash table
* @node: The node to remove
*/
void sorted_list_remove(shash_table_t *ht, shash_node_t *node)
{
/* Update previous node's next pointer */
if (node->sprev != NULL)
node->sprev->snext = node->snext;
else
ht->shead = node->snext; /* Node was the head */

/* Update next node's previous pointer */
if (node->snext != NULL)
node->snext->sprev = node->sprev;
else
ht->stail = node->sprev; /* Node was the tail */
}

/**
* free_shash_node - Frees a sorted hash node
* @node: The node to free
*/
void free_shash_node(shash_node_t *node)
{
/* Free the key and value */
free(node->key);
free(node->value);

/* Free the node itself */
free(node);
}

/**
* shash_table_delete - Deletes a sorted hash table
* @ht: The sorted hash table to delete
*/
void shash_table_delete(shash_table_t *ht)
{
unsigned long int i;
shash_node_t *node, *temp;

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

/* Remove node from sorted list */
sorted_list_remove(ht, node);

/* Free the node */
free_shash_node(node);

/* Move to the next node */
node = temp;
}
}

/* Free the array of pointers */
free(ht->array);

/* Free the hash table structure */
free(ht);
}
