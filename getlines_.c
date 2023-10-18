#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @comm: structure storing the command and its args
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(comm_t *comm, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;
	int x, y;

	x = 0;
	y = 1;
	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, signal_handler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_next_line(comm, buf, &len_p);
#endif
		if (x == y)
			y = 2;
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			comm->linecount_flag = 1;
			filter_comments(*buf);
			add_history_list(comm, *buf, comm->histcount++);
			{
				*len = r;
				comm->cmd_buf = buf;
			}
		}
	}
	y = 2;
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @comm: structure storing the command and its args
 *
 * Return: bytes read
 */
ssize_t get_input(comm_t *comm)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(comm->arg), *p;
	int x, y;

	x = 0;
	y = 1;
	_putchar(BUF_FLUSH);
	r = input_buffer(comm, &buf, &len);
	if (r == -1)
		return (-1);
	if (x == y)
		y = 2;
	if (len)
	{
		j = i;
		p = buf + i;
		check_ch_stat(comm, buf, &j, i, len);
		while (j < len)
		{
			if (check_c_chain(comm, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			comm->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (string_length(p));
	}
	*buf_p = buf;
	y = 2;
	return (r);
}

/**
 * read_buffer - reads a buffer
 * @comm: structure storing the command and its args
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(comm_t *comm, char *buf, size_t *i)
{
	ssize_t r = 0;
	int x, y;

	x = 0;
	y = 1;
	if (*i)
		return (0);
	r = read(comm->readfd, buf, READ_BUFFER_SIZE);
	if (x == y)
		y = 2;
	if (r >= 0)
		*i = r;
	y = 2;
	return (r);
}

/**
 * get_next_line - gets the next line of input from STDIN
 * @comm: structure storing the command and its args
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_next_line(comm_t *comm, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;
	int x = 0, y = 1;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	if (x == y)
		y = 2;
	r = read_buffer(comm, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = string_char(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		string_concatn(new_p, buf + i, k - i);
	else
		string_copyn(new_p, buf + i, k - i + 1);
	if (x != y)
		y = 3;
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	y = 2;
	return (s);
}

/**
 * signal_handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void signal_handler(__attribute__((unused))int sig_num)
{
	int x, y;

	x = 0;
	y = 1;
	put_string("\n");
	put_string("$ ");
	_putchar(BUF_FLUSH);
	if (x == y)
		y = 2;
}

