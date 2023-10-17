#ifndef _MYSHELL_H
#define _MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * struct vars_s - Variables
 * @av: Arguments
 * @buffer: Command buffer
 * @commands: Array of commands
 * @status: Last exit status
 * @env: Environment variables
 * @interactive: Interactive mode flag
 */
typedef struct vars_s
{
	char **av;
	char *buffer;
	char **commands;
	int status;
	char **env;
	int interactive;
} vars_t;

/* main.c */
int main(void);

/* execute_command.c */
void execute_command(char *command);

/* builtins.c */
int execute_builtin(vars_t *vars);
void custom_exit(vars_t *vars);
void _env(vars_t *vars);
void _setenv(vars_t *vars);
void _unsetenv(vars_t *vars);

/* helper_functions.c */
char *_getline(char **lineptr, size_t *n, FILE *stream);
char *_strtok(char *str, const char *delim);
int _atoi(char *s);
void _puts(char *str);
void _puts2(char *str);
int _strcmpr(const char *s1, const char *s2);
char **tokenize_commands(char *line);
char *add_key_value(char *key, char *value);
char *add_value(char *key, char *value);
void replace_value(char ***env, char *key, char *new_value);
char **find_key(char **env, char *key);
char **add_key(char ***env, char *key);
void free_env(char **env);
int len_env(char **env);
void print_error(vars_t *vars, char *msg);
#endif
