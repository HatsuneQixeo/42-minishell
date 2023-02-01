#include "minishell.h"

int	ms_pwd(int argc, char **argv, t_data *data)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		perror("getcwd in ms_pwd");
	else
		return (!ft_putendl_fd(cwd, 1));
	return (1);
}
