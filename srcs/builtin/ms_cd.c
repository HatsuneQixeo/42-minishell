#include "minishell.h"

/**
 * @brief Unset HOME, update HOME
 * 	Update pwd, and oldpwd, cd - go to oldpwd
 * @param argc 
 * @param argv 
 * @param data 
 * @return int 
 */
int	ms_cd(char **argv, t_data *data)
{
	const char			*path;
	static const char	*oldpwd;

	ft_printf("it's me cd!\n");
	if (argv[1] == NULL)
		path = ft_getenv(data->envp, "HOME");
	else
		path = argv[1];
	if (path == NULL)
		ms_errlog(": %s: HOME not set\n", argv[0]);
	if (chdir(path) == -1)
		perror(path);
	else
	{
		/* Update pwd and oldpwd */
		return (0);
	}
	return (1);
}
