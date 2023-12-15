#include "monty.h"

/**
 * open_fl - opens a file
 * @file_nm: the file namepath
 * Return: void
 */

void open_fl(char *file_nm)
{
	FILE *fd = fopen(file_nm, "r");

	if (file_nm == NULL || fd == NULL)
		err_s(2, file_nm);

	read_fl(fd);
	fclose(fd);
}


/**
 * read_fl - reads a file
 * @fb: pointer to file descriptor
 * Return: void
 */

void read_fl(FILE *fd)
{
	int line_nbr, frm = 0;
	char *bff = NULL;
	size_t _lent = 0;

	for  (line_nbr = 1; getline(&bff, &_lent, fd) != -1; line_nbr++)
	{
		frm = parse_ln(bff, line_nbr, frm);
	}
	free(bff);
}


/**
 * parse_ln - Separates each line into tokens to determine
 * which function to call
 * @bff: line from the file
 * @line_nbr: line number
 * @frm:  storage frm. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int parse_ln(char *bff, int line_nbr, int frm)
{
	char *opcode, *f_val_strue;
	const char *sep = "\n ";

	if (bff == NULL)
		err_s(4);

	opcode = strtok(bff, sep);
	if (opcode == NULL)
		return (frm);
	f_val_strue = strtok(NULL, sep);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_fc(opcode, f_val_strue, line_nbr, frm);
	return (frm);
}

/**
 * find_fc - find the appropriate function for the opcode
 * @opcode: opcode
 * @f_val_strue: argument of opcode
 * @frm:  storage frm. If 0 Nodes will be entered as a stack.
 * @ln_numb: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void find_fc(char *opcode, char *f_val_strue, int ln_numb, int frm)
{
	int n;
	int flag_s;

	instruction_t func_list[] = {
		{"push", push_node},
		{"pall", pall_stack},
		{"pop", pop_node},
		{"pint", print_tp},
		{"add", add},
		{"swap", swap_nodes_s},
		{"nop", nop},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag_s = 1, n = 0; func_list[n].opcode != NULL; n++)
	{
		if (strcmp(opcode, func_list[n].opcode) == 0)
		{
			call_fun(func_list[n].f, opcode, f_val_strue, ln_numb, frm);
			flag_s = 0;
		}
	}
	if (flag_s == 1)
		err_s(3, ln_numb, opcode);
}


/**
 * call_fun - Calls the required function.
 * @fc: Pointer to the function that is about to be called.
 * @op_str: string representing the opcode.
 * @val_str: string representing a numeric f_val_strue.
 * @ln_numb: line numeber for the instruction.
 * @frm: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void call_fun(op_func fc, char *op_str, char *val_str, int ln_numb, int frm)
{
	stack_t *node;
	int flag_s;
	int n;

	flag_s = 1;
	if (strcmp(op_str, "push") == 0)
	{
		if (val_str != NULL && val_str[0] == '-')
		{
			val_str = val_str + 1;
			flag_s = -1;
		}
		if (val_str == NULL)
			err_s(5, ln_numb);
		for (n = 0; val_str[n] != '\0'; n++)
		{
			if (isdigit(val_str[n]) == 0)
				err_s(5, ln_numb);
		}
		node = create_a_node(atoi(val_str) * flag_s);
		if (frm == 0)
			fc(&node, ln_numb);
		if (frm == 1)
			add_queue(&node, ln_numb);
	}
	else
		fc(&head, ln_numb);
}
