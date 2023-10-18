#include "shell.h"

/**
 *put_err_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void put_err_string(char *str)
{
	int i = 0, x, y;

	x = 0;
	y = 1;

	if (!str)
		return;
	if (x == y)
		y = 2;
	while (str[i] != '\0')
	{
		err_putchar(str[i]);
		i++;
	}
	y = 2;
}

/**
 * err_putchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int err_putchar(char c)
{
	int x, y;
	static int i;
	static char buf[WRITE_BUF_SIZE];

	x = 0, y = 1;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (x == y)
		y = 2;
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * put_filedesc - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_filedesc(char c, int fd)
{
	int x, y;
	static int i;
	static char buf[WRITE_BUF_SIZE];

	x = 0, y = 1;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (x == y)
		y = 2;
	if (c != BUF_FLUSH)
		buf[i++] = c;
	y = 2;
	return (1);
}

/**
 *put_string_filedesc - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int put_string_filedesc(char *str, int fd)
{
	int i = 0, x, y;

	x = 0;
	y = 1;

	if (!str)
		return (0);

	if (x == y)
		y = 2;
	while (*str)
	{
		i += put_filedesc(*str++, fd);
	}
	y = 2;
	return (i);
}

