#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Global environment */
extern char **environ;

/* Function prototypes */
void prompt(void);
char *read_line(void);
char **split_line(char *line);
int execute(char **argv, char *program_name);
void simple_shell(void);

#endif /* SHELL_H */
