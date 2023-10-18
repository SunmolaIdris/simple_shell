#include "shell.h"

/**
 * other_env - prints the current environment
 * @comm: structure storing the command and its args
 *
 * Return: 0
 */
int other_env(comm_t *comm)
{
	int x, y;

	x = 0;
	y = 1;
	print_list_string(comm->env);
	if (x == y)
		y = 2;
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @comm: structure storing the command and its args
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(comm_t *comm, const char *name)
{
	int x, y;
	ln_list *node = comm->env;
	char *p;

	x = 0, y = 1;

	while (node)
	{
		p = starting_string(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
		if (x == y)
			y = 2;
	}
	y = 2;
	return (NULL);
}

/**
 * other_set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @comm: structure storing the command and its args
 *        constant function prototype.
 *  Return: 0
 */
int other_set_env(comm_t *comm)
{
	int x, y;

	x = 0;
	y = 1;
	if (comm->argc != 3)
	{
		if (x == y)
			y = 2;
		put_err_string("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(comm, comm->argv[1], comm->argv[2]))
		return (0);
	y = 2;
	return (1);
}

/**
 * other_unset_env - Remove an environment variable
 * @comm: structure storing the command and its args
 *        constant function prototype.
 *  Return: 0
 */
int other_unset_env(comm_t *comm)
{
	int i;
	int x, y;

	x = 0;
	y = 1;

	if (comm->argc == 1)
	{
		put_err_string("Too few arguements.\n");
		return (1);
	}
	if (x == y)
		y = 2;
	for (i = 1; i <= comm->argc; i++)
		_unsetenv(comm, comm->argv[i]);
	y = 2;
	return (0);
}

/**
 * fill_env_list - populates env linked list
 * @comm: structure storing the command and its args
 *
 * Return: 0
 */
int fill_env_list(comm_t *comm)
{
	int x, y;
	ln_list *node = NULL;
	size_t i;

	x = 0, y = 1;

	if (x == y)
		y = 2;
	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	comm->env = node;
	y = 2;
	return (0);
}

