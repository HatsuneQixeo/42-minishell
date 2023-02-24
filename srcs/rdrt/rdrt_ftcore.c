#include "rdrt.h"

int	ambiguous(const char *str_arg)
{
	ms_errlog("%s: ambiguous redirect\n", str_arg);
	return (-1);
}

int	rdrt_core(const char *path, int std_fileno, int option, ...)
{
	int		fd;
	va_list	args;

	va_start(args, option);
	fd = open(path, option, va_arg(args, int));
	va_end(args);
	if (fd == -1)
	{
		ms_perror(path);
		return (-1);
	}
	ft_dup3(fd, std_fileno);
	return (0);
}
