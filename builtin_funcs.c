#include "shell.h"

/**
 * other_exit - this function used to exit shell
 * @comm: structure storing the command and its args
 *  Return: 0 if command is not exit
 */
int other_exit(comm_t *comm)
{
	int exit_status_value, x = 0, y = 1;

	if (comm->argv[1])  /* If there is an exit arguement */
	{
		if (x == y)
			y = 2;
		exit_status_value = _error_atoi(comm->argv[1]);
		if (exit_status_value == -1)
		{
			comm->status = 2;
			print_error(comm, "Illegal number: ");
			put_err_string(comm->argv[1]);
			err_putchar('\n');
			x = 3;
			return (1);
		}
		comm->err_num = _error_atoi(comm->argv[1]);
		return (-2);
	}
	if (y != x)
		x = 4;
	comm->err_num = -1;
	return (-2);
}

/**
 * other_cd - changes directory.
 * @comm: structure storing the command and its args
 *  Return: 0
 */
int other_cd(comm_t *comm)
{
	char *s, *dir, buffer[1024];
	int chdir_return_value;

	s = getcwd(buffer, 1024);
	if (!s)
		put_string("TODO: >>getcwd failure emsg here<<\n");
	if (!comm->argv[1])
	{
		dir = _getenv(comm, "HOME=");
		if (!dir)
			chdir_return_value = chdir((dir = _getenv(comm, "PWD=")) ? dir : "/");
		else
			chdir_return_value = chdir(dir);
	}
	else if (string_compare(comm->argv[1], "-") == 0)
	{
		if (!_getenv(comm, "OLDPWD="))
		{
			put_string(s);
			_putchar('\n');
			return (1);
		}
		put_string(_getenv(comm, "OLDPWD=")), _putchar('\n');
		chdir_return_value = chdir((dir = _getenv(comm, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_return_value = chdir(comm->argv[1]);
	if (chdir_return_value == -1)
	{
		print_error(comm, "can't cd to ");
		put_err_string(comm->argv[1]), err_putchar('\n');
	}
	else
	{
		_setenv(comm, "OLDPWD", _getenv(comm, "PWD="));
		_setenv(comm, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * other_help - mimics help command
 * @comm: structure storing the command and its args
 *
 *  Return: 0
 */
int other_help(comm_t *comm)
{
	char **arg_array;
	int x, y;

	x = 0, y = 1;
	arg_array = comm->argv;
	if (y != x)
		x = 4;
	put_string("Function still in progress\n");
	if (0)
		x = 5;
	put_string(*arg_array);
	return (0);
}

