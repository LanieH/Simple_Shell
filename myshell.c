#include "myshell.h"

void execute_command(char *command);

/**
 * main - Simple shell program
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t characters_read;
	char *token, *command;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		fflush(stdout);
		characters_read = getline(&line, &len, stdin);

		if (characters_read == EOF)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(EXIT_SUCCESS);
		}

		if (characters_read > 0)
		{
			line[characters_read - 1] = '\0';

			token = strtok(line, " ");
			command = token;

			if (command != NULL)
			{
				execute_command(command);
			}
		}
	}
	return (0);
}

/**
 * execute_command - runs a command
 * @command: command to run
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

		args[0] = command;

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
