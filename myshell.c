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
