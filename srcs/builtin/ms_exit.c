#include "minishell.h"

int	ms_exit(char **argv, t_data *data)
{
	const char	*prgname = argv[0];
	const char	*arg = argv[1];

	ft_putendl_fd(prgname, 2);
	if (arg == NULL)
		exit(0);
	else if (!ft_strisnumeric(arg))
	{
		ms_errlog("%s: %s: numeric argument required\n", prgname, arg);
		exit(255);
	}
	else if (argv[2] != NULL)
		ms_errlog("%s: too many arguments\n", prgname);
	else
		exit(ft_atoi(arg));
	return (1);
}
