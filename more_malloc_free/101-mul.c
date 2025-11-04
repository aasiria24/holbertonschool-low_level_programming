#include "main.h"
#include <stdlib.h>

/**
 * is_digit - checks if a string contains only digits
 * @s: the string to check
 *
 * Return: 1 if all characters are digits, 0 otherwise
 */
int is_digit(char *s)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * _strlen - calculates the length of a string
 * @s: the string to measure
 *
 * Return: length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

/**
 * print_error - prints "Error" and exits with status 98
 */
void print_error(void)
{
	_putchar('E');
	_putchar('r');
	_putchar('r');
	_putchar('o');
	_putchar('r');
	_putchar('\n');
	exit(98);
}

/**
 * multiply_strings - multiplies two large numbers represented as strings
 * @num1: first number string
 * @num2: second number string
 */
void multiply_strings(char *num1, char *num2)
{
	int len1, len2, total_len, i, j, carry, n1, n2, sum;
	int *result;

	len1 = _strlen(num1);
	len2 = _strlen(num2);
	total_len = len1 + len2;

	/* Allocate result array initialized to zeros */
	result = malloc(sizeof(int) * total_len);
	if (result == NULL)
	{
		print_error();
		return; /* This won't be reached due to exit in print_error, but for clarity */
	}

	for (i = 0; i < total_len; i++)
		result[i] = 0;

	/* Multiply each digit and sum at appropriate positions */
	for (i = len1 - 1; i >= 0; i--)
	{
		carry = 0;
		n1 = num1[i] - '0';

		for (j = len2 - 1; j >= 0; j--)
		{
			n2 = num2[j] - '0';
			sum = n1 * n2 + result[i + j + 1] + carry;
			carry = sum / 10;
			result[i + j + 1] = sum % 10;
		}

		if (carry > 0)
			result[i + j + 1] += carry;
	}

	/* Find the first non-zero digit */
	i = 0;
	while (i < total_len && result[i] == 0)
		i++;

	/* Print the result */
	if (i == total_len)
	{
		_putchar('0');
	}
	else
	{
		for (; i < total_len; i++)
			_putchar(result[i] + '0');
	}
	_putchar('\n');

	free(result);
}

/**
 * main - entry point for multiplication program
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 98 on error
 */
int main(int argc, char *argv[])
{
	char *num1, *num2;

	if (argc != 3)
		print_error();

	num1 = argv[1];
	num2 = argv[2];

	/* Validate that both arguments contain only digits */
	if (!is_digit(num1) || !is_digit(num2))
		print_error();

	/* Handle special case where one number is zero */
	if ((_strlen(num1) == 1 && num1[0] == '0') || 
	    (_strlen(num2) == 1 && num2[0] == '0'))
	{
		_putchar('0');
		_putchar('\n');
		return (0);
	}

	multiply_strings(num1, num2);
	return (0);
}
