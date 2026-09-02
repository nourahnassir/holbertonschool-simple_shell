#include "shell.h"

/**
 * execute_command - Forks and executes a command
 * @argv: Argument vector
 *
 * Return: Nothing.
 */
void execute_command(char **argv)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * simple_shell - Reads and executes commands from stdin
 *
 * Return: Nothing.
 */
void simple_shell(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *argv[1024];
	char *token;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		i = 0;
		token = strtok(line, " \t");
		while (token != NULL)
		{
			argv[i++] = token;
			token = strtok(NULL, " \t");
		}
		argv[i] = NULL;

		if (i > 0)
			execute_command(argv);
	}
	free(line);
}