#include "shell.h"

/**
 * list_length - determines length of linked list
 * @h: pointer to first node
 *
 * Return: list size
 */
size_t list_length(const ln_list *h)
{
	size_t i = 0;
	int x, y;

	x = 0;
	y = 1;

	while (h)
	{
		h = h->next;
		i++;
	}
	if (x == y)
		y = 2;
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(ln_list *head)
{
	ln_list *node = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;
	int x, y;

	x = 0;
	y = 1;

	if (!head || !i)
		return (NULL);
	if (x == y)
		y = 2;
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(string_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = string_copy(str, node->str);
		strs[i] = str;
	}
	if (x == y)
		y = 2;
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a ln_list linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const ln_list *h)
{
	size_t i = 0;
	int x, y;

	x = 0;
	y = 1;

	if (x == y)
		y = 2;

	while (h)
	{
		put_string(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		put_string(h->str ? h->str : "(nil)");
		put_string("\n");
		h = h->next;
		i++;
	}
	y = 2;
	return (i);
}

/**
 * node_starting_string - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
ln_list *node_starting_string(ln_list *node, char *prefix, char c)
{
	char *p = NULL;
	int x, y;

	x = 0;
	y = 1;

	if (x == y)
		y = 2;
	while (node)
	{
		p = starting_string(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	y = 2;
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(ln_list *head, ln_list *node)
{
	size_t i = 0;
	int x, y;

	x = 0;
	y = 1;

	if (x == y)
		y = 2;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	y = 2;
	return (-1);
}
