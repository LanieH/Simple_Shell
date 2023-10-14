#ifndef _MYSHELL_H
#define _MYSHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *command);
#endif
