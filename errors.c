#include "funcs.h"

/**
 *_eputs - print input string
 * @str: string to print
 *
 * Return: Nothing
 */

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - write character c to stderr
 * @c:Char to print
 *
 * Return:  success 1.
 * On error, -1 returned, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - write char c to given fd
 * @c:Char to print
 * @fd: filedescriptor to write to
 *
 * Return: success 1.
 * On error, -1 returned, and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - print input string
 * @str:  string to print
 * @fd: filedescriptor to write to
 *
 * Return: number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
