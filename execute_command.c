#include "myshell.h"

/**
 * execute_command - Runs an external command.
 * @vars: Program variables
 * @command: Commnd to run.
 */
void execute_command(char *command)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		char *args[] = {NULL, NULL};

		if (execve(command, args, NULL) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}
