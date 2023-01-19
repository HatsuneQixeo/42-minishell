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

char	*ft_findenvp(char **envp, const char *varname)
{
	char	*var_find;
	size_t	len_varname;

	var_find = ft_strjoin(varname, "=");
	len_varname = ft_strlen(var_find);
	while (*envp != NULL && ft_strncmp(*envp, var_find, len_varname))
		envp++;
	free(var_find);
	if (*envp != NULL)
		return ((*envp) + len_varname);
	return (NULL);
}

void	ft_pathaccess(char **envp, char **command)
{
	char	*joined;
	char	**path;
	size_t	y;

	y = 0;
	path = ft_split(ft_findenvp(envp, "PATH"), ':');
	while (path[y] != NULL)
	{
		joined = ft_strinsert(path[y++], "/", *command);
		if (!access(joined, F_OK | X_OK))
		{
			ft_strlistclear(path);
			free(*command);
			*command = joined;
			return ;
		}
		free(joined);
	} 
}
