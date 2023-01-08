/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 01:12:32 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 01:16:45 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*ms_path_full_create(char *dir, char *cmd)
{
	char	*full_path;
	int		path_len;

	path_len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = malloc(sizeof(char) * path_len);
	if (full_path)
	{
		ft_strlcpy(full_path, dir, ft_strlen(dir) + 1);
		ft_strlcat(full_path, "/", path_len);
		ft_strlcat(full_path, cmd, path_len);
	}
	return (full_path);
}

char	*ms_path_search(char *cmd)
{
	char	*dir;
	char	*full_path;
	char	*env_paths;

	env_paths = getenv("PATH");
	if (!env_paths)
		return (NULL);
	dir = ms_strtok(env_paths, ":");
	while (dir)
	{
		full_path = ms_path_full_create(dir, cmd);
		if (access(full_path, F_OK) == 0)
		{
			free(dir);
			return (full_path);
		}
		free(dir);
		free(full_path);
		dir = ms_strtok(NULL, ":");
	}
	return (NULL);
}
