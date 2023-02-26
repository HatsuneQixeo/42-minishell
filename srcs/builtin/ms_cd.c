/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 10:21:05 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 18:26:22 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expander.h"

static int	cd_core(const char *path)
{
	if (chdir(path) == -1)
		ms_perror(path);
	else
		return (0);
	return (1);
}

static int	cd_updatepath(t_data *data, const char *pwd_before, char **p_oldpwd)
{
	char	*argv[3];
	char	pwd[1024];

	if (!getcwd(pwd, sizeof(pwd)))
	{
		ms_perror("cd");
		return (1);
	}
	free(*p_oldpwd);
	*p_oldpwd = ft_strdup(pwd_before);
	argv[0] = ft_strjoin("PWD=", pwd);
	argv[1] = ft_strjoin("OLDPWD=", pwd_before);
	argv[2] = NULL;
	ms_export(argv, data);
	free(argv[0]);
	free(argv[1]);
	return (0);
}

static const char	*cd_getpath(char **envp, const char *varname,
			const char *oldpwd)
{
	const char	*path = NULL;

	if (!ft_strcmp(varname, "OLDPWD"))
	{
		path = oldpwd;
		if (oldpwd != NULL)
			ft_putendl_fd(oldpwd, 1);
	}
	else
		path = ft_getenv(envp, varname);
	if (path == NULL)
		ms_errlog("cd: %s not set\n", varname);
	return (path);
}

int	ms_cd(char **argv, t_data *data)
{
	static char	*oldpwd;
	char		pwd[1024];
	const char	*path = argv[1];

	if (!getcwd(pwd, sizeof(pwd)))
	{
		ms_perror("cd");
		return (1);
	}
	if (path == NULL)
		path = cd_getpath(data->envp, "HOME", oldpwd);
	else if (!ft_strcmp(path, "-"))
		path = cd_getpath(data->envp, "OLDPWD", oldpwd);
	return (path == NULL
		|| cd_core(path)
		|| cd_updatepath(data, pwd, &oldpwd));
}
