#include "main.h"

/**
 * cap_string - Capitalizes all words of a string
 * @str: The string to capitalize
 *
 * Return: Pointer to the capitalized string
 */
char *cap_string(char *str)
{
	int i = 0;
	int new_word = 1; /* Flag to indicate start of new word */

	while (str[i] != '\0')
	{
		/* Check if current character is a word separator */
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
		    str[i] == ',' || str[i] == ';' || str[i] == '.' ||
		    str[i] == '!' || str[i] == '?' || str[i] == '"' ||
		    str[i] == '(' || str[i] == ')' || str[i] == '{' ||
		    str[i] == '}')
		{
			new_word = 1;
		}
		/* If it's a lowercase letter and start of new word, capitalize it */
		else if (new_word && str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] - 32;
			new_word = 0;
		}
		/* If it's not a separator, reset new_word flag */
		else
		{
			new_word = 0;
		}
		i++;
	}

	return (str);
}
