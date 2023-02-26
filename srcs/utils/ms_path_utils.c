/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:18:22 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/02/24 15:36:33 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_same_name(char *name1, char *name2)
{
	int	str_len1;
	int	str_len2;
	int	longer_len;

	str_len1 = ft_strlen(name1);
	str_len2 = ft_strlen(name2);
	if (str_len1 > str_len2)
		longer_len = str_len1;
	else
		longer_len = str_len2;
	return (ft_strncmp(name1, name2, longer_len) == 0);
}

/* 
	@brief Check whether the file is contained in the given path.
 */
bool	file_in_path(char *dir_path, char *file_name)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dir_path);
	if (!dir_path || !file_name || !dir)
		return (false);
	entry = readdir(dir);
	while (entry)
	{
		if (is_same_name(entry->d_name, file_name))
		{
			closedir(dir);
			return (true);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (false);
}

/* 
	@brief Find absolute path to the cmd.
	@note Eg: "ls" -> "/usr/bin/ls"
 */
char	*absolute_path_find(char *file_name)
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
		if (file_in_path(paths[i], file_name))
		{
			tmp = ft_strjoin(paths[i], "/");
			absolute_path = ft_strjoin(tmp, file_name);
			free(tmp);
			break ;
		}
	}
	util_arr_str_free(paths);
	return (absolute_path);
}

bool	file_in_path2(char *path, char *file_name)
{
	char	*tmp;
	char	*tmp_path;
	bool	result;

	tmp = ft_strjoin(path, "/");
	tmp_path = ft_strjoin(tmp, file_name);
	if (access(tmp_path, F_OK | X_OK) == 0)
		result = true;
	else
		result = false;
	free(tmp);
	free(tmp_path);
	return (result);
}

char	*absolute_path_find2(char *file_name)
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
		if (file_in_path2(paths[i], file_name))
		{
			tmp = ft_strjoin(paths[i], "/");
			absolute_path = ft_strjoin(tmp, file_name);
			break ;
		}
	}
	util_arr_str_free(paths);
	return (absolute_path);
}