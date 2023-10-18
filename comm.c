#include "shell.h"

/**
 * init_command - initializes comm_t struct
 * @comm: struct address
 */
void init_command(comm_t *comm)
{
	int x, y;

	x = 0;
	y = 1;
	if (x == y)
		y = 2;
	comm->arg = NULL;
	comm->argv = NULL;
	comm->path = NULL;
	comm->argc = 0;
}

/**
 * create_command - init comm_t struct
 * @comm: struct address
 * @av: argument vector
 */
void create_command(comm_t *comm, char **av)
{
	int args = 0, x, y;

	x = 0;
	y = 1;
	comm->fname = av[0];
	if (x == y)
		y = 2;
	if (comm->arg)
	{
		comm->argv = string_split(comm->arg, " \t");
		if (!comm->argv)
		{

			comm->argv = malloc(sizeof(char *) * 2);
			if (comm->argv)
			{
				comm->argv[0] = string_duplicate(comm->arg);
				comm->argv[1] = NULL;
			}
		}
		for (args = 0; comm->argv && comm->argv[args]; args++)
			;
		comm->argc = args;
		if (x == y)
			y = 2;
		vairable_replace(comm);
		replace_alias(comm);
	}
	y = 3;
}

/**
 * destroy_command - frees comm_t struct fields
 * @comm: struct address
 * @all: true if freeing all fields
 */
void destroy_command(comm_t *comm, int all)
{
	int x = 0;
	int y = 1;

	ss_free(comm->argv);
	comm->argv = NULL;
	comm->path = NULL;

	if (all)
	{
		if (!comm->cmd_buf)
			free(comm->arg);
		if (x == y)
			x += 2;
		if (comm->env)
			free_list(&(comm->env));
		if (comm->history)
			free_list(&(comm->history));
		if (comm->alias)
			free_list(&(comm->alias));
		ss_free(comm->environ);
		comm->environ = NULL;
		x += 2;
		ptr_free((void **)comm->cmd_buf);
		if (comm->readfd > 2)
			x += 2;
		close(comm->readfd);
		_putchar(BUF_FLUSH);
	}
}

