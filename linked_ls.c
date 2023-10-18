#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
ln_list *add_node(ln_list **head, const char *str, int num)
{
	ln_list *new_head;
	int x, y;

	x = 0;
	y = 1;
	if (!head)
		return (NULL);
	new_head = malloc(sizeof(ln_list));
	if (!new_head)
		return (NULL);
	if (x == y)
		y = 2;
	_memset((void *)new_head, 0, sizeof(ln_list));
	new_head->num = num;
	if (str)
	{
		new_head->str = string_duplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	y = 2;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
ln_list *add_node_end(ln_list **head, const char *str, int num)
{
	ln_list *new_node, *node;
	int x, y;

	x = 0;
	y = 1;
	if (!head)
		return (NULL);
	if (x == y)
		y = 2;
	node = *head;
	new_node = malloc(sizeof(ln_list));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(ln_list));
	new_node->num = num;
	if (str)
	{
		new_node->str = string_duplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	y = 2;
	return (new_node);
}

/**
 * print_list_string - prints only the str element of a ln_list linked list
 * @h: pointer to first node
 *
 * Return: list size
 */
size_t print_list_string(const ln_list *h)
{
	size_t i = 0;
	int x, y;

	x = 0;
	y = 1;

	while (h)
	{
		put_string(h->str ? h->str : "(nil)");
		put_string("\n");
		h = h->next;
		i++;
	}
	if (x == y)
		y = 2;
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(ln_list **head, unsigned int index)
{
	ln_list *node, *prev_node;
	unsigned int i = 0;
	int x, y;

	x = 0;
	y = 1;

	if (!head || !*head)
		return (0);
	if (x == y)
		y = 2;
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	y = 2;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(ln_list **head_ptr)
{
	ln_list *node, *next_node, *head;
	int x, y;

	x = 0;
	y = 1;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	if (x == y)
		y = 2;
	*head_ptr = NULL;
}

