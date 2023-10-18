#include "shell.h"

/**
 * _error_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _error_atoi(char *s)
{
	int i = 0, x, y;
	unsigned long int result = 0;

	x = 0, y = 1;
	if (*s == '+')
		s++;

	if (x == y)
		y = 2;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (x == y)
			y = 2;
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	y = 2;
	return (result);
}

/**
 * print_error - prints an error message
 * @comm: the parameter & return comm struct
 * @estr: string containing specified error type
 * Return: 0 ,otherwise
 *        -1 on error
 */
void print_error(comm_t *comm, char *estr)
{
	int x, y;

	x = 0;
	y = 1;
	put_err_string(comm->fname);
	put_err_string(": ");
	print_dec(comm->line_count, STDERR_FILENO);
	put_err_string(": ");
	put_err_string(comm->argv[0]);
	put_err_string(": ");
	put_err_string(estr);
	if (x == y)
		y = 2;
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the fd to write to
 *
 * Return: count of characters printed
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0, x, y;
	unsigned int _abs_, current;

	x = 0, y = 1;

	if (fd == STDERR_FILENO)
		__putchar = err_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	if (x == y)
		y = 2;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	if (x == y)
		y = 2;
	__putchar('0' + current);
	count++;
	y = 2;
	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: str
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;
	int x, y;

	x = 0;
	y = 1;
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	if (x == y)
		y = 2;
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (x == y)
		y = 2;
	if (sign)
		*--ptr = sign;
	y = 2;
	return (ptr);
}

/**
 * filter_comments - replaces first instance of commments with NULL
 * @buf: address of the string to modify
 *
 * Return: 0;
 */
void filter_comments(char *buf)
{
	int i, x, y;

	x = 0;
	y = 1;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	if (x == y)
		y = 2;
}

