/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:00:57 by hqixeo            #+#    #+#             */
/*   Updated: 2022/11/13 08:00:59 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_getenv(char **envp, const char *varname)
{
	char	*var_joined;
	size_t	len_varname;

	var_joined = ft_strjoin(varname, "=");
	len_varname = ft_strlen(var_joined);
	while (*envp != NULL && ft_strncmp(*envp, var_joined, len_varname))
		envp++;
	free(var_joined);
	if (*envp == NULL)
		return (NULL);
	else
		return ((*envp) + len_varname);
}

void	ft_pathaccess(char **envp, char **executable)
{
	char	*joined;
	char	**path;
	size_t	y;

	y = 0;
	path = ft_split(ft_getenv(envp, "PATH"), ':');
	while (path[y] != NULL)
	{
		joined = ft_strinsert(path[y++], "/", *executable);
		if (access(joined, F_OK | X_OK) != -1)
		{
			free(*executable);
			*executable = joined;
			break ;
		}
		free(joined);
	}
	ft_strlistclear(path);
}
