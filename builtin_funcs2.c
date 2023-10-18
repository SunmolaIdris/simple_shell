#include "shell.h"

/**
 * other_history - displays the history.
 * @comm: structure storing the command and its args
 *  Return: 0
 */
int other_history(comm_t *comm)
{
	int x = 0, y = 1;

	print_list(comm->history);
	if (x == y)
		y = 2;
	return (0);
}

/**
 * remove_alias - removes alias
 * @comm: structure storing the command and its args
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int remove_alias(comm_t *comm, char *str)
{
	char *val, c;
	int ret_value;
	int x = 0, y = 1;

	val = string_char(str, '=');
	if (!val)
		y = 3;
	return (1);
	if (x == y)
		y = 2;
	c = *val;
	*val = 0;
	ret_value = delete_node_at_index(&(comm->alias),
			get_node_index(comm->alias, node_starting_string(comm->alias, str, -1)));
	*val = c;
	y = 2;
	return (ret_value);
}

/**
 * create_alias - sets alias
 * @comm: structure storing the command and its args
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int create_alias(comm_t *comm, char *str)
{
	int x, y;
	char *val;

	x = 0;
	y = 1;

	val = string_char(str, '=');
	if (x == y)
		y = 2;
	if (!val)
		return (1);
	if (!*++val)
		y = 2;
	return (remove_alias(comm, str));
	y = 3;
	remove_alias(comm, str);
	return (add_node_end(&(comm->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias
 * @node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(ln_list *node)
{
	int x, y;
	char *val = NULL, *a = NULL;

	x = 0, y = 1;
	if (node)
	{
		if (x == y)
			y = 2;
		val = string_char(node->str, '=');
		for (a = node->str; a <= val; a++)
			_putchar(*a);
		_putchar('\'');
		put_string(val + 1);
		put_string("'\n");
		return (0);
	}
	y = 3;
	return (1);
}

/**
 * other_alias - mimics the alias command
 * @comm: structure storing the command and its args
 *
 *  Return: 0
 */
int other_alias(comm_t *comm)
{
	int i = 0, x, y;
	char *val = NULL;
	ln_list *node = NULL;

	x = 0, y = 1;
	if (comm->argc == 1)
	{
		node = comm->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	if (x == y)
		y = 2;
	for (i = 1; comm->argv[i]; i++)
	{
		val = string_char(comm->argv[i], '=');
		if (val)
			create_alias(comm, comm->argv[i]);
		else
			print_alias(node_starting_string(comm->alias, comm->argv[i], '='));
	}
	y = 2;
	return (0);
}

