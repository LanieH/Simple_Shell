#include "myshell.h"

/**
 * execute_builtin - Runs built-in commands
 * @vars: contains program variables
 *
 * Return: 1 if command is a built-in, 0 if otherwise
 */
int execute_builtin(vars_t *vars)
{
	if (_strcmpr(vars->av[0], "exit") == 0)
	{
		custom_exit(vars);
		return (1);
	}
	else if (_strcmpr(vars->av[0], "env") == 0)
	{
		_env(vars);
		return (1);
	}
	else if (_strcmpr(vars->av[0], "setenv") == 0)
	{
		_setenv(vars);
		return (1);
	}
	else if (_strcmpr(vars->av[0], "unsetenv") == 0)
	{
		_unsetenv(vars);
		return (1);
	}
	return (0);
}

/**
 * custom_exit - Handles the 'exit' built-in command
 * @vars: contains program variables
 */
void custom_exit(vars_t *vars)
{
	int status = vars->av[1] ? _atoi(vars->av[1]) : vars->status;

	if (vars->av[1] && status == -1)
	{
		vars->status = 2;
		print_error(vars, ": Illegal number: ");
		_puts2(vars->av[1]);
		_puts2("\n");
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_env(vars->env);
	exit(status);
}

/**
 * _env - Handles the 'env' built-in command
 * @vars: Contains program variables
 */
void _env(vars_t *vars)
{
	int i;

	for (i = 0; vars->env[i]; i++)
	{
		_puts(vars->env[i]);
		_puts("\n");
	}
	vars->status = 0;
}

/**
 * _setenv - Handles 'setenv' built-in command
 * @vars: Contains program variables
 */
void _setenv(vars_t *vars)
{
	char *key = vars->av[1];
	char *value = vars->av[2];

	if (!key || !value)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}

	if (find_key(vars->env, key) != NULL)
	{
	char *new_var = add_value(key, value);

		if (!new_var)
		{
			print_error(vars, NULL);
			exit(127);
		}
		replace_value(&vars->env, key, new_var);
		free(new_var);
	}
	else
	{
		char *new_var = add_key_value(key, value);

		if (!new_var)
		{
			print_error(vars, NULL);
			exit(127);
		}
		add_key(&vars->env, new_var);
		free(new_var);
	}
	vars->status = 0;
}

/**
 * _unsetenv - Handles 'unsetenv' built-in commnd
 * @vars: Contains program variables
 */
void _unsetenv(vars_t *vars)
{
	char *key = vars->av[1];

	if (!key)
	{
		print_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}

	if (find_key(vars->env, key) != NULL)
	{
		char **new_env;
		int new_len = len_env(vars->env) - 1;
		int i = 0;
		int j = 0;

		new_env = malloc(sizeof(char *) * (new_len + 1));
		if (!new_env)
		{
			print_error(vars, NULL);
			exit(127);
		}

		for (; vars->env[i]; i++)
		{
			if (_strcmpr(vars->env[i], key) != 0)
			{
				new_env[j] = vars->env[i];
				j++;
			}
		}
		new_env[new_len] = NULL;
		free(vars->env);
		vars->env = new_env;
	}
	vars->status = 0;
}
