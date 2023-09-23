#include "funcs.h"

/**
 * clear_info - initialize info_t structure
 * @info: structure address
 */

void clearinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setinfo - initialize info_t structure
 * @info: structure address
 * @av: argument vector
 */

void setinfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - free info_t structure field
 * @info: structure address
 * @all: true if freeing field
 */
void free_info(info_t *info, int all)
{
	ffrees(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffrees(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->read_fd > 2)
			close(info->read_fd);
		_putchar(BUFFER_FLUSH);
	}
}
