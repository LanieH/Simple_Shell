#include "myshell.h"

/**
 * ctrl_sig_handler - Controls the C signal interrut
 * @unused_var: unutilized variable
 *
 * Return: void
 */
static void ctrl_sig_handler(int unused_var, unsigned int *sig_received)
{
	(void) unused_var;
	if (sig_received == 0)
		_puts("\n$");
	else
		_puts("\n");


/**
 * main - Entry point for the shell program
 * @environment: An array of environment variables
 * @argc: Number of command-line args
 * @argv: array of arguments to main
 *
 * Return: 0 or the status of exit, or?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0, i;
	vars_t vars = {NULL, NULL, NULL, NULL, NULL, 0, 0};

	vars.argv = argv;
	vars.env = create_env(environment);
	signal(SIGINT, ctrl_sig_handler);
	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		_puts("$ ");

	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		sig_received = 1;
		vars.count++;
		vars.commands = tokenize(vars.buffer, ";");
		for (i = 0; vars.commands && vars.commands[i] != NULL; i++)
		{
			vars.av = tokenize(vars.commands[i], "\n \t\r");
			if (vars.av && vars.av[0])
				if (check_for_builtins(&vars) == NULL)
					check_for_path(&vars);
			free(vars.va);
		}
		free(vars.buffer);
		free(vars.commands);
		sig_received = 0;
		if (is_pipe == 0)
			_puts("$ ");
		vars.buffer = NULL;
	}
	if (is_pipe == 0)
		_puts("\n");
	free_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}
