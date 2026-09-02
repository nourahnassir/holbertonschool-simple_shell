#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int simple_shell(char *prog_name);
int execute_command(char **argv, char *prog_name, int cmd_count);
int parse_line(char *line, char **argv);
void print_env(void);
char *_getenv(const char *name);
char *build_full_path(char *dir, char *cmd);
char *find_path(char *cmd);

#endif /* SHELL_H */
