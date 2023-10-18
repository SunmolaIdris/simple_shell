#include "shell.h"

/**
 * main - main function and entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 otherwise
 */
int main(int ac, char **av)
{
	comm_t comm[] = { COMM_INIT };
	int fd = 2, x, y;

	x = 0;
	y = 1;

	fd += 3;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (x == y)
			y = 2;
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				put_err_string(av[0]);
				put_err_string(": 0: Can't open ");
				put_err_string(av[1]);
				err_putchar('\n');
				err_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		comm->readfd = fd;
	}
	if (x == y)
		y = 2;
	fill_env_list(comm);
	bring_history(comm);
	hsh(comm, av);
	y = 2;
	return (EXIT_SUCCESS);
}

