#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: Name of the environment variable
 *
 * Return: Pointer to the value string, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i;
	size_t len;

	if (!name || !environ)
		return (NULL);

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

/**
 * build_full_path - Concatenates directory and command name
 * @dir: Directory path
 * @cmd: Command name
 *
 * Return: Pointer to newly allocated string, or NULL on failure
 */
char *build_full_path(char *dir, char *cmd)
{
	size_t len;
	char *full_path;

	len = strlen(dir) + strlen(cmd) + 2;
	full_path = malloc(sizeof(char) * len);
	if (!full_path)
		return (NULL);

	sprintf(full_path, "%s/%s", dir, cmd);
	return (full_path);
}

/**
 * find_path - Resolves the executable path of a command using PATH
 * @cmd: The command to resolve
 *
 * Return: Full path to command if found and executable, otherwise NULL
 */
char *find_path(char *cmd)
{
	char *path_env, *path_copy, *token, *full_path;

	if (!cmd || *cmd == '\0')
		return (NULL);

	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path_env = _getenv("PATH");
	if (!path_env || *path_env == '\0')
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = build_full_path(token, cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
