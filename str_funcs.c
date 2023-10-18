#include "shell.h"

/**
 * string_length - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int string_length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * string_compare - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int string_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starting_string - checks if src starts with str
 * @str: string to search
 * @src: the substring to find
 *
 * Return: address of next char of str or NULL
 */
char *starting_string(const char *str, const char *src)
{
	while (*src)
		if (*src++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * string_concat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *string_concat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
