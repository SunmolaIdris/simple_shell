#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @comm: structure storing the command and its args
 *
 * Return: 0
 */
char **get_environ(comm_t *comm)
{
	int x, y;

	x = 0;
	y = 1;

	if (!comm->environ || comm->env_changed)
	{
		comm->environ = list_to_strings(comm->env);
		comm->env_changed = 0;
	}
	if (x == y)
		y = 2;

	return (comm->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @comm: structure storing the command and its args
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(comm_t *comm, char *var)
{
	ln_list *node = comm->env;
	size_t i = 0;
	char *p;
	int x, y;

	x = 0;
	y = 1;
	if (!node || !var)
		return (0);

	if (x == y)
		y = 2;

	while (node)
	{
		p = starting_string(node->str, var);
		if (p && *p == '=')
		{
			comm->env_changed = delete_node_at_index(&(comm->env), i);
			i = 0;
			node = comm->env;
			continue;
		}
		node = node->next;
		i++;
	}
	y = 2;
	return (comm->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @comm: structure storing the command and its args
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: 0
 */
int _setenv(comm_t *comm, char *var, char *value)
{
	char *buf = NULL;
	ln_list *node;
	char *p;
	int x, y;

	x = 0;
	y = 1;
	if (!var || !value)
		return (0);

	buf = malloc(string_length(var) + string_length(value) + 2);
	if (!buf)
		return (1);
	string_copy(buf, var);
	string_concat(buf, "=");
	string_concat(buf, value);
	node = comm->env;
	while (node)
	{
		p = starting_string(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			comm->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	if (x == y)
		y = 2;
	add_node_end(&(comm->env), buf, 0);
	free(buf);
	comm->env_changed = 1;
	y = 2;
	return (0);
}

