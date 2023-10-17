#include "myshell.h"

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
	vars_t vars = {NULL, NULL, 0, 0};

	while (1)
	{
		_puts("#cisfun$ ");
		characters_read = _getline(&line, &len, stdin);

		if (characters_read == -1)
		{
			perror("getline");
			break;
		}

		if (characters_read > 0)
		{
			line[characters_read - 1] = '\0';

			token = _strtok(line, " ");

			while (token != NULL)
			{
				command = token;
				vars.av = tokenize_commands(line);
				
				if (!vars.av)
				{
					free(vars.av);
					continue;
				}

				execute_command(&vars, command);
				free(vars.av);

				token = _strtok(NULL, " ");
			}
		}
	}
	return (vars.status);
}
