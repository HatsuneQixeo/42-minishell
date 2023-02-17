#include "minishell.h"

int	ctrl_(int argc, char **argv, t_data *data)
{
	if (argc == 1)
		exit(0);
	else if (!ft_strisnumeric(argv[1]))
	{
		ft_dprintf(2, MINISHELL": %s: %s: numeric argument required\n",
			argv[0], argv[1]);
		exit(255);
	}
	else if (argc > 1 + 1)
		ft_dprintf(2, MINISHELL": %s: too many arguments\n", argv[0]);
	else
		exit(ft_atoi(argv[1]));
	return (1);
}
