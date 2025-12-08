#include "hash_tables.h"

/**
* key_index - Get the index at which a key/value pair should
*             be stored in array of a hash table.
* @key: The key to get the index of.
* @size: The size of the array of the hash table.
*
* Return: The index of the key.
*
* Description: Uses the djb2 algorithm.
*/
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
unsigned long int hash_value;

/* Calculate the hash value using djb2 algorithm */
hash_value = hash_djb2(key);

/* Return the index by taking modulo with size */
return (hash_value % size);
}
