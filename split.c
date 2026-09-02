#include "shell.h"

/**
 * split_line - Splits a string into an array of arguments
 * @line: The command line string
 *
 * Return: Array of strings (arguments)
 */
char **split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("hsh: allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\n");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("hsh: allocation error");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\n");
	}
	tokens[position] = NULL;
	return (tokens);
}
