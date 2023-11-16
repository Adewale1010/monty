#include "monty.h"

/**
 * _set_op_tok_error - Sets last element of op_toks to be an error code.
 * @error_code: Integer to store as a string in op_toks.
 */

void _set_op_tok_error(int error_code)
{
	char *exit_str = NULL;
	char **new_toks = NULL;
	int toks_len = 0, idx = 0;

	toks_len = _token_arr_len();
	new_toks = malloc(sizeof(char *) * (toks_len + 2));
	if (!_op_toks)
	{
		_malloc_error();
		return;
	}
	while (idx < toks_len)
	{
		new_toks[idx] = _op_toks[idx];
		idx++;
	}
	exit_str = _get_int(error_code);
	if (!exit_str)
	{
		free(new_toks);
		_malloc_error();
		return;
	}
	new_toks[idx++] = exit_str;
	new_toks[idx] = NULL;
	free(_op_toks);
	_op_toks = new_toks;
}
