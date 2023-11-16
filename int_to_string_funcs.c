#include <stlib.h>

unsigned int _abs(int);
char *_get_int(int num);
int _get_numbase_len(unsigned int num, unsigned int base);
void _fill_numbase_buff(unsigned int num, unsigned int base,
		char *buff, int buff_size);

/**
 * _abs - Gets the absolute value of an integer
 * @i: integer to get absolute value of
 *
 * Return: unsigned integer abs rep of i
 */

unsigned int _abs(int i)
{
	if (i < 0)
		return (-(unsigned int)i);
	return ((unsigned int)i);
}

/**
 * _get_int - Gets a character pointer to new string containing int
 * @num: number to convert to string
 *
 * Return: character pointer to newly created string. NULL if malloc fails.
 */

char *_get_int(int num)
{
	char *retr;
	long num_l = 0;
	int length = 0;
	unsigned int temp;

	temp = _abs(num);
	length = _get_numbase_len(temp, 10);

	if (num < 0 || num_l < 0)
		length++;
	retr = malloc(length + 1);
	if (!retr)
		return (NULL);

	_fill_numbase_buff(temp, 10, retr, length);
	if (num < 0 || num_l < 0)
		retr[0] = '-';

	return (retr);
}

/**
 * _get_numbase_len - Gets length of buffer needed for an unsigned int
 * @num: number to get length needed for
 * @base: base of number representation used by buffer
 *
 * Return: integer containing length of buffer needed (doesn't contain null bt)
 */

int _get_numbase_len(unsigned int num, unsigned int base)
{
	int length = 1;

	while (num > base - 1)
	{
		length++;
		num /= base;
	}
	return (length);
}

/**
 * _fill_numbase_buff - Fills buffer with correct numbers up to base 36
 * @num: number to convert to string given base
 * @base: base of number used in conversion, only works up to base 36
 * @buff: buffer to fill with result of conversion
 * @buff_size: size of buffer in bytes
 *
 * Return: always void.
 */

void _fill_numbase_buff(unsigned int num, unsigned int base,
			char *buff, int buff_size)
{
	int rem, idx = buff_size - 1;

	buff[buff_size] = '\0';
	while (idx >= 0)
	{
		rem = num % base;
		if (rem > 9)
			buff[idx] = rem + 87;
		else
			buff[idx] = rem + '0';
		num /= base;
		i--;
	}
}
