#include "minishell.h"

static int	echo_endl(const char *str)
{
	if (*str++ != '-')
		return (1);
	while (*str == 'n')
		str++;
	return (*str != '\0');
}

int	ms_echo(char **argv, t_data *data)
{
	int	nl;

	ft_printf("it's me echo!\n");
	nl = 1;
	while (*++argv != NULL && !echo_endl(*argv))
		nl = 0;
	while (*argv != NULL)
	{
		ft_putstr_fd(*argv, 1);
		write(1, " ", (*++argv != NULL));
		// if (*++argv != NULL)
		// 	ft_putchar_fd(' ', 1);
	}
	if (nl)
		ft_putchar_fd('\n', 1);
	return (0);
	(void)data;
}
