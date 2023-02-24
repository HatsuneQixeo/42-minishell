#include "rdrt.h"

int	stris_onlyspace(const char *str)
{
	while (*str != '\0' && ft_isspace(*str))
		str++;
	return (*str == '\0');
}

int	rdrt_ambiguous(const t_rdrt *rdrt)
{
	if (rdrt->lst_value == NULL || rdrt->lst_value->next != NULL
		|| stris_onlyspace(rdrt->lst_value->content))
		ms_errlog("%s: ambiguous redirect\n", rdrt->str_arg);
	else
		return (0);
	return (1);
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
