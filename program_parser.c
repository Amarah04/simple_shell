#include "funcs.h"

/**
 * is_cmd - determine a file is an executable command
 * @info: info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates chars
 * @pathstrg: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */

char *dup_chars(char *pathstrg, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstrg[i] != ':')
			buf[k++] = pathstrg[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - find this cmd in the PATH string
 * @info: info struct
 * @pathstrg: PATH string
 * @cmd: cmd to find
 *
 * Return: full path of cmd if found or NULL
 */

char *find_path(info_t *info, char *pathstrg, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstrg)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstrg[i] || pathstrg[i] == ':')
		{
			path = dup_chars(pathstrg, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstrg[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
