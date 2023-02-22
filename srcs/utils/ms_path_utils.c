/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:18:22 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/22 18:51:56 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	file_in_path(char *dir_path, char *file)
{
	DIR				*dir;
	struct dirent	*entry;

	if (!dir_path || !file)
		return (false);
	dir = opendir(dir_path);
	entry = readdir(dir);
	while (entry)
	{
		if (!ft_strncmp(entry->d_name, file, ft_strlen(file)))
		{
			closedir(dir);
			return (true);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (false);
}

char	*absolute_path_find(char *file)
{
	int		i;
	char	*tmp;
	char	*absolute_path;
	char	**paths;

	i = -1;
	absolute_path = NULL;
	paths = ft_split(env_value_get("PATH"), ':');
	while (paths[++i])
	{
		if (file_in_path(paths[i], file))
		{
			tmp = ft_strjoin(paths[i], "/");
			absolute_path = ft_strjoin(tmp, file);
			free(tmp);
			break ;
		}
	}
	util_arr_str_free(paths);
	return (absolute_path);
}