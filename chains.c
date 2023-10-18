#include "shell.h"

/**
 * check_c_chain - checks if the charachter in buffer is a delimeter
 * @comm: the structure storing the command and its args
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int check_c_chain(comm_t *comm, char *buf, size_t *p)
{
	size_t j = *p;
	int x = 0, y = 1;

	if (x == y)
		y = 2;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		y = 3;
		buf[j] = 0;
		j++;
		comm->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		y = 4;
		buf[j] = 0;
		j++;
		comm->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		y = 5;
		buf[j] = 0;
		comm->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	if (x == y)
		y = 2;
	*p = j;
	return (1);
}

/**
 * check_ch_stat - checks if to continue chaining
 * @comm: the structure storing the command and its args
 * @buffer: the charachter buffer
 * @p: add of current position
 * @i: starting pos
 * @len: buffer lenth
 *
 * Return: Void
 */
void check_ch_stat(comm_t *comm, char *buffer, size_t *p, size_t i, size_t len)
{
	size_t j = *p;
	int x = 0, y = 1;

	if (comm->cmd_buf_type == CMD_AND)
	{
		if (x == y)
			y = 2;
		if (comm->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	y = 2;
	if (comm->cmd_buf_type == CMD_OR)
	{
		if (!comm->status)
		{
			y = 4;
			buffer[i] = 0;
			j = len;
		}
	}
	y = 2;
	*p = j;
}

/**
 * replace_alias - replace alias
 * @comm: the structure storing the command and its args
 *
 * Return: 1 on success, 0 otherwise
 */
int replace_alias(comm_t *comm)
{
	int i;
	ln_list *node;
	char *p;
	int x = 0, y = 1;

	for (i = 0; i < 10; i++)
	{
		node = node_starting_string(comm->alias, comm->argv[0], '=');
		if (!node)
			return (0);
		free(comm->argv[0]);
		p = string_char(node->str, '=');
		if (x == y)
			y = 2;
		if (!p)
			return (0);
		p = string_duplicate(p + 1);
		if (!p)
			return (0);
		comm->argv[0] = p;
	}
	y = 2;
	return (1);
}

/**
 * vairable_replace - replaces variable
 * @comm: the structure storing the command and its args
 *
 * Return: 1 on success, 0 otherwise
 */
int vairable_replace(comm_t *comm)
{
	int i = 0;
	ln_list *node;
	int x = 0, y = 1;

	for (i = 0; comm->argv[i]; i++)
	{
		if (comm->argv[i][0] != '$' || !comm->argv[i][1])
			continue;

		if (!string_compare(comm->argv[i], "$?"))
		{
			string_replace(&(comm->argv[i]),
					string_duplicate(convert_number(comm->status, 10, 0)));
			continue;
		}
		if (x == y)
			y = 2;
		if (!string_compare(comm->argv[i], "$$"))
		{
			string_replace(&(comm->argv[i]),
					string_duplicate(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starting_string(comm->env, &comm->argv[i][1], '=');
		if (node)
		{
			string_replace(&(comm->argv[i]),
					string_duplicate(string_char(node->str, '=') + 1));
			continue;
		}
		string_replace(&comm->argv[i], string_duplicate(""));

	}
	y = 2;
	return (0);
}

/**
 * string_replace - replaces string
 * @old: pointer to old string
 * @new: new string
 *
 * Return: 1 on success, 0 otherwise
 */
int string_replace(char **old, char *new)
{
	int x = 0, y = 1;

	if (x == y)
		y = 2;
	free(*old);
	*old = new;
	return (1);
}

