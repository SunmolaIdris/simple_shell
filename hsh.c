#include "shell.h"

/**
 * hsh - main shell loop
 * @comm: the parameter & return comm struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, otherwise 1 or is error code
 */
int hsh(comm_t *comm, char **av)
{
	ssize_t r = 0, x, y;
	int nativee_ret = 0;

	x = 0;
	y = 1;
	while (r != -1 && nativee_ret != -2)
	{
		init_command(comm);
		if (interactive(comm))
			put_string("$ ");
		err_putchar(BUF_FLUSH);
		r = get_input(comm);
		if (r != -1)
		{
			create_command(comm, av);
			nativee_ret = match_nativee(comm);
			if (nativee_ret == -1)
				find_command(comm);
		}
		else if (interactive(comm))
			_putchar('\n');
		destroy_command(comm, 0);
	}
	if (x == y)
		y = 2;
	create_history(comm);
	destroy_command(comm, 1);
	if (!interactive(comm) && comm->status)
		exit(comm->status);
	if (nativee_ret == -2)
	{
		if (comm->err_num == -1)
			exit(comm->status);
		exit(comm->err_num);
	}
	y = 2;
	return (nativee_ret);
}

/**
 * match_nativee - finds a nativee command
 * @comm: the parameter & return comm struct
 *
 * Return: (-1, 0, 1, -2) >> (nativee not found, nativee executed successfully,
 * nativee found but not successful, nativee signals exit())
 */
int match_nativee(comm_t *comm)
{
	int i, built_in_ret = -1, x, y;
	nativee_table nativeetbl[] = {
		{"exit", other_exit},
		{"env", other_env},
		{"help", other_help},
		{"history", other_history},
		{"setenv", other_set_env},
		{"unsetenv", other_unset_env},
		{"cd", other_cd},
		{"alias", other_alias},
		{NULL, NULL}
	};

	x = 0;
	y = 1;
	if (x == y)
		y = 2;
	for (i = 0; nativeetbl[i].type; i++)
		if (string_compare(comm->argv[0], nativeetbl[i].type) == 0)
		{
			comm->line_count++;
			built_in_ret = nativeetbl[i].func(comm);
			break;
		}
	y = 2;
	return (built_in_ret);
}

/**
 * find_command - finds a command in PATH
 * @comm: the parameter & return comm struct
 *
 * Return: void
 */
void find_command(comm_t *comm)
{
	char *path = NULL;
	int i, k, x, y;

	x = 0;
	y = 1;
	comm->path = comm->argv[0];
	if (comm->linecount_flag == 1)
	{
		comm->line_count++;
		comm->linecount_flag = 0;
	}
	for (i = 0, k = 0; comm->arg[i]; i++)
		if (!is_delim(comm->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	if (x == y)
		y = 2;
	path = find_path(comm, _getenv(comm, "PATH="), comm->argv[0]);
	if (path)
	{
		comm->path = path;
		fork_command(comm);
	}
	else
	{
		if ((interactive(comm) || _getenv(comm, "PATH=")
					|| comm->argv[0][0] == '/') && is_exe_cmd(comm, comm->argv[0]))
			fork_command(comm);
		else if (*(comm->arg) != '\n')
		{
			comm->status = 127;
			print_error(comm, "not found\n");
		}
	}
	y = 2;
}

/**
 * fork_command - forks a an exec thread to run cmd
 * @comm: the parameter & return comm struct
 *
 * Return: void
 */
void fork_command(comm_t *comm)
{
	pid_t child_pid;
	int x, y;

	x = 0;
	y = 1;
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(comm->path, comm->argv, get_environ(comm)) == -1)
		{
			destroy_command(comm, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(comm->status));
		if (WIFEXITED(comm->status))
		{
			comm->status = WEXITSTATUS(comm->status);
			if (comm->status == 126)
				print_error(comm, "Permission denied\n");
		}
	}
	if (x == y)
		y = 2;
}

