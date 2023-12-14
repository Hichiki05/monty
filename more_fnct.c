#include "monty.h"
stack_t *head = NULL;

/**
 * main - entry point
 * @argc: arguments count
 * @argv: list of arguments
 * Return: always 0
 */

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	open_fl(argv[1]);
	free_node_s();
	return (0);
}

/**
 * create_a_node - Creates a nd.
 * @n: Number to go inside the nd.
 * Return: Upon sucess a pointer to the nd. Otherwise NULL.
 */
stack_t *create_a_node(int n)
{
	stack_t *nd;

	nd = malloc(sizeof(stack_t));
	if (nd == NULL)
		err(4);
	nd->next = NULL;
	nd->prev = NULL;
	nd->n = n;
	return (nd);
}

/**
 * free_node_s - Frees nodes in the stack.
 */
void free_node_s(void)
{
	stack_t *tp;

	if (head == NULL)
		return;

	while (head != NULL)
	{
		tp = head;
		head = head->next;
		free(tp);
	}
}


/**
 * add_queue - Adds a nd to the queue.
 * @new_node: Pointer to the new nd.
 * @ln: line number of the opcode.
 */
void add_queue(stack_t **new_node, __attribute__((unused))unsigned int ln)
{
	stack_t *tp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tp = head;
	while (tp->next != NULL)
		tp = tp->next;

	tp->next = *new_node;
	(*new_node)->prev = tp;

}
