#include "shell.h"

/**
 * simple_shell - Reads and executes single-word commands using execve
 */
void simple_shell(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	char *argv[2];
	char *cmd;
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

		/* إزالة حرف السطر الجديد والأطراف الفارغة */
		for (i = 0; line[i] != '\0'; i++)
		{
			if (line[i] == '\n' || line[i] == '\r')
			{
				line[i] = '\0';
				break;
			}
		}

		/* تجاوز المسافات في البداية */
		cmd = line;
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;

		if (*cmd == '\0')
			continue;

		/* إزالة المسافات من النهاية */
		for (i = strlen(cmd) - 1; i >= 0; i--)
		{
			if (cmd[i] == ' ' || cmd[i] == '\t')
				cmd[i] = '\0';
			else
				break;
		}

		if (strlen(cmd) == 0)
			continue;

		argv[0] = cmd;
		argv[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("Error forging process");
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
	free(line);
}
