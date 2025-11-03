#include "main.h"
#include <stdlib.h>

/**
* argstostr - concatenates all arguments of the program
* @ac: argument count
* @av: argument vector (array of strings)
*
* Return: pointer to new string, or NULL if it fails
*/
char *argstostr(int ac, char **av)
{
	int i, j, k = 0, total_len = 0;
	char *str;

	if (ac == 0 || av == NULL)
		return (NULL);

	for (i = 0; i < ac; i++)
	{
		j = 0;
		while (av[i][j])
		{
			total_len++;
			j++;
		}
		total_len++; /* for '\n' */
	}

	str = malloc(sizeof(char) * (total_len + 1));
	if (str == NULL)
		return (NULL);

	for (i = 0; i < ac; i++)
	{
		j = 0;
		while (av[i][j])
		{
			str[k] = av[i][j];
			j++;
			k++;
		}
		str[k] = '\n';
		k++;
	}

	str[k] = '\0';
	return (str);
}
