#include "myshell.h"

/**
 * handle_input - Handle the input, tokenize, and execute commands
 * @vars: Shell variable struct
 * @len_buffer: Buffer length
 * @is_pipe: Indicator for pipe or non-pipe mode
 */
void handle_input(vars_t *vars, size_t len_buffer, unsigned int is_pipe)
{
	size_t i;

	(void) len_buffer;

	vars->count++;
	vars->commands = tokenize(vars->buffer, ";");

	for (i = 0; vars->commands && vars->commands[i] != NULL; i++)
	{
		vars->av = tokenize(vars->commands[i], "\n \t\r");

		if (vars->av && vars->av[0])
		{
			execute_command(vars);
		}

		free(vars->av);
	}

	free(vars->buffer);
	free(vars->commands);

	if (is_pipe == 0)
		_puts("$ ");

	vars->buffer = NULL;
}
