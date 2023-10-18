#include "myshell.h"

/**
 * exec_command - Runs a command with arguments
 * @cmd: Command to run
 * @args: Array of arguments
 */
void exec_command(char *cmd, char **args)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(cmd, args, NULL) == -1)
			perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}

/**
 * execute_command - Run a single command with arguments
 * @vars: Shell variables Struct
 */
void execute_command(vars_t *vars)
{
	chat *cmd = check_for_path(vars);

	if (cmd != NULL)
	{
		exec_command(cmd, vars->av);
		free(cmd);
	}
}

/**
 * main - Main function for the shell
 * @environment: Array of environment variables
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Return: 0 or exit status
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0;
	vars_t vars = {NULL, NULL, NULL, NULL, NULL, 0, 0};

	vars.argv = argv;
	vars.env = create_env(environment);
	signal(SIGINT, ctrl_sig_handler);

	if (!isatty(STDIN_FILENO))
		is_pipe = 1;

	if (is_pipe == 0)
		_puts("$ ");
	sig_received = 0;

	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		sig_received = 1;
		handle_input(&vars, len_buffer, is_pipe);
	}

	if (is_pipe == 0)
		_puts("\n");

	free_env(vars.env);
	free(vars.buffer);
	exit(vars.status);
}
