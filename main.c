#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Status code.
 */
int main(int argc, char **argv)
{
	(void)argc;
	return (simple_shell(argv[0]));
}
