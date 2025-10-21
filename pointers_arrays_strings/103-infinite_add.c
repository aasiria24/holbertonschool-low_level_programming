#include "main.h"

/**
 * infinite_add - Adds two numbers represented as strings
 * @n1: First number string
 * @n2: Second number string
 * @r: Buffer to store the result
 * @size_r: Size of the buffer
 *
 * Return: Pointer to result or 0 if result can't be stored in r
 */
char *infinite_add(char *n1, char *n2, char *r, int size_r)
{
	int len1 = 0, len2 = 0, carry = 0, k = 0;
	int i, j, sum;

	while (n1[len1])
		len1++;
	while (n2[len2])
		len2++;

	if (len1 > size_r - 2 || len2 > size_r - 2)
		return (0);

	i = len1 - 1;
	j = len2 - 1;

	while (i >= 0 || j >= 0 || carry)
	{
		if (k >= size_r - 1)
			return (0);

		sum = carry;

		if (i >= 0)
			sum += n1[i--] - '0';
		if (j >= 0)
			sum += n2[j--] - '0';

		carry = sum / 10;
		r[k++] = (sum % 10) + '0';
	}

	r[k] = '\0';

	reverse_string(r, k);

	return (r);
}

/**
 * reverse_string - Reverses a string in place
 * @str: The string to reverse
 * @len: The length of the string
 *
 * Return: void
 */
void reverse_string(char *str, int len)
{
	int i, j;
	char temp;

	for (i = 0, j = len - 1; i < j; i++, j--)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}
