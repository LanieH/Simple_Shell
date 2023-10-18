#ifndef _MYSHELL_H
#define _MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/* Define structures and types as needed for your program */

typedef struct
{
	char **env;
	char **argv;
	char *buffer;
	char **commands;
	char **av;
	unsigned int count;
	unsigned int status;
} vars_t;

/* Function prototypes */

void ctrl_sig_handler(int unused_var, unsigned int *sig_received);
void exec_command(char *cmd, char **args);
char *check_for_path(vars_t *vars);
void execute_command(vars_t *vars);
void handle_input(vars_t *vars, size_t len_buffer, unsigned int is_pipe);
char **tokenize(char *str, const char *delimiter);
char **create_env(char **environment);
void free_env(char **env);
void _puts(const char *str);
#endif
