#ifndef __MONTY_H__
#define __MONTY_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STACK 0
#define QUEUE 1
#define DELIMS " \n\t\a\b"

/* GLOBAL OPCODE TOKENS */
extern char **_op_toks;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* PRIMARY INTERPRETER FUNCTIONS */
void _free_stack(stack_t **stack);
int _init_stack(stack_t **stack);
int _check_mode(stack_t *stack);
void _free_tokens(void);
unsigned int _token_arr_len(void);
int _run_monty(FILE *script_fd);
void _set_op_tok_error(int error_code);

/* OPCODE FUNCTIONS */
void _monty_push(stack_t **stack, unsigned int line_number);
void _monty_pall(stack_t **stack, unsigned int line_number);
void _monty_pint(stack_t **stack, unsigned int line_number);
void _monty_pop(stack_t **stack, unsigned int line_number);
void _monty_swap(stack_t **stack, unsigned int line_number);
void _monty_add(stack_t **stack, unsigned int line_number);
void _monty_nop(stack_t **stack, unsigned int line_number);
void _monty_sub(stack_t **stack, unsigned int line_number);
void _monty_div(stack_t **stack, unsigned int line_number);
void _monty_mul(stack_t **stack, unsigned int line_number);
void _monty_mod(stack_t **stack, unsigned int line_number);
void _monty_pchar(stack_t **stack, unsigned int line_number);
void _monty_pstr(stack_t **stack, unsigned int line_number);
void _monty_rotl(stack_t **stack, unsigned int line_number);
void _monty_rotr(stack_t **stack, unsigned int line_number);
void _monty_stack(stack_t **stack, unsigned int line_number);
void _monty_queue(stack_t **stack, unsigned int line_number);

/* CUSTOM STANDARD LIBRARY FUNCTIONS */
char **strtow(char *str, char *delims);
char *_get_int(int n);

/* ERROR MESSAGES & ERROR CODES */
int _usage_error(void);
int _malloc_error(void);
int _f_open_error(char *filename);
int _unknown_op_error(char *opcode, unsigned int line_number);
int _no_int_error(unsigned int line_number);
int _pop_error(unsigned int line_number);
int _pint_error(unsigned int line_number);
int _short_stack_error(unsigned int line_number, char *op);
int _div_error(unsigned int line_number);
int _pchar_error(unsigned int line_number, char *message);

#endif /* __MONTY_H__ */
