#include "minishell.h"

int	ms_cd(int argc, char **argv, t_data *data)
{
	const char	*path;

	ft_printf("it's me cd!\n");
	if (argc == 1)
		path = ft_getenv(data->envp, "HOME");
	else
		path = argv[1];
	if (chdir(path) == -1)
		perror(path);
	else
		return (0);
	return (1);
}
