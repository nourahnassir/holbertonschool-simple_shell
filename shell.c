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

        if (strlen(line) == 0)
            continue;

        argv[0] = line;
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
