/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan-wan <ntan-wan@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 22:31:59 by ntan-wan          #+#    #+#             */
/*   Updated: 2023/01/09 01:15:24 by ntan-wan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute_cmd(char **argv)
{
	char	*path;

	path = ms_path_search(argv[0]);
	if (!path)
		return (1);
	execv(path, argv);
	free(path);
	return (0);
}

int	do_cmd(t_node *node)
{
	char		**argv;

	if (!node)
		return (1);
	argv = ms_node_to_argv(node);
	int i;
	i = -1;

	while (argv[++i])
		printf("%s\n", argv[i]);
	i = -1;
	while (argv[++i])
	{
		free(argv[i]);
	}
	free(argv);
}

void	free_cmd()
{
	
}