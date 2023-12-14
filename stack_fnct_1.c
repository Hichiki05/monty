#include "monty.h"


/**
 * push_node - Adds a node to the stack.
 * @new_node: Pointer to the new node.
 * @ln: Interger representing the line number of of the opcode.
 */
void push_node(stack_t **new_node, __attribute__((unused))unsigned int ln)
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
	head = *new_node;
	head->next = tp;
	tp->prev = head;
}


/**
 * pall_stack - Adds a node to the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: line number of  the opcode.
 */
void pall_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *tp;

	(void) line_number;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	tp = *stack;
	while (tp != NULL)
	{
		printf("%d\n", tp->n);
		tp = tp->next;
	}
}

/**
 * pop_node - Adds a node to the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void pop_node(stack_t **stack, unsigned int line_number)
{
	stack_t *tp;

	if (stack == NULL || *stack == NULL)
		more_err_s(7, line_number);

	tp = *stack;
	*stack = tp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tp);
}

/**
 * print_tp - Prints the top node of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void print_tp(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
		more_err_s(6, line_number);
	printf("%d\n", (*stack)->n);
}

/**
 * add - Adds the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void add(stack_t **stack, unsigned int line_number)
{
	int sm;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err_s(8, line_number, "add");

	(*stack) = (*stack)->next;
	sm = (*stack)->n + (*stack)->prev->n;
	(*stack)->n = sm;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
