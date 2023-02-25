/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:00:57 by hqixeo            #+#    #+#             */
/*   Updated: 2023/02/25 10:21:05 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

// void	ft_pathaccess(char **envp, char **executable)
// {
// 	char	*joined;
// 	char	**path;
// 	size_t	y;

// 	y = 0;
// 	path = ft_split(ft_getenv(envp, "PATH"), ':');
// 	while (path[y] != NULL)
// 	{
// 		joined = ft_strinsert(path[y++], "/", *executable);
// 		if (access(joined, F_OK | X_OK) != -1)
// 		{
// 			free(*executable);
// 			*executable = joined;
// 			break ;
// 		}
// 		free(joined);
// 	}
// 	ft_strlistclear(path);
// }
