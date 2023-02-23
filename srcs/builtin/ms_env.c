#include "minishell.h"

int	ms_env(char **argv, t_data *data)
{
	ft_strlistiteri(data->envp, iteristr_putendl);
	return (0);
	(void)argv;
}
