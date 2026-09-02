#include "shell.h"

/**
 * print_env - Prints the current environment variables
 *
 * Return: Nothing.
 */
void print_env(void)
{
	int i = 0;

	if (!environ)
		return;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * execute_command - Resolves path and executes command
 * @argv: Argument vector
 * @prog_name: Name of the shell executable
 * @cmd_count: Command count for error formatting
 *
 * Return: Exit status of the executed command or error code
 */
int execute_command(char **argv, char *prog_name, int cmd_count)
{
	char *full_path;
	pid_t pid;
	int status;

	full_path = find_path(argv[0]);
	if (!full_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, cmd_count, argv[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		free(full_path);
		return (1);
	}
	if (pid == 0)
	{
		if (execve(full_path, argv, environ) == -1)
		{
			perror(prog_name);
			free(full_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	free(full_path);
	return (status);
}

/**
 * parse_line - Tokenizes an input line into arguments array
 * @line: Raw input string
 * @argv: Destination array for tokens
 *
 * Return: Number of parsed tokens.
 */
int parse_line(char *line, char **argv)
{
	int i = 0;
	char *token;

	token = strtok(line, " \t");
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;
	return (i);
}

/**
 * simple_shell - Main shell loop
 * @prog_name: Name of the shell program
 *
 * Return: Exit status.
 */
int simple_shell(char *prog_name)
{
	char *line = NULL, *argv[1024];
	size_t len = 0;
	ssize_t read;
	int cmd_count = 0, last_status = 0;

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
		cmd_count++;
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (parse_line(line, argv) == 0)
			continue;

		if (strcmp(argv[0], "exit") == 0)
		{
			free(line);
			exit(last_status);
		}
		if (strcmp(argv[0], "env") == 0)
			print_env();
		else
			last_status = execute_command(argv, prog_name, cmd_count);
	}
	free(line);
	return (last_status);
}
