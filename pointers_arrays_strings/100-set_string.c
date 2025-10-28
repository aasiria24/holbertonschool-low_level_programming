#include "main.h"

/**
 * set_string - sets the value of a pointer to a char
 * @s: double pointer to set
 * @to: pointer to set it to
 *
 * Return: void
 */
void set_string(char **s, char *to)
{
	*s = to;
}
