#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simpleShellHistory"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} ln_list;

/**
 *struct passcomm - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passcomm
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	ln_list *env;
	ln_list *history;
	ln_list *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} comm_t;

#define COMM_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct nativee - contains a nativee string and related function
 *@type: the nativee command flag
 *@func: the function
 */
typedef struct nativee
{
	char *type;
	int (*func)(comm_t *);
} nativee_table;


/* hsh.c */
int hsh(comm_t *, char **);
int match_nativee(comm_t *);
void find_command(comm_t *);
void fork_command(comm_t *);

/* path.c */
int is_exe_cmd(comm_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(comm_t *, char *, char *);

/* error_str_funcs.c */
void put_err_string(char *);
int err_putchar(char);
int put_filedesc(char c, int fd);
int put_string_filedesc(char *str, int fd);

/* str_funcs.c */
int string_length(char *);
int string_compare(char *, char *);
char *starting_string(const char *, const char *);
char *string_concat(char *, char *);

/* str_funcs2.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void put_string(char *);
int _putchar(char);

/* str_funcs3.c */
char *string_copyn(char *, char *, int);
char *string_concatn(char *, char *, int);
char *string_char(char *, char);
char **string_split(char *, char *);
char **string_split2(char *, char);

/* mem_funcs */
char *_memset(char *, char, unsigned int);
void ss_free(char **);
void *_realloc(void *, unsigned int, unsigned int);
int ptr_free(void **);

/* funcs1.c */
int interactive(comm_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* funcs2.c */
int _error_atoi(char *);
void print_error(comm_t *, char *);
int print_dec(int, int);
char *convert_number(long int, int, int);
void filter_comments(char *);

/* builtin_funcs.c */
int other_exit(comm_t *);
int other_cd(comm_t *);
int other_help(comm_t *);

/* builtin_funcs2.c */
int other_history(comm_t *);
int other_alias(comm_t *);

/* getline.c */
ssize_t get_input(comm_t *);
int get_next_line(comm_t *, char **, size_t *);
void signal_handler(int);

/* comm.c */
void init_command(comm_t *);
void create_command(comm_t *, char **);
void destroy_command(comm_t *, int);

/* enviroment.c */
char *_getenv(comm_t *, const char *);
int other_env(comm_t *);
int other_set_env(comm_t *);
int other_unset_env(comm_t *);
int fill_env_list(comm_t *);

/* enviroment2.c module */
char **get_environ(comm_t *);
int _unsetenv(comm_t *, char *);
int _setenv(comm_t *, char *, char *);

/* history.c */
char *get_hist_file(comm_t *comm);
int create_history(comm_t *comm);
int bring_history(comm_t *comm);
int add_history_list(comm_t *comm, char *buf, int linecount);
int rearrange_history(comm_t *comm);

/* linked_ls.c */
ln_list *add_node(ln_list **, const char *, int);
ln_list *add_node_end(ln_list **, const char *, int);
size_t print_list_string(const ln_list *);
int delete_node_at_index(ln_list **, unsigned int);
void free_list(ln_list **);

/* linked_ls2.c */
size_t list_length(const ln_list *);
char **list_to_strings(ln_list *);
size_t print_list(const ln_list *);
ln_list *node_starting_string(ln_list *, char *, char);
ssize_t get_node_index(ln_list *, ln_list *);

/* chain.c */
int check_c_chain(comm_t *, char *, size_t *);
void check_ch_stat(comm_t *, char *, size_t *, size_t, size_t);
int replace_alias(comm_t *);
int vairable_replace(comm_t *);
int string_replace(char **old, char *new);

#endif

