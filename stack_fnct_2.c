#include "monty.h"


/**
 * swap_nodes_s - Swaps the top two elements of the stack.
 * @stack: Double pointer to the beginning of the stack.
 * @line_number: Line number of the opcode in the Monty file.
 *
 * Description: This function swaps the top two elements of the stack.
 * If the stack contains less than two elements, it prints an error message.
 */
void swap_nodes_s(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err_s(10, line_number);

	temp = (*stack)->next;
	(*stack)->next = temp->next;
	(*stack)->prev = temp;
	if (temp->next != NULL)
		temp->next->prev = *stack;
	temp->next = *stack;
	temp->prev = NULL;
	*stack = temp;
}
