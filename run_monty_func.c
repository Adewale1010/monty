#include "monty.h"
#include <string.h>

int _is_empty_line(char *line, char *delims);
unsigned int _token_arr_len(void);
void _free_tokens(void);
void (*_get_op_func(char *opcode))(stack_t**, unsigned int);
int _run_monty(FILE *script_fd);

/**
 * _is_empty_line - Checks if a line read
 *	from getline only contains delimiters.
 * @line: A pointer to the line.
 * @delims: A string of delimiter characters.
 *
 * Return: If the line only contains delimiters - 1.
 *         Otherwise - 0.
 */

int _is_empty_line(char *line, char *delims)
{
	int idx, j;

	for (idx = 0; line[idx]; idx++)
	{
		for (j = 0; delims[j]; j++)
		{
			if (line[idx] == delims[j])
			{
				break;
			}
		}
		if (delims[j] == '\0')
		{
			return (0);
		}
	}

	return (1);
}

/**
 * _token_arr_len - Gets the length of current _op_toks.
 *
 * Return: Length of current op_toks (as int).
 */

unsigned int _token_arr_len(void)
{
	unsigned int _toks_len = 0;

	while (_op_toks[_toks_len])
	{
		_toks_len++;
	}
	return (_toks_len);
}

/**
 * _free_tokens - Frees the global op_toks array of strings.
 */

void _free_tokens(void)
{
	size_t idx = 0;

	if (_op_toks == NULL)
	{
		return;
	}

	for (idx = 0; _op_toks[idx]; idx++)
	{
		free(_op_toks[idx]);
	}

	free(_op_toks);
}

/**
 * _get_op_func - Matches an opcode with its corresponding function.
 * @opcode: The opcode to match.
 *
 * Return: A pointer to the corresponding function.
 */

void (*_get_op_func(char *opcode))(stack_t**, unsigned int)
{
	instruction_t op_funcs[] = {
		{"push", _monty_push},
		{"pall", _monty_pall},
		{"pint", _monty_pint},
		{"pop", _monty_pop},
		{"swap", _monty_swap},
		{"add", _monty_add},
		{"nop", _monty_nop},
		{"sub", _monty_sub},
		{"div", _monty_div},
		{"mul", _monty_mul},
		{"mod", _monty_mod},
		{"pchar", _monty_pchar},
		{"pstr", _monty_pstr},
		{"rotl", _monty_rotl},
		{"rotr", _monty_rotr},
		{"stack", _monty_stack},
		{"queue", _monty_queue},
		{NULL, NULL}
	};
	int idx;

	for (idx = 0; op_funcs[idx].opcode; idx++)
	{
		if (strcmp(opcode, op_funcs[idx].opcode) == 0)
		{
			return (op_funcs[idx].f);
		}
	}

	return (NULL);
}

/**
 * _run_monty - Primary function to execute a Monty bytecodes script.
 * @script_fd: File descriptor for an open Monty bytecodes script.
 *
 * Return: EXIT_SUCCESS on success, respective error code on failure.
 */

int _run_monty(FILE *script_fd)
{
	stack_t *stack = NULL;
	char *line = NULL;
	size_t length = 0, exit_status = EXIT_SUCCESS;
	unsigned int line_number = 0, prev_tok_length = 0;
	void (*op_func)(stack_t**, unsigned int);

	if (_init_stack(&stack) == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}

	while (_getline(&line, &length, script_fd) != -1)
	{
		line_number++;
		_op_toks = strtow(line, DELIMS);
		if (_op_toks == NULL)
		{
			if (_is_empty_line(line, DELIMS))
			{
				continue;
			}
			_free_stack(&stack);
			return (_malloc_error());
		}
		else if (_op_toks[0][0] == '#')
		{
			_free_tokens();
			continue;
		}
		op_func = _get_op_func(_op_toks[0]);
		if (op_func == NULL)
		{
			_free_stack(&stack);
			exit_status = _unknown_op_error(_op_toks[0], line_number);
			_free_tokens();
			break;
		}
		prev_tok_length = _token_arr_len();
		op_func(&stack, line_number);
		if (_token_arr_len() != prev_tok_length)
		{
			if (_op_toks && _op_toks[prev_tok_length])
			{
				exit_status = atoi(_op_toks[prev_tok_length]);
			}
			else
			{
				exit_status = EXIT_FAILURE;
			}
			_free_tokens();
			break;
		}
		_free_tokens();
	}
	_free_stack(&stack);

	if (line && line == 0)
	{
		free(line);
		return (_malloc_error());
	}

	free(line);
	return (exit_status);
}
