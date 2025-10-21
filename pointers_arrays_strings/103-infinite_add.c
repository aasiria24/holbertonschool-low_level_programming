#include "main.h"

char *infinite_add(char *n1, char *n2, char *r, int size_r)
{
	int len1 = 0, len2 = 0, carry = 0;
	int i, j, k, sum;

	while (n1[len1] != '\0')
		len1++;
	while (n2[len2] != '\0')
		len2++;

	if (len1 > size_r - 2 || len2 > size_r - 2)
		return (0);

	i = len1 - 1;
	j = len2 - 1;
	k = 0;
	carry = 0;

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

	for (i = 0, j = k - 1; i < j; i++, j--)
	{
		char temp = r[i];
		r[i] = r[j];
		r[j] = temp;
	}

	return (r);
}
