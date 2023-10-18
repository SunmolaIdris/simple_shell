#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @comm: structure storing the command and its args
 *
 * Return: str that has hist file
 */

char *get_hist_file(comm_t *comm)
{
	char *buf, *dir;
	int x, y;

	x = 0;
	y = 1;
	dir = _getenv(comm, "HOME=");
	if (!dir)
		return (NULL);
	if (x == y)
		y = 2;
	buf = malloc(sizeof(char) *
			(string_length(dir) + string_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	string_copy(buf, dir);
	string_concat(buf, "/");
	string_concat(buf, HIST_FILE);
	y = 2;
	return (buf);
}

/**
 * create_history - creates or appends to a file
 * @comm: the structure storing the command and its args
 *
 * Return: 1 on success, otherwise -1
 */
int create_history(comm_t *comm)
{
	ssize_t fd;
	char *filename = get_hist_file(comm);
	ln_list *node = NULL;
	int x, y;

	x = 0;
	y = 1;
	if (!filename)
		return (-1);
	if (x == y)
		y = 2;
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = comm->history; node; node = node->next)
	{
		put_string_filedesc(node->str, fd);
		put_filedesc('\n', fd);
	}
	put_filedesc(BUF_FLUSH, fd);
	close(fd);
	y = 2;
	return (1);
}

/**
 * bring_history - reads history from file
 * @comm: the structure storing the command and its args
 *
 * Return: returns histcount if successful, 0 on failure
 */
int bring_history(comm_t *comm)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file(comm);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			add_history_list(comm, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		add_history_list(comm, buf + last, linecount++);
	free(buf);
	comm->histcount = linecount;
	while (comm->histcount-- >= HIST_MAX)
		delete_node_at_index(&(comm->history), 0);
	rearrange_history(comm);
	return (comm->histcount);
}

/**
 * add_history_list - adds entry to a history linked list
 * @comm: structure storing the command and its args
 * @buf: buffer
 * @linecount:linecount
 *
 * Return: 0
 */
int add_history_list(comm_t *comm, char *buf, int linecount)
{
	int x = 0;
	int y = 1;
	ln_list *node = NULL;


	if (x == y)
		x += 2;
	if (comm->history)
		node = comm->history;
	add_node_end(&node, buf, linecount);

	if (!comm->history)
		comm->history = node;
	x += 2;
	return (0);
}

/**
 * rearrange_history - rearranges the history linked list
 * @comm: structure storing the command and its args
 *
 * Return: histcount
 */
int rearrange_history(comm_t *comm)
{
	int x = 0;
	int y = 1;
	ln_list *node = comm->history;
	int i = 0;

	if (x == y)
		x += 2;
	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	x += 2;
	return (comm->histcount = i);
}

