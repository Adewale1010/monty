#include "monty.h"

void _monty_pop(stack_t **stack, unsigned int line_number);
void _monty_pall(stack_t **stack, unsigned int line_number);
void _monty_push(stack_t **stack, unsigned int line_number);
void _monty_swap(stack_t **stack, unsigned int line_number);
void _monty_pint(stack_t **stack, unsigned int line_number);

/**
 * _monty_pop - Removes the top value element of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */

void _monty_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *next = NULL;

	if ((*stack)->next == NULL)
	{
		_set_op_tok_error(_pop_error(line_number));
		return;
	}

	next = (*stack)->next->next;
	free((*stack)->next);
	if (next)
		next->prev = *stack;
	(*stack)->next = next;
}

/**
 * _monty_pall - Prints the values of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */

void _monty_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = (*stack)->next;

	while (tmp)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
	(void)line_number;
}

/**
 * _monty_push - Pushes a value to a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */

void _monty_push(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp, *new;
	int idx;

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		_set_op_tok_error(_malloc_error());
		return;
	}

	if (_op_toks[1] == NULL)
	{
		_set_op_tok_error(_no_int_error(line_number));
		return;
	}

	for (idx = 0; _op_toks[1][idx]; idx++)
	{
		if (_op_toks[1][idx] == '-' && idx == 0)
			continue;
		if (_op_toks[1][idx] < '0' || _op_toks[1][idx] > '9')
		{
			_set_op_tok_error(_no_int_error(line_number));
			return;
		}
	}
	new->n = atoi(_op_toks[1]);

	if (_check_mode(*stack) == STACK)
	{
		tmp = (*stack)->next;
		new->prev = *stack;
		new->next = tmp;
		if (tmp)
			tmp->prev = new;
		(*stack)->next = new;
	}
	else
	{
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		new->next = NULL;
		tmp->next = new;
	}
}

/**
 * _monty_swap - Swaps the top two value elements of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */

void _monty_swap(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		_set_op_tok_error(_short_stack_error(line_number, "swap"));
		return;
	}

	tmp = (*stack)->next->next;
	(*stack)->next->next = tmp->next;
	(*stack)->next->prev = tmp;
	if (tmp->next)
		tmp->next->prev = (*stack)->next;
	tmp->next = (*stack)->next;
	tmp->prev = *stack;
	(*stack)->next = tmp;
}

/**
 * _monty_pint - Prints the top value of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */

void _monty_pint(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next == NULL)
	{
		_set_op_tok_error(_pint_error(line_number));
		return;
	}

	printf("%d\n", (*stack)->next->n);
}
