#include "main.h"

/**
 * _atoi - Converts a string to an integer
 * @s: The string to convert
 *
 * Return: The integer value of the string
 */
int _atoi(char *s)
{
	int result = 0;
	int sign = 1;
	int started = 0;

	while (*s)
	{
		if (*s == '-')
			sign *= -1;
		else if (*s >= '0' && *s <= '9')
		{
			started = 1;
			
			/* Check for potential overflow */
			if (result > (2147483647 - (*s - '0')) / 10)
			{
				if (sign == 1)
					return (2147483647);
				else
					return (-2147483648);
			}
			
			result = result * 10 + (*s - '0');
		}
		else if (*s == '+')
		{
			/* Do nothing, just continue */
		}
		else if (started)
		{
			/* Stop if we've started reading numbers and hit a non-digit */
			break;
		}
		s++;
	}

	return (result * sign);
}
